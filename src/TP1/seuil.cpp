// Copyright 2023 <Sébastien VIAL>
#include "../functions.h"

int main(int argc, char *argv[]) {
  if (argc <= 3) {
    printf("Usage: %s <input> <output> <s1>...\n", argv[0]);
    exit(0);
  }

  int width, height;
  lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
  int size = width * height;

  OCTET *in, *out;
  allocation_tableau(in, OCTET, size);
  allocation_tableau(out, OCTET, size);

  lire_image_pgm(argv[1], in, size);

  int seuilCount = argc - 3;
  int *seuils = (int *)malloc(sizeof(int) * seuilCount);
  for (int i = 0; i < seuilCount; i++) {
    printf("S%i: %s\n", i, argv[3 + i]);
    sscanf(argv[3 + i], "%i", seuils + i);
  }
  seuillage(in, out, width, height, seuilCount, seuils);

  ecrire_image_pgm(argv[2], out, height, width);
  free(seuils);
  free(in);
  free(out);

  return 0;
}
