#include "stdio.h"
#include "get_coefficients.h"
#include "gsl/gsl_linalg.h"
#include "shape.h"
#include "error_codes.h"
#include "calculate_coefficient.h"
#include "solve_gen_conic_dets.h"
#include "solve_circle_dets.h"
#include "solve_sphere_dets.h"
#include "solve_line_dets.h"
#include "solve_plane_dets.h"




void get_coefficients (SHAPE_TYPE shape, int num_coords, double *p_coord_matrix, double *p_coeffs)
{
	if(shape == LINE)
	{
    solve_line_dets(num_coords, p_coord_matrix, p_coeffs);		
	}
	else if(shape == PLANE)
	{
    solve_plane_dets(num_coords, p_coord_matrix, p_coeffs);
	}
	else if(shape == GENERAL_CONIC)
	{
		solve_gen_conic_dets(num_coords, p_coord_matrix, p_coeffs);
	}
	else if (shape == CIRCLE)
	{
    //Need to handle circles differently because
    //number of coordinates is not == dimension and coefficients are not linear
    solve_circle_dets(num_coords, p_coord_matrix, p_coeffs);
	}
	else if (shape == SPHERE)
	{
    //Need to handle spheres differently because
    //number of coordinates is not == dimension and coefficients are not linear
    solve_sphere_dets(num_coords, p_coord_matrix, p_coeffs);
	}
	else
	{
		printf("Unknown shape %d\n", shape);
		exit_prog(ERR_SHAPE_UNKNOWN);
	}
}


void report_final_equation (int num_coords, SHAPE_TYPE shape, double *p_coeffs)
{
	int i, num_coeffs, min_coeff;


	if (shape == LINE)
	{
		num_coeffs = 3;

		//Divide through by first coefficient to make first coefficient = 1.
		printf("Final equation: \n");
		printf("%lfx + %lfy + %lf = 0\n", p_coeffs[0]/p_coeffs[0],
																				p_coeffs[1]/p_coeffs[0],
																					p_coeffs[2]/p_coeffs[0]);
	}
	else if (shape == PLANE)
	{
		num_coeffs = 4;

    printf("Final equation: \n");
    printf("%lfx + %lfy + %lfz + %lf = 0\n", p_coeffs[0]/p_coeffs[0],
			                                        p_coeffs[1]/p_coeffs[0],
                                          			p_coeffs[2]/p_coeffs[0],
																									p_coeffs[3]/p_coeffs[0]);
	}
	else if (shape == CIRCLE)
	{
		num_coeffs = 4;

    printf("Final equation: \n");
    printf("%lf(x^2 + y^2) + %lfx + %lfy + %lf = 0\n", p_coeffs[0]/p_coeffs[0],
                                              					p_coeffs[1]/p_coeffs[0],
                                                					p_coeffs[2]/p_coeffs[0],
                                                  					p_coeffs[3]/p_coeffs[0]);
	}
	else if (shape == SPHERE)
	{
		num_coeffs = 5;

    printf("Final equation: \n");
    printf("%lf(x^2 + y^2 + z^2) + %lfx + %lfy + %lfz + %lf = 0\n", p_coeffs[0]/p_coeffs[0],
                                              												p_coeffs[1]/p_coeffs[0],
                                                												p_coeffs[2]/p_coeffs[0],
                                                  												p_coeffs[3]/p_coeffs[0],
																																						p_coeffs[4]/p_coeffs[0]);
	}
	else if (shape == GENERAL_CONIC)
	{
		num_coeffs = 6;

    printf("Final equation: \n");
    printf("%lfx^2 + %lfxy + %lfy^2 + %lfx + %lfy + %lf = 0\n", p_coeffs[0]/p_coeffs[0],
                                                                      p_coeffs[1]/p_coeffs[0],
                                                                        p_coeffs[2]/p_coeffs[0],
                                                                          p_coeffs[3]/p_coeffs[0],
                                                                            p_coeffs[4]/p_coeffs[0],
																																							p_coeffs[5]/p_coeffs[0]);
	}
	else
	{
		printf("Unknown Shape %d\n", shape);
		exit_prog(ERR_SHAPE_UNKNOWN);
	}
}

