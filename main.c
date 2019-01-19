#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "shape.h"
#include "file_access.h"
#include "init.h"
#include "error_codes.h"
#include "parse_input_string.h"
#include "my_mem.h"
#include "get_coefficients.h"


int main (int argc, char *argv[])
{
  int i, num_coords = 0;
  char inp_buf_txt[MAX_FILE_SIZE];
  double coord_matrix[MAX_NUM_COORDS*MAX_NUM_COORDS];
  double coeff_vals[MAX_NUM_COORDS];
  SHAPE_TYPE shape = LINE;
	int ret;
	int max_size_coord_matrix;



	//first check we have the right number of arguments
	//We require two - the shape we need an equation for
	//and the file containing the co-ordinates for
	//that shape.
	if (argc != 3)
	{
		printf ("Error. Expected 2 arguments, received %d\n", (argc-1));
		exit_prog (ERR_ARG_COUNT);
	}

	//Initialise the various storage arrays
  //Default the input buffer to be an empty string first.
  inp_buf_txt[0] = '\0';
  max_size_coord_matrix = MAX_NUM_COORDS*MAX_NUM_COORDS;
	//Default all the stored coefficients and coordinates to zero
	for(i=0; i<MAX_NUM_COORDS; i++)
	{
		coeff_vals[i] = 0;
	}
	
	for(i=0; i<max_size_coord_matrix; i++)
	{
		coord_matrix[i] = 0;
	}
	
	//Now check that the argument	provided is supported and initialise things from
	//the provided parameters.
	ret = init (&shape, &num_coords, argv[1]);
	if (ret != 0)
	{
		exit_prog (ret);
	}	

	//Check we have the correct values after initialisation
//	printf ("Shape is %d, Num coords is %d\n", shape, num_coords);
	
	//Now open the associated file and read the entire contents as characters
	ret = read_coord_data_from_file (&inp_buf_txt[0], argv[2]);
	if (ret != 0)
	{
		exit_prog (ret);
	}
	
	//For debugging, print out the data read from the file.
//	printf("String from file is %s\n", inp_buf_txt);

	//Parse the input string into separate double data types and place in array.
	ret = parse_input_string (num_coords, shape, inp_buf_txt, coord_matrix);
	if(ret != 0)
	{
		//Quit
		exit_prog (ERR_PARSE);
	}
	
//	for (i=0; i<max_size_coord_matrix; i++)
//	{
//		printf("Coord Matrix[%d] = %lf\n", i, coord_matrix[i]);
//	}

	//Now form each determinant in turn from the minors of the terms in the general 
	//equations and solve to get the coefficient of each term
	get_coefficients(shape, num_coords, coord_matrix, coeff_vals);

	//Now format the output and report the final equation for the shape.
	report_final_equation(num_coords, shape, coeff_vals);

	return 0;
}


//void* my_calloc (int num_blocks, int block_size)
//{
//	void *p;

//	p = (void *)calloc((size_t)num_blocks, (size_t)block_size);
	
//	if(p != 0)
//	{
//	 	printf ("Allocated address %p\n", p);
//	}

//	return p;
//}



void exit_prog (int ret)
{
	printf ("Exit program. Error %d\n", ret);
	exit(EXIT_FAILURE);
}
