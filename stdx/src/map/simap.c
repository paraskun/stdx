#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <stdx/map.h>

static int gen_lvl() {
  int lvl = 0;

  while ((double)rand() / RAND_MAX < STDX_MAP_PBT_NUM && lvl < STDX_MAP_MAX_LVL)
    lvl += 1;

  return lvl;
}

int simap_new(struct simap* m) {
  if (!m) {
    errno = EINVAL;
    return -1;
  }

  m->len = 0;
  m->lvl = -1;
  m->beg.fwd = malloc(sizeof(struct sirec*) * STDX_MAP_MAX_LVL);

  if (!m->beg.fwd) {
    errno = ENOMEM;
    return -1;
  }

  return 0;
}

int simap_cls(struct simap* m) {
  if (!m) {
    errno = EINVAL;
    return -1;
  }

  free(m->beg.fwd);

  return 0;
}

int simap_get(struct simap* m, const char* k, int* v) {
  if (!m || !v) {
    errno = EINVAL;
    return -1;
  }

  for (int l = m->lvl; l >= 0; --l) {
    struct sirec* i = &m->beg;

    while (i->fwd[l] && i->fwd[l]->k < k)
      i = i->fwd[l];

    if (i->fwd[l] && i->fwd[l]->k == k) {
      *v = i->v;
      return 0;
    }
  }

  errno = ENOENT;
  return -1;
}

int simap_put(struct simap* m, const char* k, int v) {
  if (!m) {
    errno = EINVAL;
    return -1;
  }

  int lvl = gen_lvl();
  struct sirec** spl = malloc(sizeof(struct sirec*) * lvl);

  if (!spl) {
    errno = ENOMEM;
    return -1;
  }

  memset(spl, 0, sizeof(struct sirec*) * lvl);

  for (int l = m->lvl; l >= 0; --l) {
    if (!i) {
      continue;
    }

    if (i->k == k) {
      i->v = v;
      free(spl);
      return 0;
    }

    while (i->fwd[l] && i->fwd[l]->k < i->k)
      i = i->fwd[l];

    if (!i->fwd[l] || i->fwd[l]->k > i->k) {
      spl[l] = i;
      continue;
    }

    i->fwd[l]->v = v;
    free(spl);
    return 0;
  }

  if (lvl > m->lvl) {
    if (m->beg) {
      struct sirec** n = realloc(m->beg, sizeof(struct sirec*) * lvl);

      if (!n) {
        free(spl);
        errno = ENOMEM;
        return -1;
      }

      m->beg = n;
    } else {
      m->beg = malloc(sizeof(struct sirec*) * lvl);

      if (!m->beg) {
        free(spl);
        errno = ENOMEM;
        return -1;
      }
    }

    memset(m->beg[m->lvl], 0, sizeof(struct sirec*) * (lvl - m->lvl));

    m->lvl = lvl;
  }

  struct sirec* n = malloc(sizeof(struct sirec));

  if (!n) {
    free(spl);
    errno = ENOMEM;
    return -1;
  }

  n->lvl = lvl;
  n->k = k;
  n->v = v;
  n->fwd = malloc(sizeof(struct sirec*) * lvl);

  if (!n->fwd) {
    free(n);
    free(spl);

    errno = ENOMEM;
    return -1;
  }

  for (int l = 0; l < lvl; ++l)
    if (!spl[l]) {
      n->fwd[l] = nullptr;
      m->beg[l] = n;
    } else {
      n->fwd[l] = spl[l]->fwd[l];
      spl[l]->fwd[l] = n;
    }

  return 0;
}
