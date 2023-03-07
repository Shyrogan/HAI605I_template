// Copyright 2023 <Sébastien VIAL>
#include "../functions.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <image.pgm> <sortie.dat>", argv[0]);
    exit(1);
  }

  OCTET T[256];
  memset(T, 0, sizeof(T));

  int width, height;
  lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
  int size = width * height;

  OCTET *in;
  allocation_tableau(in, OCTET, size);

  lire_image_pgm(argv[1], in, size);

  FILE *f = fopen(argv[2], "wb");
  if (f == NULL) {
    printf("Erreur lors de la création du fichier\n");
    exit(1);
  }

  for (int i = 0; i < size; i++) {
    OCTET n = in[i];

    T[n]++;
  }

  fprintf(f, "Ind NG\n");
  for (int k = 0; k < 256; k++) {
    fprintf(f, "%i %i\n", k, T[k]);
  }

  fclose(f);
  free(in);

  printf("Fichier %s écrit.\n", argv[2]);

  return 0;
}
