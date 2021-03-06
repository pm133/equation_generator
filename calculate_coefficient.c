#include "stdio.h"
#include "gsl/gsl_linalg.h"
#include "shape.h"


double calculate_coefficient (int coeff_index, int num_coords, double *p_determinant)
{
	gsl_matrix A_matrix;
	double det_val;
	gsl_permutation *p_permutation;
	int i, signum;	


	A_matrix.size1 = num_coords;
	A_matrix.size2 = num_coords;
	A_matrix.tda   = MAX_NUM_COORDS;
	A_matrix.data  = p_determinant;
	A_matrix.block = NULL;
	A_matrix.owner = 0;

	printf("A_matrix.size1 = %ld, A_matrix_size2 = %ld, A_matrix.tda = %ld\n", 
							A_matrix.size1, A_matrix.size2, A_matrix.tda);

  for (i=0; i<(MAX_NUM_COORDS*MAX_NUM_COORDS); i++)
	{
		printf("A_matrix.data[%d] = %lf \n", i, A_matrix.data[i]);
	}
	
//  p_permutation = gsl_permutation_calloc (MAX_NUM_COORDS*MAX_NUM_COORDS);
	p_permutation = gsl_permutation_calloc (num_coords);
	
	gsl_linalg_LU_decomp(&A_matrix, p_permutation, &signum);

	det_val = gsl_linalg_LU_det(&A_matrix, signum);

	gsl_permutation_free (p_permutation);

	//Even coefficient indices have their determinant values negated
	if ((coeff_index % 2) == 0)
	{
		det_val = -det_val;
	}

	return det_val;
}

