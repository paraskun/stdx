#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdx/cap.h>
#include <stdx/pque.h>
#include <string.h>

int dcut_new(struct dcut* c, int n, ...) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  c->cap = 0;
  c->len = 0;
  c->own = false;
  c->cmp.call = &dasc;
  c->cmp.ctx = nullptr;
  c->anc.call = nullptr;
  c->anc.ctx = nullptr;
  c->dat = nullptr;

  if (n == 0)
    return 0;

  dcut_exp(c, n);

  va_list arg;
  va_start(arg, n);

  for (int i = 0; i < n; ++i)
    dcut_add(c, va_arg(arg, double));

  va_end(arg);

  return 0;
}

int dcut_cls(struct dcut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat)
    if (c->own)
      free(c->dat);

  return 0;
}

int dcut_cov(struct dcut* c, double* s, int len) {
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

int dcut_mov(struct dcut* c, double* s, int len) {
  if (!c || !s) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat)
    if (c->own)
      free(c->dat);

  c->own = true;
  c->cap = len;
  c->len = len;
  c->dat = s;

  return 0;
}

int dcut_shr(struct dcut* c) {
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

  double* n = realloc(c->dat, sizeof(double) * c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = c->len;
  c->dat = n;

  return 0;
}

int dcut_exp(struct dcut* c, int cap) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (cap <= c->cap)
    return 0;

  if (!c->dat || !c->own) {
    double* n = malloc(sizeof(double) * cap);

    if (!n) {
      errno = ENOMEM;
      return -1;
    }

    c->cap = cap;
    c->own = true;

    if (c->dat)
      memcpy(n, c->dat, sizeof(double) * c->len);

    c->dat = n;

    return 0;
  }

  double* n = realloc(c->dat, sizeof(double) * cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = cap;
  c->dat = n;

  return 0;
}

int dcut_dev(struct dcut* c, int len) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (len > c->cap)
    if (dcut_exp(c, len))
      return -1;

  memset(c->dat + c->len, 0, sizeof(double) * (len - c->len));
  c->len = len;

  return 0;
}

int dcut_add(struct dcut* c, double e) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->len == c->cap)
    if (dcut_exp(c, (c->cap + 1) * 2))
      return -1;

  c->dat[c->len++] = e;

  if (c->anc.call)
    c->anc.call(c->anc.ctx, 3, e, -1, c->len - 1);

  return 0;
}

int dcut_srt(struct dcut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (dpque_fix(c))
    return -1;

  return dpque_srt(c);
}
