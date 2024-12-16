#include <munit.h>

static MunitResult test_iini(const MunitParameter[], void*) {
  return MUNIT_OK;
}

static MunitTest itests[] = {
  {"/ini", test_iini, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static MunitSuite suites[] = {
  {"icut", itests, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
};

static const MunitSuite suite = { "cut", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE };

int main(int argc, char** argv) {
  return 0;
}
