#include <munit.h>
#include <stdx/cut.h>
#include <stdx/pque.h>

static MunitResult test_ifix(const MunitParameter[], void*) {
  struct icut *c;

  munit_assert_int(0, ==, cut_new(&c));

  munit_assert_int(0, ==, cut_add(c, 3));
  munit_assert_int(0, ==, cut_add(c, 2));
  munit_assert_int(0, ==, cut_add(c, 5));
  munit_assert_int(0, ==, cut_add(c, 1));
  munit_assert_int(0, ==, cut_add(c, 4));

  int e;

  munit_assert_int(0, ==, pque_fix(c));
  munit_assert_int(0, ==, pque_ext(c, &e));
  munit_assert_int(5, ==, e);
  munit_assert_int(0, ==, pque_ext(c, &e));
  munit_assert_int(4, ==, e);
  munit_assert_int(0, ==, pque_ext(c, &e));
  munit_assert_int(3, ==, e);
  munit_assert_int(0, ==, pque_ext(c, &e));
  munit_assert_int(2, ==, e);
  munit_assert_int(0, ==, pque_ext(c, &e));
  munit_assert_int(1, ==, e);

  munit_assert_int(0, ==, cut_cls(&c));
  
  return MUNIT_OK;
}

static MunitResult test_isrt(const MunitParameter[], void*) {
  struct icut *c;

  munit_assert_int(0, ==, cut_new(&c));

  munit_assert_int(0, ==, cut_add(c, 3));
  munit_assert_int(0, ==, cut_add(c, 2));
  munit_assert_int(0, ==, cut_add(c, 5));
  munit_assert_int(0, ==, cut_add(c, 1));
  munit_assert_int(0, ==, cut_add(c, 4));

  munit_assert_int(0, ==, pque_fix(c));
  munit_assert_int(0, ==, pque_srt(c));

  munit_assert_int(1, ==, c->dat[0]);
  munit_assert_int(2, ==, c->dat[1]);
  munit_assert_int(3, ==, c->dat[2]);
  munit_assert_int(4, ==, c->dat[3]);
  munit_assert_int(5, ==, c->dat[4]);

  munit_assert_int(0, ==, cut_cls(&c));
  
  return MUNIT_OK;
}

static MunitTest itests[] = {
  {"/fix", test_ifix, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/srt", test_isrt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suites[] = {
  {"/ipque", itests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = { "pque", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE };

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv); 
}
