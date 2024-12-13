#include <stdx/cmp.h>

#define ASC(a, b)       \
  if (a < b) return 1;  \
  if (a > b) return -1; \
  return 0;

#define DSC(a, b)       \
  if (a > b) return 1;  \
  if (a < b) return -1; \
  return 0;

int iasc(int a, int b) {
  ASC(a, b)
}

int idsc(int a, int b) {
  DSC(a, b);
}

int uasc(uint a, uint b) {
  ASC(a, b)
}

int udsc(uint a, uint b) {
  DSC(a, b)
}

int fasc(float a, float b) {
  ASC(a, b)
}

int fdsc(float a, float b) {
  DSC(a, b)
}

int dasc(double a, double b) {
  ASC(a, b)
}

int ddsc(double a, double b) {
  DSC(a, b)
}
