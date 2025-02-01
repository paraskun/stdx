#ifndef STDX_MAP_H
#define STDX_MAP_H

#include <stdint.h>
#include <stdx/cap.h>

#define STDX_MAP_LVL_MAX 16
#define STDX_MAP_LVL_PBT 0.5

struct sirec {
  str k;
  int v;

  struct sirec** fwd;
};

struct simap {
  int len;
  int lvl;

  struct sirec beg;
};

int simap_new(struct simap* m);
int simap_cls(struct simap* m);

int simap_get(const struct simap* m, str k, int* v);

int simap_put(struct simap* m, str k, int v);
int simap_pop(struct simap* m, str k, int* v);
int simap_del(struct simap* m, str k);

#define map_new(X) _Generic((X),  \
    struct simap*: simap_new      \
    )(X)

#define map_cls(X) _Generic((X),  \
    struct simap*: simap_cls      \
    )(X)

#define map_get(X, k, v) _Generic((X),  \
    struct simap*: simap_get            \
    )(X, k, v)

#define map_put(X, k, v) _Generic((X),  \
    struct simap*: simap_put            \
    )(X, k, v)

#define map_pop(X, k, v) _Generic((X),  \
    struct simap*: simap_pop            \
    )(X, k, v)

#define map_del(X, k) _Generic((X),     \
    struct simap*: simap_del            \
    )(X, k)

#endif  // STDX_MAP_H
