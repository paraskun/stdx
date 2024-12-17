#ifndef STDX_CUT_H
#define STDX_CUT_H

#include <stdx/anc.h>
#include <stdx/cmp.h>

struct icut;

int icut_new(struct icut** h);
int icut_cls(struct icut** h);

int icut_cov(struct icut* c, int* beg, int* end);
int icut_mov(struct icut* c, int* s, uint len);

int icut_shr(struct icut* c);
int icut_exp(struct icut* c, uint cap);
int icut_dev(struct icut* c, uint len);

int icut_cmp(struct icut* c, icmp cmp);
int icut_anc(struct icut* c, ianc anc);

int icut_add(struct icut* c, int e);
int icut_set(struct icut* c, uint i, int e);

int icut_get(struct icut* c, uint i, int* e);
int icut_pub(struct icut* c, int** e);
int icut_srt(struct icut* c);

uint icut_len(struct icut* c);
uint icut_cap(struct icut* c);

#define cut_new(X) _Generic((X),  \
    struct icut**: icut_new       \
    )(X)

#define cut_cls(X) _Generic((X),  \
    struct icut**: icut_cls       \
    )(X)

#define cut_cov(X, b, e) _Generic((X),  \
    struct icut*: icut_cov              \
    )(X, b, e)

#define cut_mov(X, s, l) _Generic((X),  \
    struct icut*: icut_mov              \
    )(X, s, l)

#define cut_shr(X) _Generic((X),  \
    struct icut*: icut_shr        \
    )(X)

#define cut_exp(X, c) _Generic((X), \
    struct icut*: icut_exp          \
    )(X, c)

#define cut_dev(X, l) _Generic((X), \
    struct icut*: icut_dev          \
    )(X, l)

#define cut_add(X, e) _Generic((X), \
    struct icut*: icut_add          \
    )(X, e)

#define cut_set(X, i, e) _Generic((X),  \
    struct icut*: icut_set              \
    )(X, i, e)

#define cut_get(X, i, e) _Generic((X),  \
    struct icut*: icut_get              \
    )(X, i, e)

#define cut_pub(X, e) _Generic((X), \
    struct icut*: icut_pub          \
    )(X, e)

#define cut_srt(X) _Generic((X),  \
    struct icut*: icut_srt        \
    )(X)

#define cut_len(X) _Generic((X),  \
    struct icut*: icut_len        \
    )(X)

#define cut_cap(X) _Generic((X),  \
    struct icut*: icut_cap        \
    )(X)

#endif  // STDX_CUT_H
