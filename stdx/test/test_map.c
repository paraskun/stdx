#include <munit.h>
#include <string.h>

#include <stdx/map.h>

static MunitResult test_siput(const MunitParameter[], void*) {
  struct simap m;

  int v;

  munit_assert_int(0, ==, map_new(&m));
  munit_assert_int(1, ==, map_put(&m, "key", 10));
  munit_assert_int(0, ==, map_get(&m, "key", &v));
  munit_assert_int(10, ==, v);
  munit_assert_int(0, ==, map_cls(&m));

  return MUNIT_OK;
}

static MunitTest sitests[] = {
  {"/put", test_siput, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suites[] = {
  {"/simap", sitests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = {"map", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char** argv) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
