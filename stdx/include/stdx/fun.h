#ifndef STDX_FUN_H
#define STDX_FUN_H

struct fun {
  void* ctx;
  void (*call)(void*);
};

#define fun(X, Y) (struct fun){.ctx = &X, .call = (void (*)(void*))&Y}

#endif  // STDX_FUN_H
