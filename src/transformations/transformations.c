#include "transformations.h"

void align_to_center(Figure* figure) {
  double x_center = find_center_by_crd(figure->x_min, figure->x_max);
  double y_center = find_center_by_crd(figure->y_min, figure->y_max);
  double z_center = find_center_by_crd(figure->z_min, figure->z_max);
  for (int i = 0; i < figure->amount_vertex; ++i) {
    figure->vertex[i][x] -= x_center;
    figure->vertex[i][y] -= y_center;
    figure->vertex[i][z] -= z_center;
  }
}

double find_center_by_crd(double min, double max) {
  return (min + (max - min) / 2);
}

void scale_figure(Figure* figure, double scale) {
  double max_value =
      max_(figure->x_max - figure->x_min, figure->y_max - figure->y_min,
           figure->z_max - figure->z_min);
  double scale_coef = (scale - (scale * (-1)) / max_value);
  for (int i = 0; i < figure->amount_vertex; ++i) {
    figure->vertex[i][x] *= scale_coef;
    figure->vertex[i][y] *= scale_coef;
    figure->vertex[i][z] *= scale_coef;
  }
}

double max_(double a, double b, double c) {
  double res = a;
  if (b > res) res = b;
  if (c > res) res = c;
  return res;
}