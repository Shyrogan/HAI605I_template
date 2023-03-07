#include "../functions.h"

int main(int argc, char *argv[]) {

  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;

  if (argc != 3) {
    printf("Usage: ImageIn.ppm ImageOut.pgm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;

  int k = 80;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nTaille3; i += 3) {
    ImgOut[i / 3] =
        (ImgIn[i] * 0.299 + ImgIn[i + 1] * 0.587 + ImgIn[i + 2] * 0.114);
    if (ImgOut[i / 3] + k < 0) {
      ImgOut[i / 3] = 0;
    } else if (ImgOut[i / 3] + k > 255) {
      ImgOut[i / 3] = 255;
    } else {
      ImgOut[i / 3] += k;
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

  free(ImgIn);
  free(ImgOut);

  return 1;
}
