#ifndef STDX_CAP_H
#define STDX_CAP_H

typedef const char* str;

struct vcap {
  void (*call)(void*, int, ...);
  void* ctx;
};

struct icap {
  int (*call)(void*, int, ...);
  void* ctx;
};

struct ucap {
  int (*call)(void*, int, ...);
  void* ctx;
};

struct dcap {
  double (*call)(void*, int, ...);
  void* ctx;
};

#define cap(X, c) {.call = X, .ctx = (void*)c}

int iasc(void*, int, ...);
int idsc(void*, int, ...);

int uasc(void*, int, ...);
int udsc(void*, int, ...);

int dasc(void*, int, ...);
int ddsc(void*, int, ...);

int pasc(void*, int, ...);
int pdsc(void*, int, ...);

#endif  // STDX_CAP_H
