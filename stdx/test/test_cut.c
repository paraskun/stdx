#include <munit.h>
#include <stdx/cap.h>
#include <stdx/cut.h>

static MunitResult test_iini(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));

  munit_assert_not_null(c);

  munit_assert_uint(0, ==, c->len);
  munit_assert_uint(0, ==, c->cap);

  munit_assert_int(0, ==, cut_cls(&c));

  munit_assert_null(c);

  return MUNIT_OK;
}

static MunitResult test_idef(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c, 3, 1, 2, 3));

  munit_assert_int(1, ==, c->dat[0]);
  munit_assert_int(2, ==, c->dat[1]);
  munit_assert_int(3, ==, c->dat[2]);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

int tmp(void*, uint n, ...) {
  return n;
}

static MunitResult test_iexp(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_exp(c, 9));

  munit_assert_uint(0, ==, c->len);
  munit_assert_uint(9, ==, c->cap);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

static MunitResult test_idev(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_dev(c, 3));

  munit_assert_uint(3, ==, c->len);
  munit_assert_uint(3, ==, c->cap);

  munit_assert_int(0, ==, c->dat[0]);
  munit_assert_int(0, ==, c->dat[1]);
  munit_assert_int(0, ==, c->dat[2]);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

static MunitResult test_iadd(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));

  munit_assert_int(0, ==, cut_add(c, 1));
  munit_assert_int(0, ==, cut_add(c, 2));
  munit_assert_int(0, ==, cut_add(c, 3));

  munit_assert_uint(3, ==, c->len);
  munit_assert_uint(6, ==, c->cap);

  munit_assert_int(1, ==, c->dat[0]);
  munit_assert_int(2, ==, c->dat[1]);
  munit_assert_int(3, ==, c->dat[2]);
  munit_assert_int(0, ==, c->dat[3]);
  munit_assert_int(0, ==, c->dat[4]);
  munit_assert_int(0, ==, c->dat[5]);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

static MunitResult test_ishr(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_exp(c, 9));

  munit_assert_uint(0, ==, c->len);
  munit_assert_uint(9, ==, c->cap);

  munit_assert_int(0, ==, cut_add(c, 1));
  munit_assert_int(0, ==, cut_add(c, 2));
  munit_assert_int(0, ==, cut_add(c, 3));

  munit_assert_uint(9, ==, c->cap);
  munit_assert_uint(3, ==, c->len);

  munit_assert_int(0, ==, cut_shr(c));

  munit_assert_uint(3, ==, c->len);
  munit_assert_uint(3, ==, c->cap);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

static MunitResult test_isrt(const MunitParameter[], void*) {
  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_add(c, 2));
  munit_assert_int(0, ==, cut_add(c, 1));
  munit_assert_int(0, ==, cut_add(c, 3));
  munit_assert_int(0, ==, cut_srt(c));

  munit_assert_int(1, ==, c->dat[0]);
  munit_assert_int(2, ==, c->dat[1]);
  munit_assert_int(3, ==, c->dat[2]);

  munit_assert_int(0, ==, cut_cls(&c));

  return MUNIT_OK;
}

static MunitResult test_icov_full(const MunitParameter[], void*) {
  int* s = malloc(sizeof(int) * 5);

  s[0] = 2;
  s[1] = 1;
  s[2] = 5;
  s[3] = 3;
  s[4] = 4;

  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_cov(c, s, 5));
  munit_assert_int(0, ==, cut_srt(c));
  munit_assert_int(0, ==, cut_cls(&c));

  munit_assert_int(1, ==, s[0]);
  munit_assert_int(2, ==, s[1]);
  munit_assert_int(3, ==, s[2]);
  munit_assert_int(4, ==, s[3]);
  munit_assert_int(5, ==, s[4]);

  free(s);

  return MUNIT_OK;
}

static MunitResult test_icov_part(const MunitParameter[], void*) {
  int* s = malloc(sizeof(int) * 5);

  s[0] = 2;
  s[1] = 1;
  s[2] = 5;
  s[3] = 3;
  s[4] = 4;

  struct icut* c;

  munit_assert_int(0, ==, cut_new(&c));
  munit_assert_int(0, ==, cut_cov(c, s + 1, 3));
  munit_assert_int(0, ==, cut_srt(c));
  munit_assert_int(0, ==, cut_cls(&c));

  munit_assert_int(2, ==, s[0]);
  munit_assert_int(1, ==, s[1]);
  munit_assert_int(3, ==, s[2]);
  munit_assert_int(5, ==, s[3]);
  munit_assert_int(4, ==, s[4]);

  free(s);

  return MUNIT_OK;
}

static MunitTest itests[] = {
  {"/ini", test_iini, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/def", test_idef, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/exp", test_iexp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/dev", test_idev, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/add", test_iadd, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/shr", test_ishr, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/srt", test_isrt, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cov/full", test_icov_full, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/cov/part", test_icov_part, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suites[] = {
  {"/icut", itests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = {"cut", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
