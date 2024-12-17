#ifndef STDX_ANC_H
#define STDX_ANC_H

#include <stdx/cmp.h>

typedef int (*ianc)(int, uint);
typedef int (*uanc)(uint, uint);
typedef int (*fanc)(float, uint);
typedef int (*danc)(double, uint);
typedef int (*panc)(void*, uint);

#endif  // STDX_ANC_H
