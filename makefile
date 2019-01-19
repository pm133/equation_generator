#///////////////////////////////////////////////////
#//
#//  Program created by Paul Murphy
#//  
#//  This is a C program which generates the equation
#//	 for a range of shape types - line, plane, circle, sphere and conic.
#//  Comments and feedback are welcome
#//  by email - pm133@hotmail.co.uk.
#//
#//  MAKEFILE
#//  --------
#//  Version History: 1.0 - 31/12/2015
#//
#///////////////////////////////////////////////////
#DEST = ./
#OBJS = main.o init.o file_access.o parse_input_string.o get_coefficients.o solve_gen_conic_dets.o calculate_coefficient.o solve_circle_dets.o solve_sphere_dets.o solve_line_dets.c solve_plane_dets.c
equation_generator_version_1_0: main.c init.c file_access.c parse_input_string.c get_coefficients.c solve_gen_conic_dets.c calculate_coefficient.c solve_circle_dets.c solve_sphere_dets.c solve_line_dets.c solve_plane_dets.c
	gcc -o equation_generator_version_1_0 main.c init.c file_access.c parse_input_string.c get_coefficients.c solve_gen_conic_dets.c calculate_coefficient.c solve_circle_dets.c solve_sphere_dets.c solve_line_dets.c solve_plane_dets.c -I. -lm -lgsl -lgslcblas
