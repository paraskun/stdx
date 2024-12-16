#include <errno.h>
#include <stdlib.h>
#include <stdx/cut.h>
#include <string.h>

struct icut {
  uint cap;
  uint len;
  bool ctl;

  int* data;
};

int icut_ini(struct icut** h) {
  if (!h) {
    errno = EINVAL;
    return -1;
  }

  struct icut* c = malloc(sizeof(struct icut));

  if (!c) {
    errno = ENOMEM;
    return -1;
  }

  c->cap  = 0;
  c->len  = 0;
  c->ctl  = false;
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

  c->ctl  = false;
  c->cap  = end - beg + 1;
  c->len  = c->cap;
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

  c->ctl  = true;
  c->cap  = len;
  c->len  = len;
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

    c->cap  = 0;
    c->ctl  = false;
    c->data = nullptr;

    return 0;
  }

  int* n = realloc(c->data, c->len);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  c->cap  = c->len;
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
    c->data = malloc(sizeof(int) * cap);

    if (!c->data) {
      errno = ENOMEM;
      return -1;
    }

    memset(c->data, 0, sizeof(int) * cap);

    c->cap = cap;
    c->ctl = true;

    return 0;
  }

  int* n = realloc(c->data, cap);

  if (!n) {
    errno = ENOMEM;
    return -1;
  }

  memset(c->data + c->len, 0, sizeof(int) * (cap - c->len));

  c->cap  = cap;
  c->data = n;

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

  return 0;
}

int icut_set(struct icut* c, uint i, int e) {
  if (!c || i >= c->len) {
    errno = EINVAL;
    return -1;
  }

  c->data[i] = e;

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

int icut_srt(struct icut*, icmp) {
  // todo: pque sort here
  
  errno = ENOSYS;
  return -1;
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
