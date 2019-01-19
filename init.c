#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "shape.h"
#include "error_codes.h"
#include "init.h"

ERROR_CODES init (SHAPE_TYPE *p_shape, int *p_num_coords, char *arg)
{
	ERROR_CODES ret = ERR_OK;
	
  //Now check that the argument provided is supported.
  if (strcmp(arg, "line") == 0)
  {
    *p_shape = LINE;
    *p_num_coords = NUM_LINE_COORDS;
  }
  else if (strcmp(arg, "plane") == 0)
  {
    *p_shape = PLANE;
    *p_num_coords = NUM_PLANE_COORDS;
  }
  else if (strcmp(arg, "circle") == 0)
  {
    *p_shape = CIRCLE;
    *p_num_coords = NUM_CIRCLE_COORDS;
  }
  else if (strcmp(arg, "sphere") == 0)
  {
    *p_shape = SPHERE;
    *p_num_coords = NUM_SPHERE_COORDS;
  }
  else if (strcmp(arg, "general_conic") == 0)
  {
    *p_shape = GENERAL_CONIC;
    *p_num_coords = NUM_GENERAL_CONIC_COORDS;
  }
  else
  {
    printf ("Shape %s not supported\n", arg);
		ret = ERR_ARG_TYPE;
  }

	return (ret);
}
