#include <munit.h>
#include <stdx/cut.h>
#include <stdx/fun.h>
#include <stdx/err.h>

void f(struct fun f) {
  f.call(f.ctx);
}

void cbk1(int* ctx) {
  *ctx += 1;
}

void cbk2(double* ctx) {
  *ctx = *ctx * *ctx;
}

res(int) function() {
  return err(int, "something horrible");
}

static MunitResult test_inc(const MunitParameter[], void*) {
  int ictx = 10;
  double dctx = 2.0;

  f(fun(ictx, cbk1));
  f(fun(dctx, cbk2));

  munit_assert_int(11, ==, ictx);
  munit_assert_double_equal(4.0, dctx, 3);

  if (function().ok) {
  }

  return MUNIT_OK;
}

static MunitTest itests[] = {
  {"/inc", test_inc, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suites[] = {
  {"/ifun", itests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = {
  "fun", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
