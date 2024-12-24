#ifndef STDX_FUN_H
#define STDX_FUN_H

typedef unsigned int uint;

struct vcap {
  void (*call)(void*, uint, ...);
  void* ctx;
};

struct icap {
  int (*call)(void*, uint, ...);
  void* ctx;
};

struct ucap {
  uint (*call)(void*, uint, ...);
  void* ctx;
};

struct dcap {
  double (*call)(void*, uint, ...);
  void* ctx;
};

#define cap(X, c) {.call = X, .ctx = (void*)c}

int iasc(void*, uint, ...);
int idsc(void*, uint, ...);

int uasc(void*, uint, ...);
int udsc(void*, uint, ...);

int dasc(void*, uint, ...);
int ddsc(void*, uint, ...);

int pasc(void*, uint, ...);
int pdsc(void*, uint, ...);

#endif  // STDX_FUN_H
