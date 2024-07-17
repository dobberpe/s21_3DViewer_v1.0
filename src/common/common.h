#ifndef __COMMON_H__
#define __COMMON_H__

#define ERR 1
#define OK 0

typedef enum { x = 0, y, z, homo} crd;

typedef struct Polygon {
  int* vertex_p;
  int amount_p;
} Polygon;

typedef struct Vector {
  double vector[3];
} t_vector;

typedef struct Figure {
  double** vertex;
  int amount_vertex;
  Polygon* polygon;
  int amount_polygon;
  double x_max, y_max, z_max, x_min, y_min, z_min;
} Figure;

#endif