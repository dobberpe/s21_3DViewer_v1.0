#ifndef __TRANSFORMATIONS_H__
#define __TRANSFORMATIONS_H__

#include "../common/common.h"

#define INITIAL_SCALE 1

typedef struct Translation_matrix {
  double t_matrix[4][4];
} T_matrix;

void align_to_center(Figure* figure);
double find_center_by_crd(double min, double max);
void scale_figure(Figure* figure, double scale);
double max_(double a, double b, double c);

void move_figure(Figure* figure, t_vector* v_struct);

void fill_transformation_matrix(T_matrix* t_matrix, t_vector* vector);
void matrix_transpose(T_matrix* t_matrix_struct);
void multiply_matrix(Figure* figure, T_matrix* t_matrix_struct);

#endif