#include "common/common.h"
#include "parser/parser.h"
#include "transformations/transformations.h"

void print_figure(Figure* figure);

int main() {
  Figure figure;

  parse_obj_file("obj_files/tests_only/wr_test_7.obj", &figure);
  align_to_center(&figure);
  print_figure(&figure);

  destroy_figure(&figure);

  return 0;
}

void print_figure(Figure* figure) {
  printf("vertex amount: %d\n\n", figure->amount_vertex);
  printf("polygon amount: %d\n\n", figure->amount_polygon);

  // for (int i = 0; i < figure->amount_vertex; ++i) {
  //   printf("%lf ", figure->vertex[i * 3 + x]);
  //   printf("%lf ", figure->vertex[i * 3 + y]);
  //   printf("%lf ", figure->vertex[i * 3 + z]);
  //   printf("\n");
  // }

  for (int i = 0; i < figure->amount_polygon; ++i) {
    for (int j = 0; j < figure->polygon[i].amount_p; ++j) {
      printf("%d ", figure->polygon[i].vertex_p[j]);
    }
    // printf("%lf ", figure->polygon.);
    // printf("%lf ", figure->vertex[i * 3 + y]);
    // printf("%lf ", figure->vertex[i * 3 + z]);
    printf("\n");
  }
}