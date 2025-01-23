#ifndef STDX_MAP_H
#define STDX_MAP_H

#define STDX_MAP_MAX_LVL 16
#define STDX_MAP_PBT_NUM 0.5

#include <stdx/cap.h>

struct sirec {
  const char* k;
  int v;

  struct sirec** fwd;
};

struct simap {
  uint len;
  int lvl;

  struct icap cmp;
  struct sirec beg;
};

int simap_new(struct simap* m);
int simap_cls(struct simap* m);

int simap_get(struct simap* m, const char* k, int* v);
int simap_put(struct simap* m, const char* k, int v);
int simap_pop(struct simap* m, const char* k, int* v);
int simap_del(struct simap* m, const char* k);

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
