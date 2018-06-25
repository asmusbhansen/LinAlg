/*
 * main.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"

int test1_matrix_memory_leak(int debug)
{
	
	struct matrix * matrix1;
	
	if(debug)
	{
		printf("Starting matrix memory leak test\n");
	}
	
	//Memory leak test	
	for(int i = 0; i < 50000000; i++)
	{
		matrix1 = allocate_matrix_mem(20, 20);
		if(matrix1 == 0)
		{
			return 0;
		}
		if(i%100000 == 0)
		{
			if(debug)
			{
				printf("%d\n",i);
			}
		}
		free_matrix_mem(matrix1);
	}
	
	return 1;
}

int test2_vector_memory_leak(int debug)
{
	struct vector * vector1;
	
	if(debug)
	{
		printf("Starting matrix memory leak test\n");
	}
	
	//Memory leak test	
	for(int i = 0; i < 100000000; i++)
	{
		vector1 = allocate_vector_mem(200);
		if(vector1 == 0)
		{
			return 0;
		}
		if(i%1000000 == 0)
		{
			if(debug)
			{
				printf("%d\n",i);
			}
		}
		free_vector_mem(vector1);
	}
	
	return 1;
}

int test3_matrix_compare(int debug)
{
	struct matrix * matrix1;
	struct matrix * matrix2;
	
	if(debug)
	{
		printf("Starting matrix multiplication test\n");
	}
	
	matrix1 = init_identity_matrix(5);
	
	matrix2 = init_identity_matrix(5);
	
	if(compare_matrix(matrix1, matrix2))
	{
		return 1;
	}
	
	return 0;
}

int test4_matrix_multiplication(int debug)
{
	
	struct matrix * matrix1;
	struct matrix * matrix2;
	struct matrix * matrix3;

	if(debug)
	{
		printf("Starting matrix multiplication test\n");
	}

	matrix2 = allocate_matrix_mem(2, 2); 
	if(matrix2 == 0)
	{
		printf("Allocation of matrix memory failed\n");
		return 0;
	}
	
	matrix2->matrix_mem[0][0] = 1;
	matrix2->matrix_mem[1][0] = 3;
	matrix2->matrix_mem[0][1] = 2;
	matrix2->matrix_mem[1][1] = 4;
	
	matrix1 = init_identity_matrix(2);
	
	if(debug)
	{
		
		printf("Multiplying: \n\n");
		
		print_matrix(matrix2);
		
		printf("With:\n\n");
		
		print_matrix(matrix1);
		
		printf("Resulting in:\n\n");
		
		matrix3 = mult_matrix(matrix1, matrix2);

		print_matrix(matrix3);
	
	}
	
	//Since matrix 2 is multiplied by the identity it should be the same as matrix3
	if(compare_matrix(matrix2, matrix3))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

int test5_extraction_vector_test(int debug)
{
	struct matrix * matrix1;
	struct vector * vector1;
	struct vector * vector2;
	
	int column_number = 0;
	
	if(debug)
	{
		printf("Starting vector extraction test\n");
	}
	
	matrix1 = init_identity_matrix(2);

	if(matrix1 == 0)
	{
		printf("Allocation of matrix memory failed\n");
		return 0;
	}
	
	//Init reference vector
	
	vector2 = allocate_vector_mem(2);
	if(vector2 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	vector2->vector_mem[0] = 1;
	vector2->vector_mem[1] = 0;
	
	
	vector1 = vector_from_matrix(matrix1, column_number);	
	
	if(debug)
	{
		
		printf("Extracting column number %d from the following matrix:\n\n", column_number);
		
		print_matrix(matrix1);
		
		printf("Resulting in:\n\n");
		
		print_vector(vector1);
	
	}
	
	//TO DO: Test with reference vector
	
	return 1;
	
}


int test6_vector_dot_product_test(int debug)
{
	struct vector * vector1;
	struct vector * vector2;
	double dot_product = 0;
	
	//Init vectors
	
	vector1 = allocate_vector_mem(3);
	if(vector1 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	vector1->vector_mem[0] = 2;
	vector1->vector_mem[1] = 4;
	vector1->vector_mem[2] = 2;
	
	
	vector2 = allocate_vector_mem(3);
	if(vector2 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	vector2->vector_mem[0] = 1;
	vector2->vector_mem[1] = 3;
	vector2->vector_mem[2] = 0.5;
	
	
	dot_product = vector_dot_product(vector1, vector2);
	
	if(debug)
	{
		
		printf("Taking dot product of:\n\n");
		
		print_vector(vector1);
		
		printf("And:\n\n");
		
		print_vector(vector2);
		
		printf("Resulting in %lf:\n\n", dot_product);
		
	}
	
	if(dot_product == 15)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}


int test7_vector_projection_test(int debug)
{
	
	struct vector * vector1;
	struct vector * vector2;
	struct vector * vector3;
	
	if(debug)
	{
		printf("Starting vector projection test\n");
	}
	
	vector1 = allocate_vector_mem(2);
	if(vector1 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	vector1->vector_mem[0] = 3;
	vector1->vector_mem[1] = 0;
	

	
	vector2 = allocate_vector_mem(2);
	if(vector2 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	vector2->vector_mem[0] = 2;
	vector2->vector_mem[1] = 2;
	
	vector3 = project_vector(vector1, vector2);
	
	
	if(debug)
	{
		printf("Projection of vector:\n\n");
		
		print_vector(vector2);
	
		printf("Onto vector:\n\n");
		
		print_vector(vector1);
	
		printf("Results in:\n\n");	
		
		print_vector(vector3);
		
	
	}
	
	return 1;
}

int test8_gs_orthogonalization_test(int debug)
{
	struct matrix * matrix1;
	struct matrix * result_matrix;

	matrix1 = allocate_matrix_mem(3,3);
	if(matrix1 == 0)
	{
		printf("Allocation of vector memory failed\n");
		return 0;
	}
	
	matrix1->matrix_mem[0][0] = 1;
	matrix1->matrix_mem[1][0] = 4;
	matrix1->matrix_mem[2][0] = 0;
	matrix1->matrix_mem[0][1] = 0;
	matrix1->matrix_mem[1][1] = 1;
	matrix1->matrix_mem[2][1] = 0;
	matrix1->matrix_mem[0][2] = -1;
	matrix1->matrix_mem[1][2] = 0;
	matrix1->matrix_mem[2][2] = 1;
	
	result_matrix = gs_orthogonalization(matrix1);
	
	if(debug)
	{
		printf("Input matrix:\n\n");
		
		print_matrix(matrix1);
		
		printf("Output orthogonal matrix:\n\n");
		
		print_matrix(result_matrix);
	}
	
	return 1;
	
}

int test9_qr_decomposistion_test(int debug)
{
	
	struct matrix * matrix1;
	struct matrix * qr;
	struct matrix * q;
	struct matrix * r;
		
	matrix1 = allocate_matrix_mem(3,3);
	if(matrix1 == 0)
	{
		printf("Allocation of matrix memory failed\n");
		return 0;
	}
	
	matrix1->matrix_mem[0][0] = 1;
	matrix1->matrix_mem[1][0] = 4;
	matrix1->matrix_mem[2][0] = 0;
	matrix1->matrix_mem[0][1] = 0;
	matrix1->matrix_mem[1][1] = 1;
	matrix1->matrix_mem[2][1] = 0;
	matrix1->matrix_mem[0][2] = -1;
	matrix1->matrix_mem[1][2] = 0;
	matrix1->matrix_mem[2][2] = 1;

	if(!qr_matrix(matrix1, &q, &r))
	{
		printf("QR Decomposistion failed\n\n");
		return 0;
	}
	
	//q_inv = transpose_matrix(q);
	
	if(debug)
	{
		
		printf("Input matrix:\n\n");
		
		print_matrix(matrix1);
		
		printf("Q matrix:\n\n");
		
		print_matrix(q);
		
		printf("R matrix:\n\n");
	
		print_matrix(r);
		
		printf("Q * R:\n\n");
		
		qr = mult_matrix(q,r);
		
		print_matrix(qr);
		
	}
	
	return 1;

}

int main(int argc, char **argv)
{
	
	/*
	if(test1_matrix_memory_leak(1))
	{
		printf("Matrix memory leak test succeded\n");
	}
	else
	{
		printf("Matrix memory leak test failed\n");
	}
	*/
	
	/*
	if(test2_vector_memory_leak(1))
	{
		printf("Vector memory leak test succeded\n");
	}
	else
	{
		printf("Vector memory leak test failed\n");
	}
	*/
	
	/*
	if(test3_matrix_compare(1))
	{
		printf("Matrix compare test succeded\n");
	}
	else
	{
		printf("Matrix compare test failed\n");
	}
	
	
	
	if(test4_matrix_multiplication(1))
	{
		printf("Matrix multiplication test succeded\n");
	}
	else
	{
		printf("Matrix multiplication test failed\n");
	}
	
	if(test5_extraction_vector_test(1))
	{
		printf("Vector extraction test succeded\n");
	}
	else
	{
		printf("Vector extraction test failed\n");
	}
	
	
	if(test6_vector_dot_product_test(1))
	{
		printf("Dot product test succeded\n");
	}
	else
	{
		printf("Dot product test failed\n");
	}
	*/
	
	/*
	if(test7_vector_projection_test(1))
	{
		printf("Vector projection test succeded\n");
	}
	else
	{
		printf("Vector projection test failed\n");
	}
	
	
	if(test8_gs_orthogonalization_test(1))
	{
		printf("Vector orthogonalization test succeded\n");
	}
	else
	{
		printf("Vector orthogonalization test failed\n");
	}
	*/
	
	if(test9_qr_decomposistion_test(1))
	{
		printf("Vector qr decomposistion test succeded\n");
	}
	else
	{
		printf("Vector qr decomposistion test failed\n");
	}
	
	
	
	
	return 1;
}


