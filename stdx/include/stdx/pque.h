#ifndef STDX_PQUE_H
#define STDX_PQUE_H

#include <stdx/cut.h>

int ipque_fixu(struct icut* q, uint i);
int ipque_fixd(struct icut* q, uint i);

int ipque_fix(struct icut* q);

int ipque_add(struct icut* q, int e);
int ipque_ext(struct icut* q, int* e);
int ipque_srt(struct icut* q);

int ppque_fixu(struct pcut* q, uint i);
int ppque_fixd(struct pcut* q, uint i);

int ppque_fix(struct pcut* q);

int ppque_add(struct pcut* q, void* e);
int ppque_ext(struct pcut* q, void** e);
int ppque_srt(struct pcut* q);

#define pque_fixu(X, i) _Generic((X), \
    struct icut*: ipque_fixu,         \
    struct pcut*: ppque_fixu          \
    )(X, i)

#define pque_fixd(X, i) _Generic((X), \
    struct icut*: ipque_fixd,         \
    struct pcut*: ppque_fixd          \
    )(X, i)

#define pque_fix(X) _Generic((X), \
    struct icut*: ipque_fix,      \
    struct pcut*: ppque_fix       \
    )(X)

#define pque_add(X, e) _Generic((X),  \
    struct icut*: ipque_add,          \
    struct pcut*: ppque_add           \
    )(X, e)

#define pque_ext(X, e) _Generic((X),  \
    struct icut*: ipque_ext,          \
    struct pcut*: ppque_ext           \
    )(X, e)

#define pque_srt(X) _Generic((X), \
    struct icut*: ipque_srt,      \
    struct pcut*: ppque_srt       \
    )(X)

#endif  // STDX_PQUE_H
