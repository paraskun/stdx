#include <errno.h>
#include <stdx.h>

#include "../cut.h"
#include "../pque.h"

static inline void swap(struct pcut* c, uint a, uint b) {
  void* t = c->data[a];

  c->data[a] = c->data[b];
  c->data[b] = t;
}

int ppque_fixu(struct pcut* q, uint i) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  uint p = PQUE_P(i);

  while (i > 0 && q->cmp(q->data[i], q->data[p]) == -1) {
    swap(q, p, i);

    i = p;
    p = PQUE_P(i);
  }

  return 0;
}

int ppque_fixd(struct pcut* q, uint i) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (i >= q->len) {
    errno = ERANGE;
    return -1;
  }

  uint l = PQUE_L(i);
  uint r = PQUE_R(i);
  uint m;

  if (l < q->len && q->cmp(q->data[l], q->data[i]) == -1)
    m = l;
  else
    m = i;

  if (r < q->len && q->cmp(q->data[r], q->data[m]) == -1)
    m = r;

  if (m != i) {
    swap(q, m, i);

    return ppque_fixd(q, m);
  }

  return 0;
}

int ppque_fix(struct pcut* q) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  for (uint i = q->len / 2 - 1;; --i) {
    if (ppque_fixd(q, i))
      return -1;

    if (i == 0)
      break;
  }

  return 0;
}

int ppque_add(struct pcut* q, void* e) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (pcut_add(q, e))
    return -1;

  return ppque_fixu(q, q->len - 1);
}

int ppque_ext(struct pcut* q, void** e) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (q->len == 0) {
    errno = ENOENT;
    return -1;
  }

  *e = q->data[0];
  swap(q, 0, q->len - 1);
  q->len -= 1;

  if (q->len != 0)
    return ppque_fixd(q, 0);

  return 0;
}

int ppque_srt(struct pcut* q) {
  if (!q) {
    errno = EINVAL;
    return -1;
  }

  if (q->len == 0)
    return 0;

  for (uint i = q->len - 1; i > 0; --i) {
    swap(q, 0, i);
    q->len -= 1;
    ppque_fixd(q, 0);
  }

  return 0;
}
