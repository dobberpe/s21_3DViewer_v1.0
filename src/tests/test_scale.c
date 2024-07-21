#include "tests.h"

START_TEST(test_1) {
  int error = OK;
  Figure figure;
  const char *file = "obj_files/example.obj";

  error = parse_obj_file(file, &figure);
  ck_assert_msg(error == OK, "init failed");

  destroy_figure(&figure);
}
END_TEST

Suite *test_scale(void) {
  Suite *suite = suite_create("test_scale");
  TCase *tcase_core = tcase_create("test_scale");

  tcase_add_test(tcase_core, test_1);

  suite_add_tcase(suite, tcase_core);

  return suite;
}