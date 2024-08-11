
#ifndef MODEL_H
#define MODEL_H

// #define _GNU_SOURCE
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to render 3d wireframe from Wavefront .obj file
typedef struct data {
  size_t vertices_count;
  double *vertices_arr;
  size_t vertex_indices_count;
  int *vertex_indices_arr;
} obj_data;

enum exec_statuses { OK, ERROR };

/**
 * @brief Function runner for parsing object files and writing to an object with
 * data.
 * @param filename pointer to a string with the file name
 * @param data pointer to an object with data
 * @return status code: 0 - OK, 1 - ERROR
 */
int parse_obj_file(char *filename, obj_data *data);

/**
 * @brief Allocates memory inside the object with data for data from the object
 * file.
 * @param data pointer to an object with data
 * @return status code: 0 - OK, 1 - ERROR
 */
int memory_allocation(obj_data *data);

/**
 * @brief Counts vertices and vertex indices in an object file, in order to
 * allocate memory for them later.
 * @param file pointer to obj file
 * @param data pointer to an object with data
 */
void count_vertices_and_indices(FILE *file, obj_data *data);

/**
 * @brief Free memory in a data object.
 * @param data pointer to an object with data
 */
void data_destructor(obj_data *data);

/**
 * @brief Reads vertices and vertex indices from a file and writes them to an
 * object.
 * @param file pointer to obj file
 * @param data pointer to an object with data
 * @return status code: 0 - OK, 1 - ERROR
 */
int parse_vertices_and_indices(FILE *file, obj_data *data);

/**
 * @brief A debugging helper function for printing an object with a date.
 * @param data pointer to an object with data
 */
void print_data(obj_data *data);

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  // M_PI

void rotate_X(obj_data *obj, double angle);
void rotate_Y(obj_data *obj, double angle);
void rotate_Z(obj_data *obj, double angle);

void scale(obj_data *obj, const double k);

void move_X(obj_data *obj, const double k);
void move_Y(obj_data *obj, const double k);
void move_Z(obj_data *obj, const double k);

#endif  // MODEL_H
