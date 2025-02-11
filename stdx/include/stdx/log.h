#ifndef STDX_LOG_H
#define STDX_LOG_H

#include <stdx/cap.h>

#define L -1
#define I 0
#define R 1

struct irec {
  int e;

  struct irec* next;
  struct irec* prev;
};

struct ilog {
  int len;
  bool srt;
  bool dup;

  struct icap cmp;

  struct irec* beg;
  struct irec* end;

  struct irec* itr;
};

int ilog_new(struct ilog* l, int n, ...);
int ilog_cls(struct ilog* l);

int ilog_add(struct ilog* l, int e);
int ilog_ins(struct ilog* l, int e, int d);
int ilog_pop(struct ilog* l, int* e);

int ilog_beg(struct ilog* l, int* e);
int ilog_end(struct ilog* l, int* e);
int ilog_rst(struct ilog* l);
int ilog_adv(struct ilog* l, int* e);
int ilog_dec(struct ilog* l, int* e);

#define log_new(...) log_new_var(__VA_ARGS__, 0, 0)

#define log_new_var(X, n, ...) _Generic((X), \
    struct ilog*: ilog_new,                  \
    )(X, n, __VA_ARGS__)

#define log_cls(X) _Generic((X), \
    struct ilog*: ilog_cls       \
    )(X)

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

#endif  // STDX_LOG_H
