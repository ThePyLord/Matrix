#ifndef REWRITE_H
#define REWRITE_H
#include <float.h>
#include <stdbool.h>
#define MAX_INPUT 50
#define MAX_ROWS 150
#define MAX_COLS 150
#define MAX_DBL 300

typedef struct MATRIX
{
    int rows;
    int cols;
    int shape[2];
    double new_matrix[MAX_ROWS][MAX_COLS];
} Matrix;

void print_matrix(const Matrix *matrix);
void print_matrix_shape(const Matrix *matrix);
void setter(Matrix m, int r, int c, double value);
void fill_matrix(Matrix *m);
bool shape_equal(const Matrix *m1, const Matrix *m2);
double getter(Matrix m, int r, int c);
double trace(const Matrix *matrix);
// int determinant(const Matrix* m);

Matrix add_matrix(const Matrix mat1, const Matrix mat2);
Matrix construct(int rows, int cols);
Matrix construct_arr(double *arr, int rows, int cols);
Matrix identity_matrix(int n);
Matrix reshape(const Matrix *m, int r, int c);
Matrix reshape1(const Matrix *m, int shape[2]);
void multiply(const Matrix *m, const Matrix *n, Matrix *result);
Matrix _multiply(const Matrix *m, const Matrix *n);
Matrix mult(Matrix *args, ...);
bool is_invertible(const Matrix *m);
Matrix power(Matrix *mat, int exp);
Matrix sub_matrix(const Matrix *m1, const Matrix *m2);
Matrix transpose(const Matrix *m);
Matrix divide_by_scalar(const Matrix *m, double num);
Matrix multiply_by_scalar(const Matrix *m, double n);

#endif
