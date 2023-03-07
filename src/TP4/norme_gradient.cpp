#include "../functions.h"

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3) {
    printf("Usage: ImageIn.pgm ImageOut.pgm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nH - 1; i++) {
    for (int j = 0; j < nW - 1; j++) {
      OCTET pix = ImgIn[indiceImage(i, j, nW)];
      OCTET pixGauche = ImgIn[indiceImage(i, j + 1, nW)];
      OCTET pixBas = ImgIn[indiceImage(i + 1, j, nW)];

      int deltaX = pix - pixGauche;
      int deltaY = pix - pixBas;

      ImgOut[indiceImage(i, j, nW)] = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    }
  }

  // Gradient Inverse!
  // for (int i=nH-1; i > 1; i--){
  //     for (int j=nW-1; j > 1; j--){

  //         OCTET pix = ImgIn[indiceImage(i, j, nW)];
  //         OCTET pixGauche = ImgIn[indiceImage(i, j-1, nW)];
  //         OCTET pixBas = ImgIn[indiceImage(i-1, j, nW)];

  //         int deltaX = pix - pixGauche;
  //         int deltaY = pix - pixBas;

  //         ImgOut[indiceImage(i, j, nW)] =
  //             sqrt(pow(deltaX,2)+pow(deltaY,2));
  //     }
  // }
  // Fin Gradient Inverse!

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
