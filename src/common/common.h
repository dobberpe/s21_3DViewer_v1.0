#ifndef __COMMON_H__
#define __COMMON_H__

#define ERR 1
#define OK 0

#define INITIAL_SCALE 0.5

typedef enum { x = 0, y, z, homo } crd;

typedef struct t_math {
  double** tranformation_matrix;
  double** rotation_matrix_x;
  double** rotation_matrix_y;
  double** rotation_matrix_z;
  double move_vector[3];
} t_math;

typedef struct Polygon {
  int* vertex_p;
  int amount_p;
} Polygon;

typedef struct Figure {
  double* vertex;
  int amount_vertex;
  Polygon* polygon;
  int amount_polygon;
  double x_max, y_max, z_max, x_min, y_min, z_min;
  double alpha_x, alpha_y, alpha_z;
  double cur_scale;
  t_math trv;
} Figure;

#endif