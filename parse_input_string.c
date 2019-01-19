#include "stdio.h"
#include "stdlib.h"
#include "error_codes.h"
#include "parse_input_string.h"
#include "file_access.h"
#include "shape.h"


static char* skip_white(char *pbuf);
static char* get_digit (char *pbuf, char *tmp_buf);

typedef enum
{
	FALSE=0,
	TRUE

} BOOL;



ERROR_CODES parse_input_string (int num_coords, SHAPE_TYPE shape, char *p_inp_buf, double *p_coord_matrix)
{
	ERROR_CODES ret = ERR_OK;
	char *pbuf;
	double *pcoord;
	int nc_check, actual_size_of_coord_matrix;
	char tmp_buf[MAX_FILE_SIZE];
	int loop;


	tmp_buf[0] = '\0';
	pbuf = p_inp_buf;
	pcoord = p_coord_matrix;
	//In reality not all of the coordinate matrix is needed.
	//Determine actual size needed. This will be the number of coords
	//multiplied by the dimension of the shape. For a line this will
	//be 3 coordinates for the unknowns and 3 dimensions - x, y, z.
	switch (shape)
	{
		case LINE:
		case PLANE:
			//For both line and plane, number of coords = num dimensions
			actual_size_of_coord_matrix = num_coords*num_coords;
		break;

		case CIRCLE:
		case GENERAL_CONIC:
			//For circle and general conic, num coords is 3 and num dimensions is 2 - x and y.
			actual_size_of_coord_matrix = num_coords*2;
		break;

		case SPHERE:
			//For sphere, dimensions are 3 - x, y, and z
      actual_size_of_coord_matrix = num_coords*3;
		break;

		default:
			printf("Unsupported shape type %d\n", shape);
			exit_prog(ERR_SHAPE_UNKNOWN);
		break;
	}		
	
	//Repeat until we have recovered all expected coord matrix elements
	for (nc_check=0; nc_check<actual_size_of_coord_matrix; nc_check++)
	{
		//Co-ordinates are double types separated by spaces. 
		//Subsequent sets of co-ordinates are separated by a comma
		//Firstly, remove all preceding white space
		pbuf = skip_white (pbuf);
	
		//Now we are at the first actual character
		//Now collect the first digit
		pbuf = get_digit (pbuf, tmp_buf);	

//		printf("Pointing at %p and %p\n", pbuf, tmp_buf);
//		printf("digit recovered is %s\n", tmp_buf);

		//Convert digit to a double number from a string
		//and store in correct place in matrix.
		//Matrix elements stored one row at a time.
		p_coord_matrix[nc_check] = atof(tmp_buf);
//    printf("Test digit * 4 = %lf\n", p_coord_matrix[nc_check]*4);

		//Have we reached a comma? If so we need to skip it
		//If we have received a NULL, ensure we have got the
		//expected number of digits read in.
		if (*pbuf == ',')
		{
			pbuf++;
		}
		else if ((*pbuf == ';') || (*pbuf == '\0'))
		{
			if (nc_check == (actual_size_of_coord_matrix-1))
			{
				//Do nothing. We have finished.
			}
			else
			{
				//We have an error.
				ret = ERR_PARSE;
			}
		}
		else
		{
			//Do nothing. Continue with next digit.
		}
	}

//	for(loop=0; loop<actual_size_of_coord_matrix; loop++)
//	{
//		printf("Coord Matrix[%d] = %lf\n", loop, p_coord_matrix[loop]);
//	}

	return ret;
}



static char* skip_white(char *pbuf)
{
	while (*pbuf == ' ')
	{
		pbuf++;
	}

	return pbuf;
}


static char* get_digit (char *pbuf, char *tmp_buf)
{
	int dec_place_used = 0;
	//Use first_char to ensure a minus sign can only appear at start of digit.
  BOOL first_char = TRUE;


	//Next digit terminated by either a space, comma, semi-colon or NULL
	while ((*pbuf != ' ') && (*pbuf != ',') && (*pbuf != ';') && (*pbuf != '\0'))
	{
		//The actual digit will be transformed to a double type.
		//So each character retrieved must be in the range 0 to 9
		//Also, only one decimal point can be present. If either 
		//condition is not fulfilled we exit the program. Check for
		//a second decimal point first.
		if(*pbuf == '.')
		{	
			if (dec_place_used == 0)
			{
				//Prevent second dec point.
				dec_place_used = 1;
			}
			else
			{
				//We have received a second decimal point for this number.
				//Unrecoverable error.
				exit_prog (ERR_PARSE_DEC);
			}
		}
		else if (*pbuf == '-')
		{
			if (first_char == TRUE)
			{
				//Do nothing. Let minus sign go into buffer	
			}
			else
			{
				//Unexpectedly read a negative sign midway through the digit string
				exit_prog (ERR_PARSE_NEG);
			}
		}
		else if ((*pbuf < '0') || (*pbuf > '9'))
		{
			//character is not a decimal digit.
			//Unrecoverable error.
			printf("char is %c\n", *pbuf);
			exit_prog (ERR_PARSE_RANGE);
		}
		else
		{
			//Do nothing. Normal decimal digit or we are at the end of the list of coords or the
			//end of the input string.
		}

		*tmp_buf++ = *pbuf++;
		first_char = FALSE;
	}

	//Null terminate the digit string
	*tmp_buf = '\0';

	return pbuf;
}
