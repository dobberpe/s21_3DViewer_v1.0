#include "tests.h"

START_TEST(test_1) {
  int error = OK;
  Figure figure;
  const char *file = "obj_files/airboat.obj";

  error = parse_obj_file(file, &figure);

  ck_assert_msg(error == OK, "game info init failed");
  ck_assert_msg(figure.amount_vertex == 5797, "wrong vertexes amount parsed");
  ck_assert_msg(figure.amount_polygon == 6273, "wrong vertexes amount parsed");

  ck_assert_msg(figure.vertex[(figure.amount_vertex - 1) * 3 + 0] == -6.028662,
                "wrong last line vertex value [0]");
  ck_assert_msg(figure.vertex[(figure.amount_vertex - 1) * 3 + 1] == 1.639770,
                "wrong last line vertex value [1]");
  ck_assert_msg(figure.vertex[(figure.amount_vertex - 1) * 3 + 2] == 1.364798,
                "wrong last line vertex value [2]");

  ck_assert_msg(figure.polygon[figure.amount_polygon - 1].vertex_p[0] == 4561,
                "wrong polygon value [last][0]");
  ck_assert_msg(figure.polygon[figure.amount_polygon - 1].vertex_p[1] == 4560,
                "wrong polygon value [last][1]");

  ck_assert_msg(
      figure.polygon[figure.amount_polygon - 1]
              .vertex_p[figure.polygon[figure.amount_polygon - 1].amount_p -
                        2] == 4562,
      "wrong polygon value [last][last - 1]");
  ck_assert_msg(
      figure.polygon[figure.amount_polygon - 1]
              .vertex_p[figure.polygon[figure.amount_polygon - 1].amount_p -
                        1] == 4561,
      "wrong polygon value [last][last]");

  destroy_figure(&figure);
}
END_TEST

Suite *test_parser(void) {
  Suite *suite = suite_create("test_parser");
  TCase *tcase_core = tcase_create("test_parser");

  tcase_add_test(tcase_core, test_1);

  suite_add_tcase(suite, tcase_core);
  
  return suite;
}
