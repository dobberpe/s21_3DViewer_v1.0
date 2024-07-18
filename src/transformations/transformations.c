#include "transformations.h"

void align_to_center(Figure* figure) {
  double x_center = (figure->x_min + figure->x_max) / 2.0;
  double y_center = (figure->y_min + figure->y_max) / 2.0;
  double z_center = (figure->z_min + figure->z_max) / 2.0;
  double max_dist = max_(figure->x_max - x_center, figure->y_max - y_center,
                         figure->z_max - z_center);
  figure->cur_scale = INITIAL_SCALE / max_dist;
  for (int i = 0; i < figure->amount_vertex; ++i) {
    figure->vertex[i][x] =
        (figure->vertex[i][x] - x_center) * figure->cur_scale;
    figure->vertex[i][y] =
        (figure->vertex[i][y] - y_center) * figure->cur_scale;
    figure->vertex[i][z] =
        (figure->vertex[i][z] - z_center) * figure->cur_scale;
  }
}

void scale_figure(Figure* figure, double scale) {
  if (scale < 0.000001) scale = figure->cur_scale;
  double scale_coef = scale / figure->cur_scale;
  figure->cur_scale = scale;
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

void rotate_x(Figure* figure, double alpha) {
  alpha = alpha * M_PI / 180.0;
  double rotation_matrix[3][3] = {
      {1.0, 0, 0}, {0, cos(alpha), -sin(alpha)}, {0, sin(alpha), cos(alpha)}};
  rotate_helper(figure, rotation_matrix);
}

void rotate_y(Figure* figure, double alpha) {
  alpha = alpha * M_PI / 180.0;
  double rotation_matrix[3][3] = {
      {cos(alpha), 0, sin(alpha)}, {0, 1, 0}, {-sin(alpha), 0, cos(alpha)}};
  rotate_helper(figure, rotation_matrix);
}

void rotate_z(Figure* figure, double alpha) {
  alpha = alpha * M_PI / 180.0;
  double rotation_matrix[3][3] = {
      {cos(alpha), -sin(alpha), 0}, {sin(alpha), cos(alpha), 0}, {0, 0, 1}};
  rotate_helper(figure, rotation_matrix);
}

void rotate_helper(Figure* figure, double rotation_matrix[3][3]) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    double tmp[3] = {0, 0, 0};
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        tmp[j] += rotation_matrix[j][k] * figure->vertex[i][k];
      }
    }
    for (int j = 0; j < 3; ++j) {
      figure->vertex[i][j] = tmp[j];
    }
  }
}