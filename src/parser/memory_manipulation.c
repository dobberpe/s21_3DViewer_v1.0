#include "parser.h"

/// @brief initializes structure Figure (NULL / 0)
/// @param figure pointer to structure of type Figure
void init_figure(Figure* figure) {
  figure->vertex = NULL;
  figure->polygon = NULL;
  figure->amount_vertex = 0;
  figure->amount_polygon = 0;
  figure->x_max = figure->y_max = figure->z_max = 0;
  figure->x_min = figure->y_min = figure->z_min = 0;
}

/// @brief deallocates memory for figure
/// @param figure pointer to structure of type Figure
void destroy_figure(Figure* figure) {
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

/// @brief allocates memory for new vertex
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int realloc_vertex(Figure* figure) {
  int error = OK;
  if (figure->amount_vertex == 0) {
    figure->vertex = malloc(sizeof(double*));
    if (!figure->vertex) error = ERR;
    if (!error) {
      ++figure->amount_vertex;
      figure->vertex[0] = malloc(4 * sizeof(double));
      if (!figure->vertex[0]) error = ERR;
    }
  } else {
    double** row_tmp = NULL;
    row_tmp =
        realloc(figure->vertex, (figure->amount_vertex + 1) * sizeof(double*));
    if (!row_tmp) error = ERR;
    if (!error) {
      figure->vertex = row_tmp;
      ++figure->amount_vertex;
      figure->vertex[figure->amount_vertex - 1] = malloc(4 * sizeof(double));
      if (!figure->vertex[figure->amount_vertex - 1]) error = ERR;
    }
  }
  return error;
}

/// @brief allocates memory for new polygon line
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int realloc_polygon(Figure* figure) {
  int error = OK;
  if (figure->amount_polygon == 0) {
    figure->polygon = malloc(sizeof(Polygon));
    if (!figure->polygon)
      error = ERR;
    else
      ++figure->amount_polygon;
  } else {
    Polygon* tmp = NULL;
    tmp = realloc(figure->polygon,
                  (figure->amount_polygon + 1) * sizeof(Polygon));
    if (!tmp)
      error = ERR;
    else {
      figure->polygon = tmp;
      ++figure->amount_polygon;
    }
  }

  figure->polygon[figure->amount_polygon - 1].vertex_p = NULL;
  figure->polygon[figure->amount_polygon - 1].amount_p = 0;
  return error;
}

/// @brief deallocates memory for the last polygon line
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int realloc_down_polygon(Figure* figure) {
  int error = OK;
  if (figure->amount_polygon) {
    Polygon* tmp = NULL;
    tmp = realloc(figure->polygon,
                  (figure->amount_polygon - 1) * sizeof(Polygon));
    if (!tmp)
      error = ERR;
    else {
      figure->polygon = tmp;
      --figure->amount_polygon;
    }
  }
  return error;
}

/// @brief allocates memory for a new single polygon vertex
/// @param polygon pointer to structure of type Polygon
/// @return error code: 1 = error; 0 = OK
int realloc_vertex_p(Polygon* polygon) {
  int error = OK;
  if (polygon->amount_p == 0) {
    polygon->vertex_p = malloc(sizeof(int));
    if (!polygon->vertex_p)
      error = ERR;
    else
      ++polygon->amount_p;
  } else {
    int* tmp = NULL;
    tmp = realloc(polygon->vertex_p, (polygon->amount_p + 1) * sizeof(int));
    if (!tmp)
      error = ERR;
    else {
      polygon->vertex_p = tmp;
      ++polygon->amount_p;
    }
  }
  return error;
}