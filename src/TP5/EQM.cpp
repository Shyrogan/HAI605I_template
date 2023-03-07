#include "../functions.h"

int main(int argc, char *argv[]) {

  char cNomImgLue1[250], cNomImgLue2[250];
  int nH1, nW1, nTaille1, nH2, nW2, nTaille2;

  if (argc != 3) {
    printf("Usage: ImageIn2.pgm ImageIn2.pgm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue1);
  sscanf(argv[2], "%s", cNomImgLue2);

  OCTET *ImgIn1, *ImgIn2;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH1, &nW1);
  nTaille1 = nH1 * nW1;

  allocation_tableau(ImgIn1, OCTET, nTaille1);
  lire_image_pgm(cNomImgLue1, ImgIn1, nH1 * nW1);

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue2, &nH2, &nW2);
  nTaille2 = nH2 * nW2;

  allocation_tableau(ImgIn2, OCTET, nTaille2);
  lire_image_pgm(cNomImgLue2, ImgIn2, nH2 * nW2);

  if (nTaille1 != nTaille2) {
    perror("Pas bon!\n");
    exit(0);
  }

  int eqm = 0;

  for (int i = 0; i < nH1 - 1; i++) {
    for (int j = 0; j < nW1 - 1; j++) {
      int im_diff =
          ImgIn1[indiceImage(i, j, nW1)] - ImgIn2[indiceImage(i, j, nW1)];
      eqm += (im_diff * im_diff);
    }
  }

  eqm /= nTaille1;

  printf("EQM = %d\n", eqm);

  free(ImgIn1);
  free(ImgIn2);

  return 1;
}
