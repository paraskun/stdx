#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdx/cap.h>
#include <stdx/pque.h>
#include <string.h>

int pcut_new(struct pcut* c, int n, ...) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  c->cap = 0;
  c->len = 0;
  c->own = false;
  c->ctl = false;
  c->cmp.call = &pasc;
  c->cmp.ctx = nullptr;
  c->anc.call = nullptr;
  c->anc.ctx = nullptr;
  c->dat = nullptr;

  if (n == 0)
    return 0;

  pcut_exp(c, n);

  va_list arg;
  va_start(arg, n);

  for (int i = 0; i < n; ++i)
    pcut_add(c, va_arg(arg, void*));

  va_end(arg);

  return 0;
}

int pcut_cls(struct pcut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat) {
    if (c->ctl)
      for (int i = 0; i < c->len; ++i)
        free(c->dat[i]);

    if (c->own)
      free(c->dat);
  }

  return 0;
}

int pcut_cov(struct pcut* c, void** s, int len) {
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

int pcut_mov(struct pcut* c, void** s, int len) {
  if (!c || !s) {
    errno = EINVAL;
    return -1;
  }

  if (c->dat) {
    if (c->ctl)
      for (int i = 0; i < c->len; ++i)
        free(c->dat[i]);

    if (c->own)
      free(c->dat);
  }

  c->own = true;
  c->cap = len;
  c->len = len;
  c->dat = s;

  return 0;
}

int pcut_shr(struct pcut* c) {
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

  void** n = realloc(c->dat, sizeof(void*) * c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = c->len;
  c->dat = n;

  return 0;
}

int pcut_exp(struct pcut* c, int cap) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (cap <= c->cap)
    return 0;

  if (!c->dat || !c->own) {
    void** n = malloc(sizeof(void*) * cap);

    if (!n) {
      errno = ENOMEM;
      return -1;
    }

    c->cap = cap;
    c->own = true;

    if (c->dat)
      memcpy(n, c->dat, sizeof(void*) * c->len);

    c->dat = n;

    return 0;
  }

  void** n = realloc(c->dat, sizeof(void*) * cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = cap;
  c->dat = n;

  return 0;
}

int pcut_dev(struct pcut* c, int len) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (len > c->cap)
    if (pcut_exp(c, len))
      return -1;

  memset(c->dat + c->len, 0, sizeof(void*) * (len - c->len));
  c->len = len;

  return 0;
}

int pcut_add(struct pcut* c, void* e) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (c->len == c->cap)
    if (pcut_exp(c, (c->cap + 1) * 2))
      return -1;

  c->dat[c->len++] = e;

  if (c->anc.call)
    c->anc.call(c->anc.ctx, 3, e, -1, c->len - 1);

  return 0;
}

int pcut_srt(struct pcut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (ppque_fix(c))
    return -1;

  return ppque_srt(c);
}
