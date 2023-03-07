// ----------------------------------------------------------------------------
// Filename        : image_ppm.c
// Description     :
// Created On      : Tue Mar 31 13:26:36 2005
// ----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define allocation_tableau(nom, type, nombre)                                  \
  if ((nom = (type *)calloc(nombre, sizeof(type))) == NULL) {                  \
    printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");  \
    exit(1);                                                                   \
  }

typedef unsigned char OCTET;

/*===========================================================================*/
void ignorer_commentaires(FILE *f) {
  unsigned char c;
  while ((c = fgetc(f)) == '#')
    while ((c = fgetc(f)) != '\n')
      ;
  fseek(f, -sizeof(unsigned char), SEEK_CUR);
}
/*===========================================================================*/

/*===========================================================================*/
void ecrire_image_ppm(char nom_image[], OCTET *pt_image, int nb_lignes,
                      int nb_colonnes) {
  FILE *f_image;
  int taille_image = 3 * nb_colonnes * nb_lignes;

  if ((f_image = fopen(nom_image, "wb")) == NULL) {
    printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fprintf(f_image, "P6\r"); /*ecriture entete*/
    fprintf(f_image, "%d %d\r255\r", nb_colonnes, nb_lignes);

    if ((fwrite((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) !=
        (size_t)(taille_image)) {
      printf("\nErreur d'ecriture de l'image %s \n", nom_image);
      exit(EXIT_FAILURE);
    }
    fclose(f_image);
  }
}
/*===========================================================================*/

/*===========================================================================*/
void lire_nb_lignes_colonnes_image_ppm(char nom_image[], int *nb_lignes,
                                       int *nb_colonnes) {
  FILE *f_image;
  int max_grey_val;

  /* cf : l'entete d'une image .ppm : P6                   */
  /*				       nb_colonnes nb_lignes */
  /*    			       max_grey_val          */

  if ((f_image = fopen(nom_image, "rb")) == NULL) {
    printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fscanf(f_image, "P6 ");
    ignorer_commentaires(f_image);
    fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
    fclose(f_image);
  }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_ppm(char nom_image[], OCTET *pt_image, int taille_image) {
  FILE *f_image;
  int nb_colonnes, nb_lignes, max_grey_val;
  taille_image = 3 * taille_image;

  if ((f_image = fopen(nom_image, "rb")) == NULL) {
    printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fscanf(f_image, "P6 ");
    ignorer_commentaires(f_image);
    fscanf(f_image, "%d %d %d%*c", &nb_colonnes, &nb_lignes,
           &max_grey_val); /*lecture entete*/

    if ((fread((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) !=
        (size_t)(taille_image)) {
      printf("\nErreur de lecture de l'image %s \n", nom_image);
      exit(EXIT_FAILURE);
    }
    fclose(f_image);
  }
}

/*===========================================================================*/
/*===========================================================================*/

void planR(OCTET *pt_image, OCTET *src, int taille_image) {
  int i;
  for (i = 0; i < taille_image; i++) {
    pt_image[i] = src[3 * i];
  }
}

/*===========================================================================*/
/*===========================================================================*/

void planV(OCTET *pt_image, OCTET *src, int taille_image) {
  int i;
  for (i = 0; i < taille_image; i++) {
    pt_image[i] = src[3 * i + 1];
  }
}

/*===========================================================================*/
/*===========================================================================*/

void planB(OCTET *pt_image, OCTET *src, int taille_image) {
  int i;
  for (i = 0; i < taille_image; i++) {
    pt_image[i] = src[3 * i + 2];
  }
}

/*===========================================================================*/
/*===========================================================================*/

void ecrire_image_pgm(char nom_image[], OCTET *pt_image, int nb_lignes,
                      int nb_colonnes) {
  FILE *f_image;
  int taille_image = nb_colonnes * nb_lignes;

  if ((f_image = fopen(nom_image, "wb")) == NULL) {
    printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fprintf(f_image, "P5\r"); /*ecriture entete*/
    fprintf(f_image, "%d %d\r255\r", nb_colonnes, nb_lignes);

    if ((fwrite((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) !=
        (size_t)taille_image) {
      printf("\nErreur de lecture de l'image %s \n", nom_image);
      exit(EXIT_FAILURE);
    }
    fclose(f_image);
  }
}
/*===========================================================================*/

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes,
                                       int *nb_colonnes) {
  FILE *f_image;
  int max_grey_val;

  /* cf : l'entete d'une image .pgm : P5                    */
  /*				       nb_colonnes nb_lignes */
  /*    			       max_grey_val          */

  if ((f_image = fopen(nom_image, "rb")) == NULL) {
    printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fscanf(f_image, "P5 ");
    ignorer_commentaires(f_image);
    fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
    fclose(f_image);
  }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_pgm(char nom_image[], OCTET *pt_image, int taille_image) {
  FILE *f_image;
  int nb_colonnes, nb_lignes, max_grey_val;

  if ((f_image = fopen(nom_image, "rb")) == NULL) {
    printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
    exit(EXIT_FAILURE);
  } else {
    fscanf(f_image, "P5 ");
    ignorer_commentaires(f_image);
    fscanf(f_image, "%d %d %d%*c", &nb_colonnes, &nb_lignes,
           &max_grey_val); /*lecture entete*/

    if ((fread((OCTET *)pt_image, sizeof(OCTET), taille_image, f_image)) !=
        (size_t)taille_image) {
      printf("\nErreur de lecture de l'image %s \n", nom_image);
      exit(EXIT_FAILURE);
    }
    fclose(f_image);
  }
}
/*===========================================================================*/
/*===========================================================================*/

int indiceImage(int x, int y, int width) {
  if (x >= width) {
    printf("x trop grand! %d %d\n", x, y);
  }
  if (y >= width) {
    printf("y trop grand! %d\n", y);
  }
  return x * width + y;
}

int floutage(OCTET *imgIn, int x, int y, int width) {
  int sum = 0;
  sum += imgIn[indiceImage(x, y, width)];
  sum += imgIn[indiceImage(x - 1, y, width)];
  sum += imgIn[indiceImage(x + 1, y, width)];
  sum += imgIn[indiceImage(x, y - 1, width)];
  sum += imgIn[indiceImage(x, y + 1, width)];
  return sum / 5;
}

int floutage2(OCTET *imgIn, int x, int y, int width) {
  int sum = 0;
  sum += imgIn[indiceImage(x, y, width)];
  sum += imgIn[indiceImage(x - 1, y, width)];
  sum += imgIn[indiceImage(x + 1, y, width)];
  sum += imgIn[indiceImage(x, y - 1, width)];
  sum += imgIn[indiceImage(x, y + 1, width)];
  sum += imgIn[indiceImage(x + 1, y + 1, width)];
  sum += imgIn[indiceImage(x - 1, y + 1, width)];
  sum += imgIn[indiceImage(x + 1, y - 1, width)];
  sum += imgIn[indiceImage(x - 1, y - 1, width)];
  return sum / 9;
}

int floutageGaussian(OCTET *imgIn, int x, int y, int width) {
  int sum = 0;
  sum += imgIn[indiceImage(x, y, width)] * 4;
  sum += imgIn[indiceImage(x - 1, y, width)] * 2;
  sum += imgIn[indiceImage(x + 1, y, width)] * 2;
  sum += imgIn[indiceImage(x, y - 1, width)] * 2;
  sum += imgIn[indiceImage(x, y + 1, width)] * 2;
  sum += imgIn[indiceImage(x + 1, y + 1, width)];
  sum += imgIn[indiceImage(x - 1, y + 1, width)];
  sum += imgIn[indiceImage(x + 1, y - 1, width)];
  sum += imgIn[indiceImage(x - 1, y - 1, width)];
  return sum / 16;
}

int au_moins_1_voisin(OCTET *imgIn, int x, int y, int width, int val) {
  return imgIn[indiceImage(x + 1, y + 1, width)] == val ||
         imgIn[indiceImage(x + 1, y, width)] == val ||
         imgIn[indiceImage(x, y + 1, width)] == val ||
         imgIn[indiceImage(x + 1, y - 1, width)] == val ||
         imgIn[indiceImage(x - 1, y + 1, width)] == val ||
         imgIn[indiceImage(x - 1, y, width)] == val ||
         imgIn[indiceImage(x, y - 1, width)] == val ||
         imgIn[indiceImage(x - 1, y - 1, width)] == val;
}

/*===========================================================================*/

// plot "dat/profil_ville_l_128.dat" using 1:2 title 'Normal' with lines,
// "dat/profil_ville_f2_1_l_128.dat" using 1:2 title 'FloueX1' with lines,
// "dat/profil_ville_f2_2_l_128.dat" using 1:2 title 'FloueX2' with lines,
// "dat/profil_ville_f2_3_l_128.dat" using 1:2 title 'FloueX3' with lines,
// "dat/profil_ville_f2_4_l_128.dat" using 1:2 title 'FloueX4' with lines,
// "dat/profil_ville_f2_5_l_128.dat" using 1:2 title 'FloueX5' with lines

// plot "dat/histo_ville_pgm.dat" using 1:2 title 'Normal' with lines,
// "dat/histo_ville_f2_1.dat" using 1:2 title 'FloueX1' with lines,
// "dat/histo_ville_f2_2.dat" using 1:2 title 'FloueX2' with lines,
// "dat/histo_ville_f2_3.dat" using 1:2 title 'FloueX3' with lines,
// "dat/histo_ville_f2_4.dat" using 1:2 title 'FloueX4' with lines,
// "dat/histo_ville_f2_5.dat" using 1:2 title 'FloueX5' with lines
