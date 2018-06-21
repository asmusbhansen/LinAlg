/** linalg.c
* 
* Implementation of some linear algebra operations 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "linalg.h"

/* 
 * @Param a: Matrix 1 to be multiplied
 * @Param n: Matrix 2 to be multiplied
 * @Return: Ptr to resulting matrix 
 */
struct matrix * mult_matrix(struct matrix * a, struct matrix * b)
{
	
	struct matrix * res_matrix;
	
	if(a->cols != b->rows)
	{
		printf("Wrong matrix dimensions\n");
		return 0;
	}

	
	//A m1 by n1 matrix multiplied by a m2 by n2 matrix yields a m1 by n2 matrix. 
	//Allocate memory for new matrix
	
	// Matrix multiplication example
	//
	//| 1 0 |   | 2 1 |   | 2 1 |
 	//| 2 1 | x | 2 2 | = | 6 4 |
	
	res_matrix = allocate_matrix_mem(a->rows, b->cols);
	if(res_matrix == 0)
	{
		return 0;
	}
	
	for(int k = 0; k < a->rows; k++)
	{
	
		for(int i = 0; i < b->cols; i++)
		{
	
			for(int j = 0; j < a->cols; j++)
			{

				res_matrix->matrix_mem[k][i] += a->matrix_mem[k][j] * b->matrix_mem[j][i];
				
			}
	
		} 
	
	}	
	
	return res_matrix;
}

/* 
 * @Param a: Matrix 1 to be compared
 * @Param n: Matrix 2 to be compared
 * @Return: 1 if equal, 0 if not 
 */
int compare_matrix(struct matrix * a, struct matrix * b)
{
		
	if(a->rows != b->rows || a->cols != b->cols)
	{
		return 0;
	}
	 
	for(int i = 0; i < a->rows; i++)
	{
		
		for(int j = 0; j < a->cols; j++)
		{
			
			//printf("%lf, %lf\n\n",a->matrix_mem[i][j], b->matrix_mem[i][j]);
			
			if(a->matrix_mem[i][j] != b->matrix_mem[i][j])
			{
				return 0;
			}
			
		}
		
	}
	 
	return 1;
 
}


/* 
 * @Param m: Number of rows
 * @Param n: Number of columns
 * @Return: Ptr to allocated matrix 
 */
struct matrix * allocate_matrix_mem(int m, int n)
{
	//Allocate memory for matrix struct
	struct matrix * mtrix = malloc(sizeof(struct matrix));
	
	//printf("Trying to allocate %lu bytes of memory for matrix struct\n", sizeof(struct matrix));
	
	if(mtrix == 0)
	{
		//printf("Failed allocation of matrix struc memory\n");
		return 0;
	}
	
	mtrix->rows = m;
	
	mtrix->cols = n;
	
	//printf("Trying to allocate %lu bytes of memory for matrix data\n", (mtrix->rows)*(mtrix->cols)*sizeof(double));
	
	//Allocate memory for pointer to each row
	mtrix->matrix_mem = malloc((mtrix->rows)*sizeof(double *));	
	
	if(mtrix->matrix_mem == 0)
	{
		return 0;
	}
	
	
	for(int i = 0; i < mtrix->rows; i++)
	{
		//For each row, allocate memory for each column entry
		mtrix->matrix_mem[i] = malloc((mtrix->cols)*sizeof(double));
		if(mtrix->matrix_mem[i] == 0)
		{
			return 0;
		}
	}
		
	return mtrix;
	
}

/* 
 * @Param d: Dimension of vector
 * @Return: Ptr to allocated vector
 */
struct vector * allocate_vector_mem(int d)
{
	//Allocate memory for vector struct
	struct vector * vect = malloc(sizeof(struct vector));
	
	//printf("Trying to allocate %lu bytes of memory for vector struct\n", sizeof(struct vector));
	
	if(vect == 0)
	{
		//printf("Failed allocation of vector struc memory\n");
		return 0;
	}
	
	vect->dim = d;
	
	//Allocate memory vector 
	vect->vector_mem = malloc((vect->dim)*sizeof(double));	
	
	if(vect->vector_mem == 0)
	{
		return 0;
	}
		
	return vect;
	
}



/*
 * @Param a: Ptr to matrix
 * @Return: void 
 */
void free_matrix_mem(struct matrix * a)
{
	//Free allocated space for matrix data
	
	for(int i = 0; i < a->rows; i++)
	{
		free(a->matrix_mem[i]);
	}
	
	free(a->matrix_mem);

}

/*
 * @Param a: Ptr to vector
 * @Return: void 
 */
void free_vector_mem(struct vector * a)
{
	//Free allocated space for vector data
	
	free(a->vector_mem);

}


/*
 * @Param a: Ptr to matrix
 * @Return: Void
 */
void print_matrix(struct matrix * a)
{
	int rows = a->rows;
	int cols = a->cols;
	
	for(int i = 0; i < rows; i++)
	{
		printf("| ");
		for(int j = 0; j < cols; j++)
		{
			
			printf("%lf ", a->matrix_mem[i][j]);
			
		}
		printf("|");
		
		printf("\n\n");
		
	}
	
}

/*
 * @Param a: Ptr to matrix
 * @Return: Void
 */
void print_vector(struct vector * a)
{
	int dim = a->dim;
	
	for(int i = 0; i < dim; i++)
	{
		printf("| ");
		printf("%lf ", a->vector_mem[i]);
		printf("|");
		
		printf("\n\n");
		
	}
	
}

/*
 * @Param m: Number of rows and columns
 * @Return: Ptr to identity matrix
 */
struct matrix * init_identity_matrix(int m)
{
	
	struct matrix * res_matrix = allocate_matrix_mem(m, m);
		
	if(res_matrix == 0)
	{
		return 0;
	}
	
	
	for(int i = 0; i < res_matrix->rows; i++)
	{
		
		for(int j = 0; j < res_matrix->cols; j++)
		{
			
			if(i == j)
			{
				res_matrix->matrix_mem[i][j] = 1;
			}
			else
			{
				res_matrix->matrix_mem[i][j] = 0;
			}
			
		}
		
	}
	
	return res_matrix;

}

/* 
 * @Param input: Function computes the transpose of this matrix
 * @Return: Return a pointer to the transposed matrix
 */
 struct matrix * transpose_matrix(struct matrix * input)
 {
	 
	struct matrix * res_matrix = allocate_matrix_mem(input->cols, input->rows);
		
	if(res_matrix == 0)
	{
		return 0;
	}
	 
	for(int i = 0; i < input->rows; i++)
	{
		
		for(int j = 0; j < input->cols; j++)
		{
			
			res_matrix->matrix_mem[j][i] = input->matrix_mem[i][j];
			
		}
		
	}
	 
	return res_matrix;
 
 }
 
 
/* 
 * @Param input: Input matrix
 * @Param m: Function extracts the m'th column as a vector
 * @Return: Vector pointer 
 */
 struct vector * vector_from_matrix(struct matrix * input, int n)
 {
	 
	struct vector * res_vector; 
	
	res_vector = allocate_vector_mem(input->rows);
	
		
	if(res_vector == 0)
	{
		return 0;
	}
	
	 
	for(int i = 0; i < input->rows; i++)
	{
		 
	 res_vector->vector_mem[i] = input->matrix_mem[i][n];
		 
	}
	 	 
	return res_vector;
 
}

/* 
 * @Param v1: Vector 1
 * @Param v1: Vector 2
 * @Return: result vector = v1 - v2 
 */
struct vector * subtract_vector(struct vector * v1, struct vector * v2)
{
	
	struct vector * res_vector; 
	
	res_vector = allocate_vector_mem(v1->dim);
	
		
	if(res_vector == 0)
	{
		return 0;
	}
	
	if(v1->dim != v2->dim)
	{
		printf("Vectors not same dimension\n");
		return 0;
	}
	
	for(int i = 0; i < v1->dim; i++)
	{
		 
	 res_vector->vector_mem[i] = v1->vector_mem[i] - v2->vector_mem[i];
		 
	}
	 	 
	return res_vector;
	
	
}

/* 
 * @Param v1: Vector 1
 * @Param v1: Vector 2
 * @Return: result vector = v1 + v2 
 */
struct vector * add_vector(struct vector * v1, struct vector * v2)
{
	
	struct vector * res_vector; 
	
	res_vector = allocate_vector_mem(v1->dim);
	
		
	if(res_vector == 0)
	{
		return 0;
	}
	
	if(v1->dim != v2->dim)
	{
		printf("Vectors not same dimension\n");
		return 0;
	}
	
	for(int i = 0; i < v1->dim; i++)
	{
		 
	 res_vector->vector_mem[i] = v1->vector_mem[i] + v2->vector_mem[i];
		 
	}
	 	 
	return res_vector;
	
}

/* 
 * @Param v1: Vector 1
 * @Param s: Scale factor
 * @Return: v1 * s 
 */
struct vector * scale_vector(struct vector * v1, double s)
{
	
	struct vector * res_vector; 
	
	res_vector = allocate_vector_mem(v1->dim);
	
		
	if(res_vector == 0)
	{
		return 0;
	}
	
	
	for(int i = 0; i < v1->dim; i++)
	{
		 
	 res_vector->vector_mem[i] = v1->vector_mem[i] * s;
		 
	}
	 	 
	return res_vector;
	
}


/* 
 * @Param v1: Vector 1
 * @Param v1: Vector 2
 * @Return: Projection of v2 onto v1
 */
struct vector * project_vector(struct vector * v1, struct vector * v2)
{
	struct vector * temp_vector;
	struct vector * res_vector;
	double dot_product;
	
	
	//Projection og v2 onto v1: |v2| * cos(phi)
	//Cos(phi) can be foundfrom dot product definition
	// v1 dot v2 = |v1| * |v2| * cos(phi)
	// v1 dot v2 / ( |v1| * |v2| )= cos(phi)
	// |v2| * v1 dot 2 / ( |v1| * |v2| ) - Where |v2| cancels
	// v1 dot v2 / ( |v1| ) - here the lenght squared of v1 is v1' dot v1 where"'" is the transpose
	
	dot_product = vector_dot_product(v1, v1);
	
	temp_vector = scale_vector(v1, 1/dot_product);
	
	//Unit length v1 dot v2
	dot_product = vector_dot_product(temp_vector, v2);
		
	res_vector = scale_vector(v1, dot_product);	
	
	return res_vector;
}

/* 
 * @Param v1: Vector 1
 * @Param v1: Vector 2
 * @Return: Dot product of vector 1 and vector 2 
 */
 double vector_dot_product(struct vector * v1, struct vector * v2)
 {
	 
	double dot_product = 0; 
	 
	if(v1->dim != v2->dim)
	{
		printf("Vector dimensions does not match, dot product is not well defined\n");
		return 0;
	}
	 
	for(int i = 0; i < v1->dim; i++)
	{
		 
	 dot_product += v1->vector_mem[i] * v2->vector_mem[i];
		 
	}
	 	 
	return dot_product;
 
 } 

/* 
 * @Param input: Function computes the qr factorization of this matrix
 * @Param q: Q matrix in the QR factorization
 * @Param R: R matrix in the QR factorization
 * @Return: 1 if succesfull, 0 if not 
 */
 int qr_matrix(struct matrix * input, struct matrix * q, struct matrix * r)
 {
	 
	 
	 
	 return 1;
 }
 
 

/* 
 * @Param input: Function computes the svd of this matrix
 * @Param s: S matrix in the SVD transform
 * @Param v: V matrix in the SVD transform
 * @Param d: D matrix in the SVD transform
 * @Return: 1 if succesfull, 0 if not 
 */
 int svd_matrix(struct matrix * input, struct matrix * s, struct matrix * v, struct matrix * d)
 {
	 
	 
	 
	 return 1;
 }

/* 
 * @Param input: Function computes the eigenvalues and eigenvectors of this matrix
 * @Param l: Eigenvalue matrix
 * @Param v: Eigenvector matrix
 * @Return: 1 if succesfull, 0 if not 
 */
 int eig_matrix(struct matrix * input, struct matrix * l, struct matrix * v)
 {
	 
	 
	 
	 return 1;
 }

