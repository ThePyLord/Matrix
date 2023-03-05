#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "matrix.h"

Matrix construct(int rows, int cols)
{
	Matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mat.new_matrix[i][j] = 0;
		}
	}
	// Initialize the matrix shape
	mat.shape[0] = mat.rows;
	mat.shape[1] = mat.cols;

	return mat;
}

Matrix construct_arr(double *arr, int rows, int cols)
{
	Matrix mat;
	mat.rows = rows;
	mat.cols = cols;
	assert(mat.rows * mat.cols == rows * cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mat.new_matrix[i][j] = arr[i * cols + j];
		}
	}
	mat.shape[0] = mat.rows;
	mat.shape[1] = mat.cols;
	return mat;
}

Matrix add_matrix(const Matrix mat1, const Matrix mat2)
{

	Matrix res = construct(mat1.rows, mat1.cols);
	for (size_t i = 0; i < mat1.rows; i++)
	{
		for (size_t j = 0; j < mat1.cols; j++)
		{
			res.new_matrix[i][j] = mat1.new_matrix[i][j] + mat2.new_matrix[i][j];
		}
	}

	return res;
}

// Get the number of rows and columns from the user
// Create a function print_matrix() that takes a matrix as a parameter and prints it to the screen.
// First print the number of rows and columns, then print each element of the matrix.
void print_matrix(const Matrix *matrix)
{
	for (int i = 0; i < matrix->rows; i++)
	{
		printf("[");
		for (int j = 0; j < matrix->cols; j++)
		{
			printf("%.17g", matrix->new_matrix[i][j]);
			if (j == matrix->cols - 1)
			{
				printf("]\n");
			}
			else
			{
				printf(", ");
			}
		}
	}
	printf("\n");
}

void print_matrix_shape(const Matrix *matrix)
{
	printf("(%d, %d)\n", matrix->shape[0], matrix->shape[1]);
}

double getter(Matrix m, int r, int c)
{
	assert(r >= 0 && c >= 0 && r < MAX_ROWS && c < MAX_COLS);
	if (r >= 0 && c >= 0 && r < MAX_ROWS && c < MAX_COLS)
	{
		return m.new_matrix[r][c];
	}
	else
	{
		fprintf(stderr, "ERROR\n");
		exit(1);
	}
}

// Create a function that takes a matrix, row, column, and value as parameters and sets the value of the matrix at the given row and column to the given value.
void set_value(Matrix *matrix, int row, int col, double value)
{
	// set_value function for matrix
	assert(value < MAX_DBL && row >= 0 && col >= 0 && row <= matrix->rows && col <= matrix->cols);
	if (value < MAX_DBL && row >= 0 && col >= 0 && row <= matrix->rows && col <= matrix->cols)
	{
		matrix->new_matrix[row][col] = value;
		assert(value == getter(*matrix, row, col));
	}
	else
	{
		fprintf(stderr, "ERROR Setting value\n");
		exit(1);
	}
}

/**
 * @brief returns the identity matrix of size n
 * @param n size of the identity matrix
 * @return identity matrix of size n
 *
 */
Matrix identity_matrix(int n)
{
	assert(n > 0 && (n * n) <= MAX_ROWS);
	Matrix *mat = malloc(sizeof(Matrix));
	mat->rows = n;
	mat->cols = n;
	mat->shape[0] = n;
	mat->shape[1] = n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				mat->new_matrix[i][j] = 1;
				assert(mat->new_matrix[i][j] == 1);
			}
			else
			{
				mat->new_matrix[i][j] = 0;
			}
		}
	}
	assert(mat->new_matrix[0][0] == 1);
	return *mat;
}

Matrix transpose(const Matrix *m)
{
	Matrix res = construct(m->cols, m->rows);

	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			res.new_matrix[j][i] = m->new_matrix[i][j];
		}
	}

	return res;
}

bool shape_equal(const Matrix *mat1, const Matrix *mat2)
{
	assert(mat1->shape[0] == mat2->shape[0] && mat1->shape[1] == mat2->shape[1]);
	if (mat1->shape[0] == mat2->shape[0] && mat1->shape[1] == mat2->shape[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

Matrix sub_matrix(const Matrix *m1, const Matrix *m2)
{
	Matrix res = construct(m1->rows, m1->cols);
	if (shape_equal(m1, m2))
	{
		for (size_t i = 0; i < m1->rows; i++)
		{
			for (size_t j = 0; j < m1->cols; j++)
			{
				res.new_matrix[i][j] = m1->new_matrix[i][j] - m2->new_matrix[i][j];
			}
		}
		return res;
	}
	else
	{
		fprintf(stderr, "The shapes of the matrices are not the same.\n");
		exit(1);
	}
}

Matrix mult(Matrix *args, ...)
{
	va_list arg_list;
	va_start(arg_list, args);
	Matrix res = args[0];
	for (int i = 1; i < va_arg(arg_list, int); i++)
	{
		res = _multiply(&res, &args[i]);
	}
	va_end(arg_list);
	return res;
}

Matrix _multiply(const Matrix *m, const Matrix *n)
{
	assert(m->cols == n->rows);
	Matrix res = construct(m->rows, n->cols);
	for (size_t i = 0; i < m->rows; i++)
	{
		for (size_t j = 0; j < n->cols; j++)
		{
			for (size_t k = 0; k < m->cols; k++)
			{
				res.new_matrix[i][j] += m->new_matrix[i][k] * n->new_matrix[k][j];
			}
		}
	}
	return res;
}

void multiply(const Matrix *m, const Matrix *n, Matrix *result)
{
	assert(m->cols == n->rows);
	if (m->cols == n->rows)
	{
		*result = construct(m->rows, n->cols);

		for (size_t i = 0; i < m->rows; i++)
		{
			for (size_t j = 0; j < n->cols; j++)
			{
				int sum = 0;
				for (size_t k = 0; k < n->rows; k++)
				{
					// Print the computation
					// printf("(%g) * (%g) + ", m->new_matrix[i][k], n->new_matrix[k][j]);
					assert(m->new_matrix[i][k] < MAX_DBL && n->new_matrix[k][j] < MAX_DBL);
					sum += m->new_matrix[i][k] * n->new_matrix[k][j];
				}
				// printf("= %i\n", sum);
				set_value(result, i, j, sum);
			}
		}
		printf("\n");
	}
	else
	{
		fprintf(stderr, "ERROR: Improper dimensions!\n");
		exit(1);
	}
}

/**
 * @brief raises a matrix to the power of an integer
 *
 * @param m the matrix to be raised
 * @param exp the exponent
 * @return Matrix the resultant matrix
 */
Matrix power(Matrix *m, int exp)
{
	Matrix mat;
	if (m->cols == m->rows)
	{

		Matrix temp = *(m);
		mat.rows = m->rows;
		mat.cols = m->cols;
		if (exp == 0)
		{
			return identity_matrix(m->rows);
		}
		else if (exp == 1)
		{
			return *(m);
		}
		else if (exp > 1)
		{
			for (int i = 1; i < exp; i++)
			{
				multiply(&temp, m, &mat);
			}
		}
		else if (exp < 0)
		{
			for (int i = 1; i < -exp; i++)
			{
				multiply(&temp, m, &mat);
			}
			mat = transpose(&mat);
		}
	}
	else
	{
		fprintf(stderr, "ERROR: Improper dimensions!\n");
		exit(1);
	}
	return mat;
}

int determinant(const Matrix *m)
{
	int det = 0;
	if (m->cols == m->rows)
	{
		if (m->cols == 1)
		{
			return m->new_matrix[0][0];
		}
		else if (m->cols == 2)
		{
			return m->new_matrix[0][0] * m->new_matrix[1][1] - m->new_matrix[0][1] * m->new_matrix[1][0];
		}
		else
		{
			for (int i = 0; i < m->cols; i++)
			{
				Matrix temp = *(m);
				temp.new_matrix[0][i] = m->new_matrix[1][i];
				temp.new_matrix[1][i] = m->new_matrix[0][i];
				det += m->new_matrix[0][i] * determinant(&temp);
			}
		}
	}
	else
	{
		fprintf(stderr, "ERROR: Improper dimensions!\n");
		exit(1);
	}
	return det;
}

void fill_matrix(Matrix *m)
{
	for (size_t i = 0; i < m->rows; i++)
	{
		for (size_t j = 0; j < m->cols; j++)
		{
			m->new_matrix[i][j] = rand() % 10;
		}
	}
}

Matrix reshape(const Matrix *m, int r, int c)
{
	assert(r > 0 && c > 0);
	if (r * c == m->cols * m->rows)
	{
		int size = r * c;
		double *arr;
		arr = (double *)malloc(size * sizeof(double));
		int k = 0;
		for (size_t i = 0; i < m->rows; i++)
		{
			for (size_t j = 0; j < m->cols; j++)
			{
				arr[k] = m->new_matrix[i][j];
				k++;
			}
		}
		// Create the new matrix
		Matrix mat;
		mat.rows = r;
		mat.cols = c;
		mat.shape[0] = r;
		mat.shape[1] = c;
		// Pass the array's values into the new matrix
		for (size_t i = 0; i < r; i++)
		{
			for (size_t j = 0; j < c; j++)
			{
				mat.new_matrix[i][j] = arr[i * c + j];
			}
		}
		free(arr);
		return mat;
	}
	else
	{
		fprintf(stderr, "ERROR: Size %d doesn't match the size: %d of the input matrix!\n", r * c, m->cols * m->rows);
		exit(1);
	}
}

/**
 * @brief Overloaded multiplication function for scalar by matrix multiplication
 *
 * @param m the matrix to be multiplied
 * @param n the scalar to be multiplied
 * @return Matrix
 */
Matrix multiply_by_scalar(const Matrix *m, const double n)
{
	Matrix mat;
	mat = *m;
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			mat.new_matrix[i][j] = mat.new_matrix[i][j] * n;
		}
	}
	return mat;
}

double trace(const Matrix *matrix)
{
	double matTrace = 0;
	assert(matrix->rows == matrix->cols);
	for (size_t i = 0; i < matrix->rows; i++)
	{
		matTrace += matrix->new_matrix[i][i];
	}
	return matTrace;
}

Matrix divide_by_scalar(const Matrix *m, double num)
{
	Matrix *mat = malloc(sizeof(Matrix));
	return *mat;
}

/**
 * @brief Checks if a matrix is invertible(currently only works for 2x2 matrices)
 *
 * @param m the matrix to be multiplied
 * @return true if the matrix is invertible, false otherwise
 */
bool is_invertible(const Matrix *m)
{
	assert(m->rows == 2 && m->cols == 2);
	double det = determinant(m);
	bool is_invertible;
	if (det == 0)
	{
		is_invertible = false;
	}
	else
	{
		is_invertible = true;
	}
	return is_invertible;
}