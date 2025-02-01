#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <stdx/map.h>

static int gen_lvl() {
  int lvl = 0;

  while ((double)rand() / RAND_MAX < STDX_MAP_LVL_PBT && lvl < STDX_MAP_LVL_MAX)
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
  m->beg.fwd = malloc(sizeof(struct sirec*) * STDX_MAP_LVL_MAX);

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

  struct sirec* i = m->beg.fwd[0];
  struct sirec* j = nullptr;

  while (i) {
    j = i->fwd[0];

    free(i->fwd);
    free(i);

    i = j;
  }

  free(m->beg.fwd);

  return 0;
}

int simap_get(const struct simap* m, str k, int* v) {
  if (!m || !v) {
    errno = EINVAL;
    return -1;
  }

  const struct sirec* i = &m->beg;

  for (int l = m->lvl; l >= 0; --l) {
    while (i->fwd[l] && strcmp(i->fwd[l]->k, k) < 0)
      i = i->fwd[l];

    if (i->fwd[l] && strcmp(i->fwd[l]->k, k) == 0) {
      *v = i->fwd[l]->v;
      return 0;
    }
  }

  errno = ENOENT;
  return -1;
}

int simap_put(struct simap* m, str k, int v) {
  if (!m) {
    errno = EINVAL;
    return -1;
  }

  struct sirec* rec = malloc(sizeof(struct sirec));
  struct sirec* fwd = nullptr;

  if (!rec) {
    errno = ENOMEM;
    return -1;
  }

  int lvl = gen_lvl();

  rec->k = k;
  rec->v = v;
  rec->fwd = malloc(sizeof(struct sirec*) * lvl);

  if (!rec->fwd) {
    free(rec);

    errno = ENOMEM;
    return -1;
  }

  rec->fwd[lvl] = &m->beg;

  for (int l = lvl; l >= 0; --l) {
    fwd = rec->fwd[l]->fwd[l];

    while (fwd && strcmp(fwd->k, k) < 0) {
      rec->fwd[l] = fwd;
      fwd = fwd->fwd[l];
    }

    if (fwd && strcmp(fwd->k, k) == 0) {
      fwd->v = v;

      free(rec->fwd);
      free(rec);

      return 0;
    }

    if (l != 0)
      rec->fwd[l + 1] = rec->fwd[l];
  }

  for (int l = lvl; l >= 0; --l) {
    struct sirec* n = rec->fwd[l]->fwd[l];

    rec->fwd[l]->fwd[l] = rec;
    rec->fwd[l] = n;
  }

  if (lvl > m->lvl)
    m->lvl = lvl;

  return 1;
}
