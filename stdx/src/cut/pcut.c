#include <errno.h>
#include <stdlib.h>
#include <stdx.h>
#include <string.h>

#include "../cut.h"

int pcut_new(struct pcut** h) {
  if (!h) {
    errno = EINVAL;
    return -1;
  }

  struct pcut* c = malloc(sizeof(struct pcut));

  if (!c) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = 0;
  c->len = 0;
  c->ctl = false;
  c->cmp = &pasc;
  c->anc = nullptr;
  c->data = nullptr;

  *h = c;

  return 0;
}

int pcut_cls(struct pcut** h) {
  if (!h || !(*h)) {
    errno = EINVAL;
    return -1;
  }

  struct pcut* c = *h;

  if (c->data && c->ctl)
    free(c->data);

  free(c);
  *h = nullptr;

  return 0;
}

int pcut_cov(struct pcut* c, void** beg, void** end) {
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

int pcut_mov(struct pcut* c, void** s, uint len) {
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

int pcut_shr(struct pcut* c) {
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

  void** n = realloc(c->data, sizeof(void*) * c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = c->len;
  c->data = n;

  return 0;
}

int pcut_exp(struct pcut* c, uint cap) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (cap <= c->cap)
    return 0;

  if (!c->data || !c->ctl) {
    void** n = malloc(sizeof(void*) * cap);

    if (!n) {
      errno = ENOMEM;
      return -1;
    }

    c->cap = cap;
    c->ctl = true;

    if (c->data)
      memcpy(n, c->data, sizeof(void*) * c->len);

    c->data = n;

    return 0;
  }

  void** n = realloc(c->data, sizeof(void*) * cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap = cap;
  c->data = n;

  return 0;
}

int pcut_dev(struct pcut* c, uint len) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (len > c->cap)
    if (pcut_exp(c, len))
      return -1;

  memset(c->data + c->len, 0, sizeof(void*) * (len - c->len));
  c->len = len;

  return 0;
}

int pcut_cmp(struct pcut* c, pcmp cmp) {
  if (!c || !cmp) {
    errno = EINVAL;
    return -1;
  }

  c->cmp = cmp;

  return 0;
}

int pcut_anc(struct pcut* c, panc anc) {
  if (!c || !anc) {
    errno = EINVAL;
    return -1;
  }

  c->anc = anc;

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

  c->data[c->len++] = e;

  if (c->anc)
    c->anc(e, c->len - 1);

  return 0;
}

int pcut_set(struct pcut* c, uint i, void* e) {
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

int pcut_get(struct pcut* c, uint i, void** e) {
  if (!c || !e || i >= c->len) {
    errno = EINVAL;
    return -1;
  }

  *e = c->data[i];

  return 0;
}

int pcut_pub(struct pcut* c, void*** e) {
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

int pcut_srt(struct pcut* c) {
  if (!c) {
    errno = EINVAL;
    return -1;
  }

  if (pque_fix(c))
    return -1;

  return pque_srt(c);
}

uint pcut_len(struct pcut* c) {
  if (!c) {
    errno = EINVAL;
    return 0;
  }

  return c->len;
}

uint pcut_cap(struct pcut* c) {
  if (!c) {
    errno = EINVAL;
    return 0;
  }

  return c->cap;
}
