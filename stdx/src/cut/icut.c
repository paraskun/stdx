#include <errno.h>
#include <stdlib.h>
#include <stdx.h>
#include <string.h>

#include "../cut.h"

int icut_new(struct icut** h) {
  if (!h) {
    errno = EINVAL;
    return -1;
  }

  struct icut* c = malloc(sizeof(struct icut));

  if (!c) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = 0;
  c->len = 0;
  c->ctl = false;
  c->cmp = &iasc;
  c->anc = nullptr;
  c->data = nullptr;

  *h = c;

  return 0;
}

int icut_cls(struct icut** h) {
  if (!h || !(*h)) {
    errno = EINVAL;
    return -1;
  }

  struct icut* c = *h;

  if (c->data && c->ctl)
    free(c->data);

  free(c);
  *h = nullptr;

  return 0;
}

int icut_cov(struct icut* c, int* beg, int* end) {
  if (!c || !beg || !end) {
    errno = EINVAL;
    return -1;
  }

  if (c->data && c->ctl)
    free(c->data);

  c->ctl = false;
  c->cap = end - beg + 1;
  c->len = c->cap;
  c->data = beg;

  return 0;
}

int icut_mov(struct icut* c, int* s, uint len) {
  if (!c || !s) {
    errno = EINVAL;
    return -1;
  }

  if (c->data && c->ctl)
    free(c->data);

  c->ctl = true;
  c->cap = len;
  c->len = len;
  c->data = s;

  return 0;
}

int icut_shr(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (!c->ctl || c->len == c->cap)
    return 0;

  if (c->len == 0) {
    free(c->data);

    c->cap = 0;
    c->ctl = false;
    c->data = nullptr;

    return 0;
  }

  int* n = realloc(c->data, sizeof(int) * c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = c->len;
  c->data = n;

  return 0;
}

int icut_exp(struct icut* c, uint cap) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (cap <= c->cap)
    return 0;

  if (!c->data || !c->ctl) {
    int* n = malloc(sizeof(int) * cap);

    if (!n) {
      errno = ENOMEM;
      return -1;
    }

    c->cap = cap;
    c->ctl = true;

    if (c->data)
      memcpy(n, c->data, sizeof(int) * c->len);

    c->data = n;

    return 0;
  }

  int* n = realloc(c->data, sizeof(int) * cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = cap;
  c->data = n;

  return 0;
}

int icut_dev(struct icut* c, uint len) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (len > c->cap)
    if (icut_exp(c, len))
      return -1;

  memset(c->data + c->len, 0, sizeof(int) * (len - c->len));
  c->len = len;

  return 0;
}

int icut_cmp(struct icut* c, icmp cmp) {
  if (!c || !cmp) {
    errno = EINVAL;
    return -1;
  }

  c->cmp = cmp;

  return 0;
}

int icut_anc(struct icut* c, ianc anc) {
  if (!c || !anc) {
    errno = EINVAL;
    return -1;
  }

  c->anc = anc;

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

  c->data[c->len++] = e;

  if (c->anc)
    c->anc(e, c->len - 1);

  return 0;
}

int icut_set(struct icut* c, uint i, int e) {
  if (!c || i >= c->len) {
    errno = EINVAL;
    return -1;
  }

  if (i >= c->len) {
    errno = ERANGE;
    return -1;
  }

  c->data[i] = e;

  if (c->anc)
    c->anc(e, i);

  return 0;
}

int icut_get(struct icut* c, uint i, int* e) {
  if (!c || !e || i >= c->len) {
    errno = EINVAL;
    return -1;
  }

  *e = c->data[i];

  return 0;
}

int icut_pub(struct icut* c, int** e) {
  if (!c || !e) {
    errno = EINVAL;
    return -1;
  }

  if (!c->data) {
    errno = ENOMEDIUM;
    return -1;
  }

  *e = c->data;

  return 0;
}

int icut_srt(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (pque_fix(c))
    return -1;

  return pque_srt(c);
}

uint icut_len(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return 0;
  }

  return c->len;
}

uint icut_cap(struct icut* c) {
  if (!c) {
    errno = EINVAL;
    return 0;
  }

  return c->cap;
}
