#include "../functions.h"

int main(int argc, char *argv[]) {

  char cNomImgLue[250], cNomImgEcrite1[250], cNomImgEcrite2[250],
      cNomImgEcrite3[250];
  int nH, nW, nTaille, nR, nG, nB;

  if (argc != 5) {
    printf("Usage: ImageIn.ppm ImageOutY ImageOutCb ImageOutCr.pgm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite1);
  sscanf(argv[3], "%s", cNomImgEcrite2);
  sscanf(argv[4], "%s", cNomImgEcrite3);
  OCTET *ImgIn, *ImgOut1, *ImgOut2, *ImgOut3;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

  allocation_tableau(ImgOut1, OCTET, nTaille);
  allocation_tableau(ImgOut2, OCTET, nTaille);
  allocation_tableau(ImgOut3, OCTET, nTaille);

  for (int i = 0; i < nTaille3; i += 3) {
    ImgOut1[i / 3] =
        (ImgIn[i] * 0.299 + ImgIn[i + 1] * 0.587 + ImgIn[i + 2] * 0.114);
    ImgOut2[i / 3] =
        -0.1687 * ImgIn[i] - 0.3313 * ImgIn[i + 1] + 0.5 * ImgIn[i + 2] + 128;
    ImgOut3[i / 3] =
        0.5 * ImgIn[i] - 0.4187 * ImgIn[i + 1] - 0.0813 * ImgIn[i + 2] + 128;
  }

  ecrire_image_pgm(cNomImgEcrite1, ImgOut1, nH, nW);
  ecrire_image_pgm(cNomImgEcrite2, ImgOut2, nH, nW);
  ecrire_image_pgm(cNomImgEcrite3, ImgOut3, nH, nW);

  free(ImgIn);
  free(ImgOut1);
  free(ImgOut2);
  free(ImgOut3);

  return 1;
}
