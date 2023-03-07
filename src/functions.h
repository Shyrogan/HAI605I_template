#include "./library.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

OCTET get(OCTET *in, int x, int y, int width, int height) {
  x = fmax(0, fmin(x, width));
  y = fmax(0, fmin(y, height));

  return in[y * width + x];
}

void set(OCTET *out, OCTET pixel, int x, int y, int width, int height) {
  x = fmax(0, fmin(x, width));
  y = fmax(0, fmin(y, height));

  out[y * width + x] = pixel;
}

void fill_pgm(OCTET *in, OCTET *out, int size) {
  for (int i = 0; i < size; i++) {
    out[i] = in[i];
  }
}

void seuillage(OCTET *in, OCTET *out, int width, int height, int seuilCount,
               int seuils[]) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      OCTET pixel = get(in, x, y, width, height);
      set(out, 255, x, y, width, height);
      for (int s = 0; s < seuilCount; s++) {
        int seuil = seuils[s];
        if (pixel < seuil) {
          set(out, 255 - 255 / (s + 1), x, y, width, height);
        }
      }
    }
  }
}

void dilatation(OCTET *in, OCTET *out, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      OCTET cur = get(in, x, y, width, height);
      OCTET l = get(in, x - 1, y, width, height);
      OCTET r = get(in, x + 1, y, width, height);
      OCTET t = get(in, x, y + 1, width, height);
      OCTET b = get(in, x, y - 1, width, height);

      set(out, fmax(cur, fmax(l, fmax(r, fmax(t, b)))), x, y, width, height);
    }
  }
}

void erosion(OCTET *in, OCTET *out, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      OCTET cur = get(in, x, y, width, height);
      OCTET l = get(in, x - 1, y, width, height);
      OCTET r = get(in, x + 1, y, width, height);
      OCTET t = get(in, x, y + 1, width, height);
      OCTET b = get(in, x, y - 1, width, height);

      set(out, fmin(cur, fmin(l, fmin(r, fmin(t, b)))), x, y, width, height);
    }
  }
}

void fermeture(OCTET *in, OCTET *out, int width, int height) {
  dilatation(in, out, width, height);
  OCTET *temp;
  allocation_tableau(temp, OCTET, width * height);
  fill_pgm(out, temp, width * height);
  erosion(temp, out, width, height);
}

void ouverture(OCTET *in, OCTET *out, int width, int height) {
  erosion(in, out, width, height);
  OCTET *temp;
  allocation_tableau(temp, OCTET, width * height);
  fill_pgm(out, temp, width * height);
  dilatation(temp, out, width, height);
}

void blur(OCTET *in, OCTET *out, int width, int height, int radius,
          int passes) {
  for (int i = 0; i < passes; i++) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int sum = 0;
        int l = 0;
        for (int rx = -radius; rx <= radius; rx++) {
          for (int ry = -radius; ry <= radius; ry++) {
            sum += get(in, x + rx, y + ry, width, height);
            l++;
          }
        }
        set(out, sum / l, x, y, width, height);
      }
    }
    OCTET *p = in;
    in = out;
    out = p;
  }
}

void gradient(OCTET *in, OCTET *out, int width, int height) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      OCTET pixel = get(in, x, y, width, height);
      OCTET right_pixel = get(in, x + 1, y, width, height);
      OCTET down_pixel = get(in, x, y + 1, width, height);

      OCTET dx = abs(right_pixel - pixel);
      OCTET dy = abs(down_pixel - pixel);

      set(out, sqrt(dx * dx + dy * dy), x, y, width, height);
    }
  }
}

typedef struct RGB RGB;
struct RGB {
  OCTET r;
  OCTET g;
  OCTET b;
};

RGB get_rgb(OCTET *in, int x, int y, int width, int height) {
  x = fmax(0, fmin(x, width));
  y = fmax(0, fmin(y, height));

  struct RGB rgb;
  rgb.r = in[y * width + x];
  rgb.g = in[y * width + x + 1];
  rgb.b = in[y * width + x + 2];
  return rgb;
}

void set_rgb(OCTET *out, RGB pixel, int x, int y, int width, int height) {
  x = fmax(0, fmin(x, width));
  y = fmax(0, fmin(y, height));

  out[y * width + x] = pixel.r;
  out[y * width + x + 1] = pixel.g;
  out[y * width + x + 2] = pixel.b;
}
