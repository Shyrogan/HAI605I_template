#include "../functions.h"

int main(int argc, char *argv[]) {

  char cNomImgLueY[250], cNomImgLueCb[250], cNomImgLueCr[250],
      cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;

  if (argc != 5) {
    printf("Usage: ImageInY.pgm ImageInCb.pgm ImageInCr.pgm ImageOut.ppm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLueY);
  sscanf(argv[2], "%s", cNomImgLueCb);
  sscanf(argv[3], "%s", cNomImgLueCr);
  sscanf(argv[4], "%s", cNomImgEcrite);

  OCTET *ImgInY, *ImgInCb, *ImgInCr, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
  lire_nb_lignes_colonnes_image_pgm(cNomImgLueCb, &nH, &nW);
  lire_nb_lignes_colonnes_image_pgm(cNomImgLueCr, &nH, &nW);

  nTaille = nH * nW;

  allocation_tableau(ImgInY, OCTET, nTaille);
  allocation_tableau(ImgInCb, OCTET, nTaille);
  allocation_tableau(ImgInCr, OCTET, nTaille);

  lire_image_pgm(cNomImgLueY, ImgInY, nH * nW);
  lire_image_pgm(cNomImgLueCb, ImgInCb, nH * nW);
  lire_image_pgm(cNomImgLueCr, ImgInCr, nH * nW);

  allocation_tableau(ImgOut, OCTET, nTaille * 3);

  for (int i = 0; i < nTaille * 3; i += 3) {
    nR = ImgInY[i / 3] + 1.402 * (ImgInCr[i / 3] - 128);
    nG = ImgInY[i / 3] - 0.34414 * (ImgInCb[i / 3] - 128) -
         0.714414 * (ImgInCr[i / 3] - 128);
    nB = ImgInY[i / 3] + 1.772 * (ImgInCb[i / 3] - 128);

    // Gestion débordement//
    if (nR < 0)
      nR = 0;
    if (nR > 255)
      nR = 255;
    if (nG < 0)
      nG = 0;
    if (nG > 255)
      nG = 255;
    if (nB < 0)
      nB = 0;
    if (nB > 255)
      nB = 255;
    // Fin Gestion débordement//

    ImgOut[i] = nR;
    ImgOut[i + 1] = nG;
    ImgOut[i + 2] = nB;
  }

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);

  free(ImgInY);
  free(ImgInCb);
  free(ImgInCr);
  free(ImgOut);

  return 1;
}
// set yrange [0:2000]
