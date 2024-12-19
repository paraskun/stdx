#ifndef STDX_CUT_INT_H
#define STDX_CUT_INT_H

#include <stdx/cut.h>

struct icut {
  uint cap;
  uint len;
  bool ctl;

  icmp cmp;
  ianc anc;

  int* data;
};

struct pcut {
  uint cap;
  uint len;
  bool ctl;

  pcmp cmp;
  panc anc;

  void** data;
};

#endif  // STDX_CUT_INT_H
