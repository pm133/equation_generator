#ifndef _GET_COEFFICIENTS_H_
#define _GET_COEFFICIENTS_H_

#include "shape.h"

void get_coefficients (SHAPE_TYPE shape, int num_coords, double *p_coord_matrix, double *p_coeffs);
void report_final_equation (int num_coords, SHAPE_TYPE shape, double *p_coeffs);
#endif
