#ifndef STDX_PQUE_H
#define STDX_PQUE_H

#include <stdx/cut.h>

int ipque_fixu(struct icut* q, int i);
int ipque_fixd(struct icut* q, int i);

int ipque_fix(struct icut* q);
int ipque_add(struct icut* q, int e);
int ipque_ext(struct icut* q, int* e);
int ipque_srt(struct icut* q);

int dpque_fixu(struct dcut* q, int i);
int dpque_fixd(struct dcut* q, int i);

int dpque_fix(struct dcut* q);
int dpque_add(struct dcut* q, double e);
int dpque_ext(struct dcut* q, double* e);
int dpque_srt(struct dcut* q);

int ppque_fixu(struct pcut* q, int i);
int ppque_fixd(struct pcut* q, int i);

int ppque_fix(struct pcut* q);
int ppque_add(struct pcut* q, void* e);
int ppque_ext(struct pcut* q, void** e);
int ppque_srt(struct pcut* q);

#define pque_fixu(X, i) _Generic((X), \
    struct icut*: ipque_fixu,         \
    struct dcut*: dpque_fixu,         \
    struct pcut*: ppque_fixu          \
    )(X, i)

#define pque_fixd(X, i) _Generic((X), \
    struct icut*: ipque_fixd,         \
    struct dcut*: dpque_fixd,         \
    struct pcut*: ppque_fixd          \
    )(X, i)

#define pque_fix(X) _Generic((X), \
    struct icut*: ipque_fix,      \
    struct dcut*: dpque_fix,      \
    struct pcut*: ppque_fix       \
    )(X)

#define pque_add(X, e) _Generic((X),  \
    struct icut*: ipque_add,          \
    struct dcut*: dpque_add,          \
    struct pcut*: ppque_add           \
    )(X, e)

#define pque_ext(X, e) _Generic((X),  \
    struct icut*: ipque_ext,          \
    struct dcut*: dpque_ext,          \
    struct pcut*: ppque_ext           \
    )(X, e)

#define pque_srt(X) _Generic((X), \
    struct icut*: ipque_srt,      \
    struct dcut*: dpque_srt,      \
    struct pcut*: ppque_srt       \
    )(X)

#endif  // STDX_PQUE_H
