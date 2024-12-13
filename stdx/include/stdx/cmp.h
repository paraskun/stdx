#ifndef STDX_CMP_H
#define STDX_CMP_H

typedef unsigned int uint;

typedef int (*icmp)(int, int);
typedef int (*ucmp)(uint, uint);
typedef int (*fcmp)(float, float);
typedef int (*dcmp)(double, double);
typedef int (*pcmp)(void*, void*);

int iasc(int, int);
int idsc(int, int);

int uasc(uint, uint);
int udsc(uint, uint);

int fasc(float, float);
int fdsc(float, float);

int dasc(double, double);
int ddsc(double, double);

#endif  // STDX_CMP_H
