#ifndef STDX_CUT_H
#define STDX_CUT_H

#include <stdx/anc.h>
#include <stdx/cmp.h>

struct icut;

int icut_new(struct icut** h, uint n, ...);
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

struct pcut;

int pcut_new(struct pcut** h, uint n, ...);
int pcut_cls(struct pcut** h);

int pcut_cov(struct pcut* c, void** beg, void** end);
int pcut_mov(struct pcut* c, void** s, uint len);

int pcut_shr(struct pcut* c);
int pcut_exp(struct pcut* c, uint cap);
int pcut_dev(struct pcut* c, uint len);

int pcut_cmp(struct pcut* c, pcmp cmp);
int pcut_anc(struct pcut* c, panc anc);

int pcut_add(struct pcut* c, void* e);
int pcut_set(struct pcut* c, uint i, void* e);

int pcut_get(struct pcut* c, uint i, void** e);
int pcut_pub(struct pcut* c, void*** e);
int pcut_srt(struct pcut* c);

uint pcut_len(struct pcut* c);
uint pcut_cap(struct pcut* c);

#define ZERO_DEFAULT_ZERO(F, _0, _1, ...) F(_0, _1, __VA_ARGS__)
#define ZERO_DEFAULT(...) ZERO_DEFAULT_ZERO(__VA_ARGS__, 0, 0)

#define cut_new(...) ZERO_DEFAULT(cut_new_exp, __VA_ARGS__)

#define cut_new_exp(X, n, ...) _Generic((X),  \
    struct icut**: icut_new,              \
    struct pcut**: pcut_new               \
    )(X, n, __VA_ARGS__)

#define cut_cls(X) _Generic((X),  \
    struct icut**: icut_cls,      \
    struct pcut**: pcut_cls       \
    )(X)

#define cut_cov(X, b, e) _Generic((X),  \
    struct icut*: icut_cov,             \
    struct pcut*: pcut_cov              \
    )(X, b, e)

#define cut_mov(X, s, l) _Generic((X),  \
    struct icut*: icut_mov,             \
    struct pcut*: pcut_mov              \
    )(X, s, l)

#define cut_shr(X) _Generic((X),  \
    struct icut*: icut_shr,       \
    struct pcut*: pcut_shr        \
    )(X)

#define cut_exp(X, c) _Generic((X), \
    struct icut*: icut_exp,         \
    struct pcut*: pcut_exp          \
    )(X, c)

#define cut_dev(X, l) _Generic((X), \
    struct icut*: icut_dev,         \
    struct pcut*: pcut_dev          \
    )(X, l)

#define cut_cmp(X, c) _Generic((X), \
    struct icut*: icut_cmp,         \
    struct pcut*: pcut_cmp          \
    )(X, c)

#define cut_anc(X, a) _Generic((X), \
    struct icut*: icut_anc,         \
    struct pcut*: pcut_anc          \
    )(X, a)

#define cut_add(X, e) _Generic((X), \
    struct icut*: icut_add,         \
    struct pcut*: pcut_add          \
    )(X, e)

#define cut_set(X, i, e) _Generic((X),  \
    struct icut*: icut_set,             \
    struct pcut*: pcut_set              \
    )(X, i, e)

#define cut_get(X, i, e) _Generic((X),  \
    struct icut*: icut_get,             \
    struct pcut*: pcut_get              \
    )(X, i, e)

#define cut_pub(X, e) _Generic((X), \
    struct icut*: icut_pub,         \
    struct pcut*: pcut_pub          \
    )(X, e)

#define cut_srt(X) _Generic((X),  \
    struct icut*: icut_srt,       \
    struct pcut*: pcut_srt        \
    )(X)

#define cut_len(X) _Generic((X),  \
    struct icut*: icut_len,       \
    struct pcut*: pcut_len        \
    )(X)

#define cut_cap(X) _Generic((X),  \
    struct icut*: icut_cap,       \
    struct pcut*: pcut_cap        \
    )(X)

#endif  // STDX_CUT_H
