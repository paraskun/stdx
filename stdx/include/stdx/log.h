#ifndef STDX_LOG_H
#define STDX_LOG_H

#include <stdx/cmp.h>

#define L -1
#define I 0
#define R 1

struct ilog;

int ilog_new(struct ilog** h);
int ilog_cls(struct ilog** h);

int ilog_cmp(struct ilog* l, icmp cmp);
int ilog_srt(struct ilog* l, bool srt);
int ilog_dup(struct ilog* l, bool dup);

int ilog_add(struct ilog* l, int e);
int ilog_ins(struct ilog* l, int e, int d);
int ilog_pop(struct ilog* l, int* e);

int ilog_beg(struct ilog* l, int* e);
int ilog_end(struct ilog* l, int* e);
int ilog_rst(struct ilog* l);
int ilog_adv(struct ilog* l, int* e);
int ilog_dec(struct ilog* l, int* e);

uint ilog_len(struct ilog* l);

#define log_new(X) _Generic((X),  \
    struct ilog**: ilog_new       \
    )(X)

#define log_cls(X) _Generic((X),  \
    struct ilog**: ilog_cls       \
    )(X)

#define log_cmp(X, c) _Generic((X), \
    struct ilog*: ilog_cmp          \
    )(X, c)

#define log_srt(X, s) _Generic((X), \
    struct ilog*: ilog_srt          \
    )(X, s)

#define log_dup(X, d) _Generic((X), \
    struct ilog*: ilog_dup          \
    )(X, d)

#define log_add(X, e) _Generic((X), \
    struct ilog*: ilog_add          \
    )(X, e)

#define log_ins(X, e, d) _Generic((X),  \
    struct ilog*: ilog_ins              \
    )(X, e, d)

#define log_pop(X, e) _Generic((X), \
    struct ilog*: ilog_pop          \
    )(X, e)

#define log_beg(X, e) _Generic((X), \
    struct ilog*: ilog_beg          \
    )(X, e)

#define log_end(X, e) _Generic((X), \
    struct ilog*: ilog_end          \
    )(X, e)

#define log_rst(X) _Generic((X),  \
    struct ilog*: ilog_rst        \
    )(X)

#define log_adv(X, e) _Generic((X), \
    struct ilog*: ilog_adv          \
    )(X, e)

#define log_dec(X, e) _Generic((X), \
    struct ilog*: ilog_dec          \
    )(X, e)

#define log_len(X) _Generic((X),  \
    struct ilog*: ilog_len        \
    )(X)

#endif  // STDX_LOG_H
