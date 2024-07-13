#include "parser.h"

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

/// @brief initializes structure Figure
/// @param figure
void init_figure(Figure * figure) {
  figure->vertex = NULL;
  figure->polygon = NULL;
  figure->amount_vertex = 0;
  figure->amount_polygon = 0;
  figure->x_max = figure->y_max = figure->z_max = 0;
  figure->x_min = figure->y_min = figure->z_min = 0;
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

int parse_obj_file(const char * filename, Figure* figure) {
  int error = OK;
  FILE* file = fopen(filename, "r");
  if (!file) error = ERR;
  if (!error) {
    size_t line_size = 0;
    char* line = NULL;
    while (getline(&line, &line_size, file) != -1 && !error) {
      remove_comment(line);
      // printf("%s", line);
      if (strncmp(line, "v ", 2) == 0) {
          error = parse_vertex(line, figure);
      } 
      else if (strncmp(line, "f ", 2) == 0) {
          error = parse_polygon(line, figure);
      }
    }
    if (line) free(line);
    fclose(file);
  }

  return error;
}

void remove_comment(char* line) {
    char* comment = strchr(line, '#');
    if (comment) *comment = '\0';
}

int parse_vertex(const char* line, Figure* figure) {
  int error = OK;
  double _x,_y,_z,_w = 0;
  char c1,c2,c3,c4,c5 = 'a';
  int last_line, signal_to_fill = 0;
  if (line[strlen(line) - 1] != '\n') ++last_line;

  int num_components = sscanf(line, "v%c%lf%c%lf%c%lf%c%lf%c", &c1, &_x, &c2, &_y, &c3, &_z, &c4, &_w, &c5);

  if (!last_line && num_components == 7 && c1 == ' ' && c2 == ' ' && c3 == ' ' && c4 == '\n') {
    // правильный случай с 3 координатами
    ++signal_to_fill;
  } else if (last_line && num_components == 6 && c1 == ' ' && c2 == ' ' && c3 == ' ') {
    // правильный случай с 3 координатами - конец файла
    ++signal_to_fill;
  } else if (!last_line && num_components == 9 && c1 == ' ' && c2 == ' ' && c3 == ' ' && c4 == ' ' && c5 == '\n') {
    // правильный случай с 3 координатами + w
    ++signal_to_fill;
  } else if (last_line && num_components == 8 && c1 == ' ' && c2 == ' ' && c3 == ' ' && c4 == ' ') {
    // правильный случай с 3 координатами - конец файла + w
    ++signal_to_fill;
  }

  if (signal_to_fill) {
    error = realloc_vertex(figure);
    if (!error && figure->vertex[figure->amount_vertex - 1]) {
      figure->vertex[figure->amount_vertex - 1][x] = _x;
      figure->vertex[figure->amount_vertex - 1][y] = _y;
      figure->vertex[figure->amount_vertex - 1][z] = _z;
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

int parse_polygon(char* line, Figure* figure) {
  int error = OK;
  int v, vt, vn, signal_to_fill = 0;

  error = realloc_polygon(figure);

  char * token = NULL;
  token = strtok(line, " ");
  int num_token = 0;
  int pattern = 0;
  while (token != NULL && !error) {
    signal_to_fill = 0;
    if (!num_token) {
      if (sscanf(token, "%d/%d/%d", &v, &vt, &vn) == 3) {
        if (num_token > 1 && pattern != 1) {
          --signal_to_fill;
        } else {
          pattern = 1;
          ++signal_to_fill;
        }
      } else if (sscanf(token, "%d/%d", &v, &vt) == 2) {
        if (num_token > 1 && pattern != 2) {
          --signal_to_fill;
        } else {
          pattern = 2;
          ++signal_to_fill;
        }
      } else if (sscanf(token, "%d//%d", &v, &vn) == 2) {
        if (num_token > 1 && pattern != 3) {
          --signal_to_fill;
        } else {
          pattern = 3;
          ++signal_to_fill;
        }
      } else if (sscanf(token, "%d", &v) == 1) {
        if (num_token > 1 && pattern != 4) {
          --signal_to_fill;
        } else {
          pattern = 4;
          ++signal_to_fill;
        }
      } else {
        --signal_to_fill;
      }
      if (signal_to_fill) {
        if (num_token > 1) error = realloc_vertex_p(figure->polygon);
        if (!error && figure->polygon->vertex_p)
          figure->polygon->vertex_p[figure->polygon->amount_p - 1] = v;
        else
          error = ERR;
      } else if (signal_to_fill == -1)
      {
        error = ERR;
      }
    }
    ++num_token;
  }

  if (error) {
    if (figure->polygon->vertex_p) free(figure->polygon->vertex_p);
    if (figure->polygon) error = realloc_down_polygon(figure);
  }

  return error;
}

int realloc_vertex(Figure* figure) {
  int error = OK;
  if (figure->amount_vertex == 0) {
    figure->vertex = malloc(sizeof(double*));
    if (!figure->vertex) error = ERR;
    if (!error) {
      ++figure->amount_vertex;
      figure->vertex[0] = malloc(3 * sizeof(double));
      if (!figure->vertex[0]) error = ERR;
    }
  } else {
    double ** row_tmp = NULL;
    row_tmp = realloc(figure->vertex, (figure->amount_vertex + 1) * sizeof(double *));
    if (!row_tmp) error = ERR;
    if (!error) {
      ++figure->amount_vertex;
      figure->vertex[figure->amount_vertex - 1] = malloc(3 * sizeof(double));
      if (!figure->vertex[figure->amount_vertex - 1]) error = ERR;
    }
  }
  return error;
}

int realloc_polygon(Figure * figure) {
    int error = OK;
    if (figure->amount_polygon == 0) {
      figure->polygon = malloc(sizeof(Polygon));
      if (!figure->polygon) error = ERR;
      else ++figure->amount_polygon;
    } else {
      Polygon * tmp = NULL;
      tmp = realloc(figure->polygon, (figure->amount_polygon + 1) * sizeof(Polygon));
      if (!tmp) error = ERR;
      else
        {figure->polygon = tmp;
        ++figure->amount_polygon;}
    }

    figure->polygon[figure->amount_polygon - 1].vertex_p = NULL;
    figure->polygon[figure->amount_polygon - 1].amount_p = 0;
    return error;
}

int realloc_down_polygon(Figure * figure) {
  int error = OK;
  if (figure->amount_polygon) {
    Polygon* tmp = NULL;
    tmp = realloc(figure->polygon, (figure->amount_polygon - 1) * sizeof(Polygon));
    if (!tmp) error = ERR;
    else {
      figure->polygon = tmp;
      --figure->amount_polygon;
    }
  }
  return error;
}

int realloc_vertex_p(Polygon* polygon) {
  int error = OK;
  if (polygon->amount_p == 0) {
    polygon->vertex_p = malloc(sizeof(int));
    if (!polygon->vertex_p) error = ERR;
    else ++polygon->amount_p;
  } else {
    int * tmp = NULL;
    tmp = realloc(polygon->vertex_p, (polygon->amount_p + 1) * sizeof(int));
    if (!tmp)
      error = ERR;
    else
    { polygon->vertex_p = tmp;
      ++polygon->amount_p;}
  }
  return error;
}