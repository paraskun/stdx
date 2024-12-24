#include <stdarg.h>
#include <stdx/cap.h>

#define ASC(a, b)       \
  if (a < b) return 1;  \
  if (a > b) return -1; \
  return 0

#define DSC(a, b)       \
  if (a > b) return 1;  \
  if (a < b) return -1; \
  return 0

int iasc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  int a = va_arg(arg, int);
  int b = va_arg(arg, int);

  va_end(arg);

  ASC(a, b);
}

int idsc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  int a = va_arg(arg, int);
  int b = va_arg(arg, int);

  va_end(arg);

  DSC(a, b);
}

int uasc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  uint a = va_arg(arg, uint);
  uint b = va_arg(arg, uint);

  va_end(arg);

  ASC(a, b);
}

int udsc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  uint a = va_arg(arg, uint);
  uint b = va_arg(arg, uint);

  va_end(arg);

  DSC(a, b);
}

int dasc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  double a = va_arg(arg, double);
  double b = va_arg(arg, double);

  va_end(arg);

  ASC(a, b);
}

int ddsc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  double a = va_arg(arg, double);
  double b = va_arg(arg, double);

  va_end(arg);

  DSC(a, b);
}

int pasc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  void* a = va_arg(arg, void*);
  void* b = va_arg(arg, void*);

  va_end(arg);

  ASC(a, b);
}

int pdsc(void*, uint n, ...) {
  if (n < 2)
    return 0;

  va_list arg;
  va_start(arg, n);

  void* a = va_arg(arg, void*);
  void* b = va_arg(arg, void*);

  va_end(arg);

  DSC(a, b);
}
