#ifndef STDX_CUT_H
#define STDX_CUT_H

#include <stdx/cmp.h>

struct icut;

int icut_ini(struct icut** h);
int icut_cls(struct icut** h);

int icut_cov(struct icut* c, int* beg, int* end);
int icut_mov(struct icut* c, int* s, uint len);

int icut_shr(struct icut* c);
int icut_exp(struct icut* c, uint cap);

int icut_add(struct icut* c, int e);
int icut_set(struct icut* c, uint i, int e);

int icut_get(struct icut* c, uint i, int* e);
int icut_srt(struct icut* c, icmp cmp);

uint icut_len(struct icut* c);
uint icut_cap(struct icut* c);

#endif  // STDX_CUT_H
