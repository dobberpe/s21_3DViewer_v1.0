#ifndef __TRANSFORMATIONS_H__
#define __TRANSFORMATIONS_H__

#include "../common/common.h"

#define INITIAL_SCALE 0.5

void align_to_center(Figure* figure);
double find_center_by_crd(double min, double max);
void scale_figure(Figure* figure, double scale);
double max_(double a, double b, double c);

#endif