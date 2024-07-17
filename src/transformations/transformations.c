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

void fill_transformation_matrix(T_matrix* t_m_struct, t_vector* v_struct) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      t_m_struct->t_matrix[i][j] = i == j ? 1 : 0;
    }
  }
  t_m_struct->t_matrix[0][homo] = v_struct->vector[x];
  t_m_struct->t_matrix[1][homo] = v_struct->vector[y];
  t_m_struct->t_matrix[2][homo] = v_struct->vector[z];
}

void matrix_transpose(T_matrix* t_m_struct) {
  double temp = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      temp = t_m_struct->t_matrix[i][j];
      t_m_struct->t_matrix[i][j] = t_m_struct->t_matrix[j][i];
      t_m_struct->t_matrix[j][i] = temp;
    }
  }
}

void multiply_matrix(Figure* figure, T_matrix* t_m_struct) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    for (int j = 0; j < 4; ++j) {
      double temp = 0;
      for (int k = 0; k < 4; ++k) {
        temp += figure->vertex[i][k] * t_m_struct->t_matrix[k][j];
      }
      figure->vertex[i][j] = temp;
    }
  }
}

void move_figure(Figure* figure, t_vector* v_struct) {
  T_matrix t_m_struct = {0};
  fill_transformation_matrix(&t_m_struct, v_struct);
  matrix_transpose(&t_m_struct);
  multiply_matrix(figure, &t_m_struct);
}
