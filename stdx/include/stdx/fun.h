#ifndef STDX_FUN_H
#define STDX_FUN_H

struct clsr {
  void* ctx;
  void (*call)(void*);
};

#define clsr(X, Y) (struct clsr){.ctx = &X, .call = (void (*)(void*))&Y}

#endif  // STDX_FUN_H
