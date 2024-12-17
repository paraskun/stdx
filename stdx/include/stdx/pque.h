#ifndef STDX_PQUE_H
#define STDX_PQUE_H

#include <stdx/cut.h>

int ipque_fixu(struct icut* q, uint i);
int ipque_fixd(struct icut* q, uint i);

int ipque_fix(struct icut* q);

int ipque_add(struct icut* q, int e);
int ipque_ext(struct icut* q, int* e);
int ipque_srt(struct icut* q);

#define pque_fixu(X, i) _Generic((X), \
    struct icut*: ipque_fixu          \
    )(X, i)

#define pque_fixd(X, i) _Generic((X), \
    struct icut*: ipque_fixd          \
    )(X, i)

#define pque_fix(X) _Generic((X), \
    struct icut*: ipque_fix       \
    )(X)

#define pque_add(X, e) _Generic((X),  \
    struct icut*: ipque_add           \
    )(X, e)

#define pque_ext(X, e) _Generic((X),  \
    struct icut*: ipque_ext           \
    )(X, e)

#define pque_srt(X) _Generic((X), \
    struct icut*: ipque_srt       \
    )(X)

#endif  // STDX_PQUE_H
