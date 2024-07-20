#ifndef __PARSER_H__
#define __PARSER_H__

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"

int init_figure(Figure* figure);
void destroy_figure(Figure* figure);

int parse_obj_file(const char* filename, Figure* figure);

int realloc_vertex(Figure* figure);
int realloc_polygon(Figure* figure);
int realloc_down_polygon(Figure* figure);
int realloc_vertex_p(Polygon* polygon);

#endif