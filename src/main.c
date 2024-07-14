#include "parser/parser.h"

void print_figure(Figure* figure);

int main() {
  int error = OK;

  Figure figure;

  const char* filename = "obj_files/example.obj";

  error = parse_obj_file(filename, &figure);

  print_figure(&figure);
  
  destroy_figure(&figure);

  return 0;
}

void print_figure(Figure* figure) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    printf("%lf ", figure->vertex[i][x]);
    printf("%lf ", figure->vertex[i][y]);
    printf("%lf ", figure->vertex[i][z]);
    printf("\n");
  }

  for (int i = 0; i < figure->amount_polygon; ++i) {
    for (int j = 0; j < figure->polygon[i].amount_p; ++j) {
      printf("%d ", figure->polygon[i].vertex_p[j]);
    }
    printf("\n");
  }
}