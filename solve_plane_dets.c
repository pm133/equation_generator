#include "stdio.h"
#include "shape.h"
#include "get_coefficients.h"
#include "calculate_coefficient.h"
#include "solve_plane_dets.h"



void solve_plane_dets (int num_coords, double *p_coord_matrix, double *p_coeffs)
{
  double *pcoord, *pcoeffs;
  double determinant[MAX_NUM_COORDS][MAX_NUM_COORDS];
  int coeff_index, det_row_index, det_col_index;
  int i,j;


  pcoord = p_coord_matrix;
  pcoeffs = p_coeffs;

  //Start at the first coefficient which is x.
  //The other columns are y, z and constant.
  //Fill in the first column of the corresponding 3x3 determinant for this 
  //first coefficient.

  //NOTE: LU decomposition destroys contents of determinant so must fill
  //out completely every time we calculate a new coefficient even though
  //only one column changes at a time between coefficients.
  coeff_index = 0; //for first coeff - x

  //First the y column values for the x coeff
  det_col_index = 0;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Y_POS]; 
  }

  //Next the z column values for the x coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Z_POS];
  }

  //Finally the remaining constant column values for the x coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] = 1;
  }

  //The determinant for the x coefficient is now complete

//    printf("Co-efficient: %d\n", coeff_index);

//    for(det_row_index=0; det_row_index<num_coords; det_row_index++)
//    {
//      for(det_col_index=0; det_col_index<num_coords; det_col_index++)
//      {
//        printf("determinant[%d][%d] = %lf\n", det_row_index,
//                          det_col_index, determinant[det_row_index][det_col_index]);
//      }
//    }


  //We now have the determinant for the x coefficient. Solve the determinant
  //to get the numerical value of the coefficient.
  pcoeffs[coeff_index] = calculate_coefficient (coeff_index, num_coords, &determinant[0][0]);



/****************************/


  coeff_index++; //for second coeff - y

  //First the x column values for the y coeff
  det_col_index = 0;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + X_POS];
  }

  //Next the z column values for the y coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Z_POS];
  }

  //Finally the remaining constant column values for the y coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] = 1;
  }
  //The determinant for the y coefficient is now complete

//    printf("Co-efficient: %d\n", coeff_index);

//    for(det_row_index=0; det_row_index<num_coords; det_row_index++)
//    {
//      for(det_col_index=0; det_col_index<num_coords; det_col_index++)
//      {
//        printf("determinant[%d][%d] = %lf\n", det_row_index,
//                          det_col_index, determinant[det_row_index][det_col_index]);
//      }
//    }


  //We now have the determinant for the y coefficient. Solve the determinant
  //to get the numerical value of the coefficient.
  pcoeffs[coeff_index] = calculate_coefficient (coeff_index, num_coords, &determinant[0][0]);



/****************************/



  coeff_index++; //for third coeff - z

  //First the x column values for the z coeff
  det_col_index = 0;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + X_POS];
  }

  //Next the y column values for the z coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Y_POS];
  }

  //Finally the remaining constant column values for the z coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] = 1;
  }

  //The determinant for the z coefficient is now complete

//    printf("Co-efficient: %d\n", coeff_index);

//    for(det_row_index=0; det_row_index<num_coords; det_row_index++)
//    {
//      for(det_col_index=0; det_col_index<num_coords; det_col_index++)
//      {
//        printf("determinant[%d][%d] = %lf\n", det_row_index,
//                          det_col_index, determinant[det_row_index][det_col_index]);
//      }
//    }


  //We now have the determinant for the z coefficient. Solve the determinant
  //to get the numerical value of the coefficient.
  pcoeffs[coeff_index] = calculate_coefficient (coeff_index, num_coords, &determinant[0][0]);



/****************************/



  coeff_index++; //for final coeff - constant

  //First the x column values for the constant coeff
  det_col_index = 0;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + X_POS];
  }

  //Next the y column values for the constant coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Y_POS];
  }

  //Finally the z column values for the constant coeff
  det_col_index++;
  for (det_row_index=0; det_row_index < NUM_PLANE_COORDS; det_row_index++)
  {
    determinant[det_row_index][det_col_index] =
                pcoord[det_row_index*NUM_PLANE_DIMENSIONS + Z_POS];
  }

  //The determinant for the constant coefficient is now complete

//    printf("Co-efficient: %d\n", coeff_index);

//    for(det_row_index=0; det_row_index<num_coords; det_row_index++)
//    {
//      for(det_col_index=0; det_col_index<num_coords; det_col_index++)
//      {
//        printf("determinant[%d][%d] = %lf\n", det_row_index,
//                          det_col_index, determinant[det_row_index][det_col_index]);
//      }
//    }


  //We now have the determinant for the constant coefficient. Solve the determinant
  //to get the numerical value of the coefficient.
  pcoeffs[coeff_index] = calculate_coefficient (coeff_index, num_coords, &determinant[0][0]);
}
