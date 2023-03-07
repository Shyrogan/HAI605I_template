#include "../functions.h"

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;

  if (argc != 5) {
    printf("Usage: ImageIn.pgm ImageOut.pgm Seuil_Bas Seuil_Haut \n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%d", &SB);
  sscanf(argv[4], "%d", &SH);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nH; i++) {
    for (int j = 0; j < nW; j++) {
      if (ImgIn[indiceImage(i, j, nW)] <= SB) {
        ImgOut[indiceImage(i, j, nW)] = 0;
      } else if (ImgIn[indiceImage(i, j, nW)] >= SH) {
        ImgOut[indiceImage(i, j, nW)] = 255;
      } else {
        ImgOut[indiceImage(i, j, nW)] = ImgIn[indiceImage(i, j, nW)];
      }
    }
  }

  for (int i = 1; i < nH - 1; i++) {
    for (int j = 1; j < nW - 1; j++) {
      if (ImgOut[indiceImage(i, j, nW)] > SB &&
          ImgOut[indiceImage(i, j, nW)] < SH) {
        if (au_moins_1_voisin(ImgOut, i, j, nW, 255)) {
          ImgOut[indiceImage(i, j, nW)] = 255;
        } else {
          ImgOut[indiceImage(i, j, nW)] = 0;
        }
      }
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
