#include <stdio.h>
#include <stdlib.h>

// список вершин (w - необязательный)
// v x y z w

// текстурные координаты (w - необязательный)
// vt u v w

// нормали
// vn x y z 

// параметры вершин в пространстве (v, w - необязательный)
// vp u v w

// определение поверхности (сторон)
// f v1 v2 v3
// v/vt/vn 
// v//vn 
// v/vt 
// v

// группа
// g

// объект
// o

#define ERR 1
#define OK 0

typedef enum {
  x = 0,
  y,
  z
} crd;

typedef struct Polygon {
  int * vertex_p;
  int amount_p;
} Polygon;

typedef struct Figure {
  double ** vertex;
  int amount_vertex;
  Polygon * polygon;
  int amount_polygon;

} Figure;

int init_figure(Figure * figure) {
  int error = OK;

  figure->vertex = NULL;
  figure->polygon = NULL;
  figure->amount_vertex = 0;
  figure->amount_polygon = 0;

  figure->vertex = calloc(1, sizeof(double*));
  if (!figure->vertex) error = ERR;
  if (!error) {
    figure->vertex[0] = calloc(3, sizeof(double));
    if (!figure->vertex[0]) error = ERR;
    
  }
  if (!error) {
    ++figure->amount_vertex;
    figure->polygon = malloc(sizeof(Polygon));
    if (!figure->polygon) error = ERR;
  }
  if (!error) {
    ++figure->amount_polygon;
    figure->polygon->vertex_p = NULL;
    figure->polygon->amount_p = 0;
    figure->polygon->vertex_p = calloc(1, sizeof(int));
    if (!figure->polygon->vertex_p) error = ERR;
    if (!error) ++figure->polygon->amount_p;
   }

  return error;
}

void destroy_figure(Figure * figure) {
  if (figure->polygon) {
    for (int i = 0; i < figure->amount_polygon; ++i) {
      if (figure->polygon[i].vertex_p) free(figure->polygon[i].vertex_p);
    }
    free(figure->polygon);
    figure->polygon = NULL;
    figure->amount_polygon = 0;
  }

  if (figure->vertex) {
    for (int i = 0; i < figure->amount_vertex; ++i) {
      if (figure->vertex[i]) free(figure->vertex[i]);
    }
    free(figure->vertex);
    figure->vertex = NULL;
    figure->amount_vertex = 0;
  }
}

int main() {
  int error = OK;

  Figure figure;
  error = init_figure(&figure);

  if (!error) {
    figure.vertex[0][x] = 1;
    figure.vertex[0][y] = 2;
    figure.vertex[0][z] = 3;
    figure.polygon->vertex_p[0] = 20;

    printf("%f\n", figure.vertex[0][x]);
    printf("%f\n", figure.vertex[0][y]);
    printf("%f\n", figure.vertex[0][z]);
    printf("%d\n", figure.polygon->vertex_p[0]);
  }

  
  
  destroy_figure(&figure);

  return 0;
}