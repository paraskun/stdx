#include <errno.h>
#include <stdx/cut.h>

#include "pque.h"

static inline void swap(struct icut* c, int a, int b) {
  int t = c->dat[a];

  c->dat[a] = c->dat[b];
  c->dat[b] = t;
}

int ipque_fixu(struct icut* q, int i) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  int p = PQUE_P(i);

  while (i > 0 && q->cmp.call(q->cmp.ctx, 2, q->dat[i], q->dat[p]) == -1) {
    swap(q, p, i);

    i = p;
    p = PQUE_P(i);
  }

  return 0;
}

int ipque_fixd(struct icut* q, int i) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (i >= q->len) {
    errno = ERANGE;
    return -1;
  }

  int l = PQUE_L(i);
  int r = PQUE_R(i);
  int m;

  if (l < q->len && q->cmp.call(q->cmp.ctx, 2, q->dat[l], q->dat[i]) == -1)
    m = l;
  else
    m = i;

  if (r < q->len && q->cmp.call(q->cmp.ctx, 2, q->dat[r], q->dat[m]) == -1)
    m = r;

  if (m != i) {
    swap(q, m, i);

    return ipque_fixd(q, m);
  }

  return 0;
}

int ipque_fix(struct icut* q) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  for (int i = q->len / 2 - 1;; --i) {
    if (ipque_fixd(q, i))
      return -1;

    if (i == 0)
      break;
  }

  return 0;
}

int ipque_add(struct icut* q, int e) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (icut_add(q, e))
    return -1;

  return ipque_fixu(q, q->len - 1);
}

int ipque_ext(struct icut* q, int* e) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (q->len == 0) {
    errno = ENOENT;
    return -1;
  }

  *e = q->dat[0];
  swap(q, 0, q->len - 1);
  q->len -= 1;

  if (q->len != 0)
    return ipque_fixd(q, 0);

  return 0;
}

int ipque_srt(struct icut* q) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (q->len == 0)
    return 0;

  int len = q->len;

  for (int i = q->len - 1; i > 0; --i) {
    swap(q, 0, i);
    q->len -= 1;
    ipque_fixd(q, 0);
  }

  q->len = len;

  return 0;
}
