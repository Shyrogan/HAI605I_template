// Copyright 2023 <Sébastien VIAL>
#include "../functions.h"

int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("Usage: %s <input.pgm> <output.dat> <column|line> <index>\n",
           argv[0]);
    exit(1);
  }

  int width, height;
  lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
  int size = width * height;

  OCTET *in;
  allocation_tableau(in, OCTET, size);
  lire_image_pgm(argv[1], in, size);

  FILE *f = fopen(argv[2], "wb");

  int index;
  sscanf(argv[4], "%i", &index);

  if (strcmp(argv[3], "column") == 0) {
    for (int y = 0; y < height; y++) {
      fprintf(f, "%i %i\n", y, in[y * width + index]);
    }
    printf("Écriture du fichier .dat en colonne terminée\n");
  } else {
    for (int x = 0; x < width; x++) {
      fprintf(f, "%i %i\n", x, in[index * width + x]);
    }
    printf("Écriture du fichier .dat en ligne terminée\n");
  }

  fclose(f);
  free(in);

  return 0;
}
