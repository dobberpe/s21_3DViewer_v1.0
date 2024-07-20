#include "parser/parser.h"
#include "transformations/transformations.h"

void print_figure(Figure* figure);

int main() {
  int error = OK;

  Figure figure;

  const char* filename = "obj_files/example.obj";

  error = parse_obj_file(filename, &figure);

  if (!error) {
    print_figure(&figure);
    printf("\n");
    align_to_center(&figure);
    print_figure(&figure);
    printf("\n");
    scale_figure(&figure, 1);
    print_figure(&figure);
    printf("\n");

    figure.alpha_x = 100;
    figure.alpha_y = 101;
    figure.alpha_z = 102;
    rotate_figure(&figure);
    print_figure(&figure);
    printf("\n");

    figure.trv.move_vector[0] = 1;
    figure.trv.move_vector[1] = -1;
    figure.trv.move_vector[2] = 2;
    move_figure(&figure);
    print_figure(&figure);
  }

  destroy_figure(&figure);

  return 0;
}

void print_figure(Figure* figure) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    printf("%lf ", figure->vertex[i][x]);
    printf("%lf ", figure->vertex[i][y]);
    printf("%lf ", figure->vertex[i][z]);
    printf("%lf ", figure->vertex[i][homo]);
    printf("\n");
  }

  for (int i = 0; i < figure->amount_polygon; ++i) {
    for (int j = 0; j < figure->polygon[i].amount_p; ++j) {
      printf("%d ", figure->polygon[i].vertex_p[j]);
    }
    printf("\n");
  }
}