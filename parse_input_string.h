#ifndef _PARSE_INPUT_STRING_H_
#define _PARSE_INPUT_STRING_H_

#include "error_codes.h"
#include "shape.h"

ERROR_CODES parse_input_string (int num_coords, SHAPE_TYPE shape, char *p_inp_buf, double *p_coord_matrix);

#endif 
