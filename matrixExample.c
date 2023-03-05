#include "matrix.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	double mat1[] = {0, -1, 0, 1, 1, 1};
	double mat2[] = {1, 2, 3, 4, 1, 1, -2, 0};

	Vector *vec1 = new_vector(3, 1., -2., 1.);
	Vector *vec2 = new_vector(3, 3., 0., 2.);
	print_vec(vec1);
	print_vec(vec2);
	printf("Dot product: %.17g\n", dot_product(vec1, vec2));
	// print_vec(dot_product(vec1, vec2));
	// free(vec1);
	Matrix a = construct_arr(mat1, 3, 2);
	Matrix b = construct_arr(mat2, 2, 4);
	Matrix aTranspose = transpose(&b);
	int det = determinant(&a);
	// Matrix result;
	// multiply(&a, &b, &result);
	// Matrix rTranspose = transpose(&result);
	// // multiply(&b, &result, &result);
	// printf("Printing the final result:\n");
	// print_matrix(&result);
	// print_matrix(&rTranspose);


	return 0;
}
