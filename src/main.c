#include "parser/parser.h"
#include "transformations/transformations.h"

void print_figure(Figure* figure);

int main() {
  int error = OK;

  Figure figure;

  const char* filename = "obj_files/example.obj";

  error = parse_obj_file(filename, &figure);

  if (!error) {
    printf("x_max %lf ", figure.x_max);
    printf("x_min %lf ", figure.x_min);
    printf("y_max %lf ", figure.y_max);
    printf("y_min %lf ", figure.y_min);
    printf("z_max %lf ", figure.z_max);
    printf("z_min %lf\n", figure.z_min);
    print_figure(&figure);
    // printf("\n");
    // align_to_center(&figure);
    // print_figure(&figure);
    printf("\n");
    scale_figure(&figure, INITIAL_SCALE);
    print_figure(&figure);
    printf("\n");

    // t_vector vct = {0};
    // vct.vector[0] = 1;
    // vct.vector[1] = -1;
    // vct.vector[2] = 2;
    // move_figure(&figure, &vct);
    // print_figure(&figure);
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