// Copyright 2023 <Sébastien VIAL>
#include "../functions.h"

int main(int argc, char *argv[]) {
  if (argc != 5) {
    printf("Usage: %s <input> <output> <radius> <passes>\n", argv[0]);
    exit(0);
  }

  int width, height;
  lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
  int size = width * height;

  OCTET *in, *out;
  allocation_tableau(in, OCTET, size);
  allocation_tableau(out, OCTET, size);

  lire_image_pgm(argv[1], in, size);

  int radius, passes;
  sscanf(argv[3], "%i", &radius);
  sscanf(argv[4], "%i", &passes);
  blur(in, out, width, height, radius, passes);

  ecrire_image_pgm(argv[2], out, height, width);
  free(in);
  free(out);

  return 0;
}
