#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdx/cut.h>
#include <stdx/pque.h>
#include <string.h>

int icut_new(struct icut* c, int n, ...) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  c->cap = 0;
  c->len = 0;
  c->own = false;
  c->cmp.call = &iasc;
  c->cmp.ctx = nullptr;
  c->anc.call = nullptr;
  c->anc.ctx = nullptr;
  c->dat = nullptr;

  if (n == 0)
    return 0;

  icut_exp(c, n);

  va_list arg;
  va_start(arg, n);

  for (int i = 0; i < n; ++i)
    icut_add(c, va_arg(arg, int));

  va_end(arg);

  return 0;
}

int icut_cls(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat && c->own)
    free(c->dat);

  return 0;
}

int icut_cov(struct icut* c, int* s, int len) {
  if (!c || !s || len == 0) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat && c->own)
    free(c->dat);

  c->own = false;
  c->cap = len;
  c->len = len;
  c->dat = s;

  return 0;
}

int icut_mov(struct icut* c, int* s, int len) {
  if (!c || !s) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat && c->own)
    free(c->dat);

  c->own = true;
  c->cap = len;
  c->len = len;
  c->dat = s;

  return 0;
}

int icut_shr(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (!c->own || c->len == c->cap)
    return 0;

  if (c->len == 0) {
    free(c->dat);

    c->cap = 0;
    c->own = false;
    c->dat = nullptr;

    return 0;
  }

  int* n = realloc(c->dat, sizeof(int) * c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = c->len;
  c->dat = n;

  return 0;
}

int icut_exp(struct icut* c, int cap) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (cap <= c->cap)
    return 0;

  if (!c->dat || !c->own) {
    int* n = malloc(sizeof(int) * cap);

    if (!n) {
      errno = ENOMEM;
      return -1;
    }

    c->cap = cap;
    c->own = true;

    if (c->dat)
      memcpy(n, c->dat, sizeof(int) * c->len);

    c->dat = n;

    return 0;
  }

  int* n = realloc(c->dat, sizeof(int) * cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = cap;
  c->dat = n;

  return 0;
}

int icut_dev(struct icut* c, int len) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (len > c->cap)
    if (icut_exp(c, len))
      return -1;

  memset(c->dat + c->len, 0, sizeof(int) * (len - c->len));
  c->len = len;

  return 0;
}

int icut_add(struct icut* c, int e) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->len == c->cap)
    if (icut_exp(c, (c->cap + 1) * 2))
      return -1;

  c->dat[c->len++] = e;

  if (c->anc.call)
    c->anc.call(c->anc.ctx, 3, e, -1, c->len - 1);

  return 0;
}

int icut_srt(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (ipque_fix(c))
    return -1;

  return ipque_srt(c);
}
