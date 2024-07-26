#include "common/common.h"
#include "parser/parser.h"
#include "transformations/transformations.h"

void print_figure(Figure* figure);

int main() {
  Figure figure;

  parse_obj_file("./obj_files/test.obj", &figure);

  print_figure(&figure);

  destroy_figure(&figure);

  return 0;
}

void print_figure(Figure* figure) {
  printf("vertext amount: %d\n\n", figure->amount_vertex);

  // for (int i = 0; i < figure->amount_vertex; ++i) {
  //   printf("%lf ", figure->vertex[i * 3 + x]);
  //   printf("%lf ", figure->vertex[i * 3 + y]);
  //   printf("%lf ", figure->vertex[i * 3 + z]);
  //   printf("\n");
  // }
}