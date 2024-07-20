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

void fill_transformation_matrix(Figure* figure) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      figure->trv.tranformation_matrix[i][j] = i == j ? 1 : 0;
    }
  }
  figure->trv.tranformation_matrix[0][homo] = figure->trv.move_vector[x];
  figure->trv.tranformation_matrix[1][homo] = figure->trv.move_vector[y];
  figure->trv.tranformation_matrix[2][homo] = figure->trv.move_vector[z];
}

void matrix_transpose(double** t_matrix) {
  double temp = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      temp = t_matrix[i][j];
      t_matrix[i][j] = t_matrix[j][i];
      t_matrix[j][i] = temp;
    }
  }
}

void move_figure(Figure* figure) {
  fill_transformation_matrix(figure);
  matrix_transpose(figure->trv.tranformation_matrix);
  mult_matrix(figure->vertex, figure->trv.tranformation_matrix,
              figure->amount_vertex, 4);
  // тут нужно будет создать временную матрицу с 4-й колонкой
  // для этой операции
  // а потом вернуть данные обратно
}

void rotate_figure(Figure* figure) {
  double alpha_x = figure->alpha_x * M_PI / 180.0;
  double alpha_y = figure->alpha_y * M_PI / 180.0;
  double alpha_z = figure->alpha_z * M_PI / 180.0;
  make_rotation_matrix(figure, alpha_x, alpha_y, alpha_z);
  rotate_helper(figure);
}

void make_rotation_matrix(Figure* figure, double alpha_x, double alpha_y,
                          double alpha_z) {
  fill_rotation_matrix_crd(figure->trv.rotation_matrix_x, alpha_x, x);
  fill_rotation_matrix_crd(figure->trv.rotation_matrix_y, alpha_y, y);
  fill_rotation_matrix_crd(figure->trv.rotation_matrix_z, alpha_z, z);
  mult_matrix(figure->trv.rotation_matrix_x, figure->trv.rotation_matrix_y, 3,
              3);
  mult_matrix(figure->trv.rotation_matrix_x, figure->trv.rotation_matrix_z, 3,
              3);
}

void fill_rotation_matrix_crd(double** matrix, double alpha, int crd) {
  matrix[0][0] = crd == x ? 1.0 : cos(alpha);
  matrix[0][1] = 0;
  if (crd == x) matrix[0][2] = 0;
  if (crd == y) matrix[0][2] = sin(alpha);
  if (crd == z) matrix[0][2] = -sin(alpha);
  matrix[1][0] = crd == z ? sin(alpha) : 0;
  matrix[1][1] = crd == y ? 1 : cos(alpha);
  matrix[1][2] = crd == x ? -sin(alpha) : 0;
  matrix[2][0] = crd == y ? -sin(alpha) : 0;
  matrix[2][1] = crd == x ? sin(alpha) : 0;
  matrix[2][2] = crd == z ? 1 : cos(alpha);
}

void rotate_helper(Figure* figure) {
  for (int i = 0; i < figure->amount_vertex; ++i) {
    double tmp[3] = {0, 0, 0};
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < 3; ++k) {
        tmp[j] += figure->trv.rotation_matrix_x[j][k] * figure->vertex[i][k];
      }
    }
    for (int j = 0; j < 3; ++j) {
      figure->vertex[i][j] = tmp[j];
    }
  }
}

/// @brief Multiplies two 2nd matrixes, result is written to the first matrix
/// @param m1
/// @param m2
/// @param rows_1
/// @param col_2
void mult_matrix(double** m1, double** m2, int rows_1, int col_2) {
  for (int i = 0; i < rows_1; ++i) {
    for (int j = 0; j < col_2; ++j) {
      double temp = 0;
      for (int k = 0; k < col_2; ++k) {
        temp += m1[i][k] * m2[k][j];
      }
      m1[i][j] = temp;
    }
  }
}