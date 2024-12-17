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

#endif  // STDX_CUT_INT_H
