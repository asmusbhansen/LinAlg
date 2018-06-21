/** linalg.h
* 
* Implementation of some linear algebra operations 
*
*/ 

#ifndef _LINALG_H
#define _LINALG_H

struct matrix {
	
	int rows, cols;
	
	/*
	 * Each entry in the matrix if of the type double
	 * The pointer matrix_mem points to a specific row
	 * which in turn points to an columns(array), hence the 
	 * type pointer pointer.
	 * Indexing in the matrix is: matrix_mem[m][n]
	 * This yields the number in row m columns n 
	*/
	double ** matrix_mem;
	
}matrix;

struct vector {
	
	int dim;
	
	double * vector_mem;
	
}vector;


struct matrix * mult_matrix(struct matrix * a, struct matrix * b);
int compare_matrix(struct matrix * a, struct matrix * b);
struct matrix * allocate_matrix_mem(int m, int n);
struct vector * allocate_vector_mem(int d);
void free_matrix_mem(struct matrix * m);
void free_vector_mem(struct vector * a);
void print_matrix(struct matrix * m);
void print_vector(struct vector * a);
struct matrix * init_identity_matrix(int m);
struct matrix * transpose_matrix(struct matrix * input);
struct vector * vector_from_matrix(struct matrix * input, int n);
//Vect to matrix
struct vector * subtract_vector(struct vector * v1, struct vector * v2);
struct vector * add_vector(struct vector * v1, struct vector * v2);
struct vector * scale_vector(struct vector * v1, double s);

struct vector * project_vector(struct vector * v1, struct vector * v2);


double vector_dot_product(struct vector * v1, struct vector * v2);
int qr_matrix(struct matrix * input, struct matrix * q, struct matrix * r);
int svd_matrix(struct matrix * input, struct matrix * s, struct matrix * v, struct matrix * d);
int eig_matrix(struct matrix * input, struct matrix * l, struct matrix * v);


#endif /* _LINALG_H */
