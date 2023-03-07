#include "../functions.h"

int main(int argc, char *argv[]) {
  char cNomImgLue[250];
  int nH, nW, nTaille, indice_profil;
  char L_or_C;

  if (argc != 4) {
    printf("Usage: ImageIn.pgm Ligne(l)/Colonne(c) indice\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%c", &L_or_C);
  sscanf(argv[3], "%d", &indice_profil);

  OCTET *ImgIn;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

  if (L_or_C == 'l') {
    if (indice_profil > nW) {
      printf("Il n'y a que %d lignes!\n", nW);
      exit(1);
    }
    for (int i = 0; i < nW; i++) {
      printf("%d %d\n", i, ImgIn[indice_profil * nH + i]);
    }
  } else {
    if (indice_profil > nH) {
      printf("Il n'y a que %d colonnes!\n", nH);
      exit(1);
    }
    for (int i = 0; i < nH; i++) {
      printf("%d %d\n", i, ImgIn[indice_profil + nW * i]);
    }
  }

  free(ImgIn);

  return 1;
}
