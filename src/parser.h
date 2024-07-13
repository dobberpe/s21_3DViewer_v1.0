#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  double x_max, y_max, z_max, x_min, y_min, z_min;
} Figure;


void init_figure(Figure * figure);
void destroy_figure(Figure * figure);

int parse_obj_file(const char * filename, Figure* figure);
int parse_vertex(const char* line, Figure* figure);
int parse_polygon(char* line, Figure* figure);
void remove_comment(char* line);

int realloc_vertex(Figure* figure);
int realloc_polygon(Figure * figure);
int realloc_down_polygon(Figure * figure);
int realloc_vertex_p(Polygon* polygon);