#include "parser.h"

void print_figure(Figure* figure);

int main() {
  int error = OK;

  Figure figure;
  init_figure(&figure);

  const char* filename = "example.obj";

  error = parse_obj_file(filename, &figure);

  // print_figure(&figure);
  
  destroy_figure(&figure);

  return 0;
}

void print_figure(Figure* figure) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    for (int j = 0; j < 3; ++j) {
      printf("%lf ", figure->vertex[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < figure->amount_polygon; ++i) {
    for (int j = 0; j < figure->polygon[i].amount_p; ++j) {
      printf("%d ", figure->polygon[i].vertex_p[j]);
    }
    printf("\n");
  }
}