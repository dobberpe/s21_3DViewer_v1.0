#ifndef __TRANSFORMATIONS_H__
#define __TRANSFORMATIONS_H__

#include <math.h>

#include "../common/common.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void align_to_center(Figure* figure);
void scale_figure(Figure* figure, double scale);
double max_(double a, double b, double c);

void move_figure(Figure* figure);
void rotate_figure(Figure* figure);

void fill_transformation_matrix(Figure* figure);
void matrix_transpose(double** t_matrix);
void make_rotation_matrix(Figure* figure, double alpha_x, double alpha_y,
                          double alpha_z);
void fill_rotation_matrix_crd(double** matrix, double alpha, int crd);
void rotate_helper(Figure* figure);
void mult_matrix(double** m1, double** m2, int rows_1, int col_2);

#endif