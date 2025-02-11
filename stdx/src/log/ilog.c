#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdx/log.h>

int ilog_new(struct ilog* l, int n, ...) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  l->len = 0;
  l->srt = false;
  l->dup = true;
  l->cmp.call = &iasc;
  l->cmp.ctx = nullptr;
  l->beg = nullptr;
  l->end = nullptr;
  l->itr = nullptr;

  if (n == 0)
    return 0;

  va_list arg;
  va_start(arg, n);

  for (int i = 0; i < n; ++i)
    ilog_add(l, va_arg(arg, int));

  va_end(arg);

  return 0;
}

int ilog_cls(struct ilog* l) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  struct irec* r = l->beg;
  struct irec* t;

  while (r) {
    t = r;
    r = r->next;

    free(t);
  }

  return 0;
}

int ilog_add(struct ilog* l, int e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  l->itr = nullptr;

  if (l->srt || !l->dup)
    for (int i; ilog_adv(l, &i);) {
      int c = l->cmp.call(l->cmp.ctx, 2, i, e);

      if (c == 0 && !l->dup) {
        errno = EALREADY;
        return -1;
      }

      if (c != 1 && l->srt) {
        if (ilog_ins(l, e, L))
          return -1;

        l->itr = l->itr->prev;

        return 0;
      }
    }

  if (ilog_ins(l, e, R))
    return -1;

  if (!l->itr)
    l->itr = l->end;
  else
    l->itr = l->itr->next;

  return 0;
}

int ilog_ins(struct ilog* l, int e, int d) {
  if (!l || d < L || d > R) {
    errno = EINVAL;
    return -1;
  }

  if (d == I) {
    if (!l->itr) {
      errno = ENOENT;
      return -1;
    }

    l->itr->e = e;

    return 0;
  }

  struct irec* r = malloc(sizeof(struct irec));

  if (!r) {
    errno = ENOMEM;
    return -1;
  }

  r->e = e;

  switch (d) {
    case L:
      if (!l->itr || !l->itr->prev) {
        r->prev = nullptr;
        r->next = l->beg;
        l->beg = r;

        if (l->len == 0)
          l->end = r;
      } else {
        r->prev = l->itr->prev;
        r->next = l->itr;
        l->itr->prev = r;
      }

      break;
    case R:
      if (!l->itr || !l->itr->next) {
        r->next = nullptr;
        r->prev = l->end;
        l->end = r;

        if (l->len == 0)
          l->beg = r;
      } else {
        r->next = l->itr->next;
        r->prev = l->itr;
        l->itr->next = r;
      }
  }

  l->len += 1;

  return 0;
}

int ilog_pop(struct ilog* l, int* e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  struct irec* r = l->itr;

  if (!r) {
    errno = ENOENT;
    return -1;
  }

  l->itr = r->prev;
  l->len -= 1;

  if (e)
    *e = r->e;

  if (!r->prev)
    l->beg = r->next;
  else
    r->prev->next = r->next;

  if (!r->next)
    l->end = r->prev;
  else
    r->next->prev = r->prev;

  free(r);

  return 0;
}

int ilog_beg(struct ilog* l, int* e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  l->itr = l->beg;

  if (!l->itr)
    return 0;

  if (e)
    *e = l->itr->e;

  return 1;
}

int ilog_end(struct ilog* l, int* e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  l->itr = l->end;

  if (!l->itr)
    return 0;

  if (e)
    *e = l->itr->e;

  return 1;
}

int ilog_rst(struct ilog* l) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  l->itr = nullptr;

  return 0;
}

int ilog_adv(struct ilog* l, int* e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  if (!l->itr) {
    l->itr = l->beg;

    if (!l->itr)
      return 0;
  } else {
    if (!l->itr->next)
      return 0;

    l->itr = l->itr->next;
  }

  if (e)
    *e = l->itr->e;

  return 1;
}

int ilog_dec(struct ilog* l, int* e) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  if (!l->itr) {
    l->itr = l->end;

    if (!l->itr)
      return 0;
  } else {
    if (!l->itr->prev)
      return 0;

    l->itr = l->itr->prev;
  }

  if (e)
    *e = l->itr->e;

  return 1;
}

int ilog_len(struct ilog* l) {
  if (!l) {
    errno = EINVAL;
    return -1;
  }

  return l->len;
}
