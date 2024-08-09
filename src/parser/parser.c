#include "parser.h"

int parse_vertex(char* line, Figure* figure);
int parse_polygon(char* line, Figure* figure);
void remove_comment(char* line);
void check_polygon_pattern(int* num_token, int* pattern, int current_pattern,
                           int* signal_to_fill);
int fill_vertex_p(Polygon* polygon, int value);

/// @brief loops over a file line by line, detects and parses vertexes and
/// polygons
/// @param filename file path (better to use absolute)
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int parse_obj_file(const char* filename, Figure* figure) {
  init_figure(figure);
  int error = OK;
  FILE* file = fopen(filename, "r");
  if (!file) error = ERR;
  if (!error) {
    size_t line_size = 0;
    char* line = NULL;
    while (getline(&line, &line_size, file) != -1 && !error) {
      remove_comment(line);
      if (strncmp(line, "v ", 2) == 0) {
        error = parse_vertex(line, figure);
      } else if (strncmp(line, "f ", 2) == 0) {
        error = parse_polygon(line, figure);
      }
    }
    if (line) free(line);
    fclose(file);
  }
  return error;
}

/// @brief if a line consists of a comment - removes comment
/// @param line file line as a string
void remove_comment(char* line) {
  char* comment = strchr(line, '#');
  if (comment) *comment = '\0';
}

/// @brief reads vertexes from line and saves them to figure
/// @param line file line as a string
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int parse_vertex(char* line, Figure* figure) {
  int error = OK;
  double _x, _y, _z, _w = 0;
  int signal_to_fill = 0;

  char* token = NULL;
  token = strtok(line, " ");
  int num_token = 0;

  while (token != NULL && signal_to_fill != -1) {
    if (num_token == 1 && sscanf(token, "%lf", &_x) == 1) {
      ++signal_to_fill;
    } else if (num_token == 2 && sscanf(token, "%lf", &_y) == 1) {
      ++signal_to_fill;
    } else if (num_token == 3 && sscanf(token, "%lf", &_z) == 1) {
      ++signal_to_fill;
    } else if (num_token == 4 && sscanf(token, "%lf", &_w) == 1) {
      ;
    } else if (num_token > 0) {
      signal_to_fill = -1;
    }
    ++num_token;
    token = strtok(NULL, " ");
  }

  if (signal_to_fill == 3) {
    error = realloc_vertex(figure);
    if (!error) {
      figure->vertex[(figure->amount_vertex - 1) * 3 + x] = _x;
      figure->vertex[(figure->amount_vertex - 1) * 3 + y] = _y;
      figure->vertex[(figure->amount_vertex - 1) * 3 + z] = _z;
      // printf("%lf, %lf, %lf\n", _x, _y, _z);
      
      if (figure->amount_vertex == 1) {
        // если первая строка
        figure->x_max = figure->x_min = _x;
        figure->y_max = figure->y_min = _y;
        figure->z_max = figure->z_min = _z;
      } else {
        figure->x_max = _x > figure->x_max ? _x : figure->x_max;
        figure->y_max = _y > figure->y_max ? _y : figure->y_max;
        figure->z_max = _z > figure->z_max ? _z : figure->z_max;
        figure->x_min = _x < figure->x_min ? _x : figure->x_min;
        figure->y_min = _y < figure->y_min ? _y : figure->y_min;
        figure->z_min = _z < figure->z_min ? _z : figure->z_min;
      }
    } else {
      error = ERR;
    }
  }
  return error;
}

/// @brief reads polygons from line and saves them to figure.polygon
/// @param line file line as a string
/// @param figure pointer to structure of type Figure
/// @return error code: 1 = error; 0 = OK
int parse_polygon(char* line, Figure* figure) {
  int error = OK;
  int v = 0, vt, vn, signal_to_fill = 0;

  error = realloc_polygon(figure);

  char* token = NULL;
  token = strtok(line, " ");
  int num_token = 0;
  int pattern = 0;
  while (token != NULL && !error && signal_to_fill != -1) {
    signal_to_fill = 0;
    if (num_token) {
      if (sscanf(token, "%d/%d/%d", &v, &vt, &vn) == 3) {
        check_polygon_pattern(&num_token, &pattern, 1, &signal_to_fill);
      } else if (sscanf(token, "%d/%d", &v, &vt) == 2) {
        check_polygon_pattern(&num_token, &pattern, 2, &signal_to_fill);
      } else if (sscanf(token, "%d//%d", &v, &vn) == 2) {
        check_polygon_pattern(&num_token, &pattern, 3, &signal_to_fill);
      } else if (sscanf(token, "%d", &v) == 1) {
        check_polygon_pattern(&num_token, &pattern, 4, &signal_to_fill);
      } else if (num_token) {
        signal_to_fill = -1;
      }
      if (v < 1) signal_to_fill = -1;
      if (signal_to_fill == 1) {
        error = realloc_vertex_p(&figure->polygon[figure->amount_polygon - 1]);
        if (!error)
          error = fill_vertex_p(&figure->polygon[figure->amount_polygon - 1],
                                v - 1);
        else
          error = ERR;
      } else if (signal_to_fill == -1) {
        if (figure->polygon[figure->amount_polygon - 1].vertex_p)
          free(figure->polygon[figure->amount_polygon - 1].vertex_p);
        error = realloc_down_polygon(figure);
      }
    }
    ++num_token;
    token = strtok(NULL, " ");
  }
  if (num_token == 1) realloc_down_polygon(figure);

  return error;
}

/// @brief checks if a current pattern is the same as general line pattern
/// @param num_token number of processed token
/// @param pattern polygon line pattern
/// @param current_pattern pattern of a current token
/// @param signal_to_fill
void check_polygon_pattern(int* num_token, int* pattern, int current_pattern,
                           int* signal_to_fill) {
  if (*num_token > 1 && *pattern != current_pattern) {
    *signal_to_fill -= 1;
  } else {
    *pattern = current_pattern;
    *signal_to_fill += 1;
  }
}

/// @brief fills polygon line in a format:
/// point_1 point_2 point_2 point_3 point_3 point_1
/// @param polygon pointer to structure of type Polygon
/// @param value int
int fill_vertex_p(Polygon* polygon, int value) {
  int error = OK;
  if (polygon->amount_p - 1 != 0) {
    polygon->vertex_p[polygon->amount_p - 2] = value;
  }
  polygon->vertex_p[polygon->amount_p - 1] = value;
  error = realloc_vertex_p(polygon);
  if (!error) polygon->vertex_p[polygon->amount_p - 1] = polygon->vertex_p[0];

  return error;
}
