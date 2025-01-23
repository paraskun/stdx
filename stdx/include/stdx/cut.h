#ifndef STDX_CUT_H
#define STDX_CUT_H

#include <stdx/cap.h>

struct icut {
  uint cap;
  uint len;
  bool own;

  struct icap cmp;
  struct vcap anc;

  int* dat;
};

int icut_new(struct icut* c, uint n, ...);
int icut_cls(struct icut* c);

int icut_cov(struct icut* c, int* s, uint len);
int icut_mov(struct icut* c, int* s, uint len);

int icut_shr(struct icut* c);
int icut_exp(struct icut* c, uint cap);
int icut_dev(struct icut* c, uint len);

int icut_add(struct icut* c, int e);
int icut_srt(struct icut* c);

struct dcut {
  uint cap;
  uint len;
  bool own;

  struct icap cmp;
  struct vcap anc;

  double* dat;
};

int dcut_new(struct dcut* c, uint n, ...);
int dcut_cls(struct dcut* c);

int dcut_cov(struct dcut* c, double* s, uint len);
int dcut_mov(struct dcut* c, double* s, uint len);

int dcut_shr(struct dcut* c);
int dcut_exp(struct dcut* c, uint cap);
int dcut_dev(struct dcut* c, uint len);

int dcut_add(struct dcut* c, double e);
int dcut_srt(struct dcut* c);

struct pcut {
  uint cap;
  uint len;
  bool own;
  bool ctl;

  struct icap cmp;
  struct vcap anc;

  void** dat;
};

int pcut_new(struct pcut* c, uint n, ...);
int pcut_cls(struct pcut* c);

int pcut_cov(struct pcut* c, void** s, uint len);
int pcut_mov(struct pcut* c, void** s, uint len);

int pcut_shr(struct pcut* c);
int pcut_exp(struct pcut* c, uint cap);
int pcut_dev(struct pcut* c, uint len);

int pcut_add(struct pcut* c, void* e);
int pcut_srt(struct pcut* c);

#define cut_new(...) cut_new_var(__VA_ARGS__, 0, 0)

#define cut_new_var(X, n, ...) _Generic((X), \
    struct icut*: icut_new,                  \
    struct dcut*: dcut_new,                  \
    struct pcut*: pcut_new                   \
    )(X, n, __VA_ARGS__)

#define cut_cls(X) _Generic((X), \
    struct icut*: icut_cls,      \
    struct dcut*: dcut_cls,      \
    struct pcut*: pcut_cls       \
    )(X)

#define cut_cov(X, s, l) _Generic((X),  \
    struct icut*: icut_cov,             \
    struct dcut*: dcut_cov,             \
    struct pcut*: pcut_cov              \
    )(X, s, l)

#define cut_mov(X, s, l) _Generic((X),  \
    struct icut*: icut_mov,             \
    struct dcut*: dcut_mov,             \
    struct pcut*: pcut_mov              \
    )(X, s, l)

#define cut_shr(X) _Generic((X),  \
    struct icut*: icut_shr,       \
    struct dcut*: dcut_shr,       \
    struct pcut*: pcut_shr        \
    )(X)

#define cut_exp(X, c) _Generic((X), \
    struct icut*: icut_exp,         \
    struct dcut*: dcut_exp,         \
    struct pcut*: pcut_exp          \
    )(X, c)

#define cut_dev(X, l) _Generic((X), \
    struct icut*: icut_dev,         \
    struct dcut*: dcut_dev,         \
    struct pcut*: pcut_dev          \
    )(X, l)

#define cut_add(X, e) _Generic((X), \
    struct icut*: icut_add,         \
    struct dcut*: dcut_add,         \
    struct pcut*: pcut_add          \
    )(X, e)

#define cut_srt(X) _Generic((X),  \
    struct icut*: icut_srt,       \
    struct dcut*: dcut_srt,       \
    struct pcut*: pcut_srt        \
    )(X)

#endif  // STDX_CUT_H
