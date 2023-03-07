// Copyright 2023 <Sébastien VIAL>
#include "../functions.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <image.ppm> <sortie.dat>", argv[0]);
    exit(1);
  }

  OCTET T[256 * 3];
  memset(T, 0, sizeof(T));

  int width, height;
  lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
  int size = width * height;

  OCTET *in;
  allocation_tableau(in, OCTET, size * 3);

  lire_image_ppm(argv[1], in, size);

  FILE *f = fopen(argv[2], "wb");
  if (f == NULL) {
    printf("Erreur lors de la création du fichier\n");
    exit(1);
  }

  for (int i = 0; i < size * 3; i += 3) {
    OCTET nR = in[i];
    OCTET nG = in[i + 1];
    OCTET nB = in[i + 2];

    T[3 * nR]++;
    T[3 * nG + 1]++;
    T[3 * nB + 2]++;
  }

  fprintf(f, "Ind NR NG NB\n");
  for (int k = 0; k < 256; k++) {
    fprintf(f, "%i %i %i %i\n", k, T[3 * k], T[3 * k + 1], T[3 * k + 2]);
  }

  fclose(f);
  free(in);

  printf("Fichier %s écrit.\n", argv[2]);

  return 0;
}
