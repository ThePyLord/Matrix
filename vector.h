// Create a header file for a vector struct.
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <float.h>
#include <stdarg.h>

typedef struct vector
{
	double x;
	double y;
	double z;
} vector;

typedef struct vect
{
	double *components;
	int size;
} Vector;

Vector *new_vector(int args, ...);
Vector *norm_vec(Vector *v);
double mag_vec(Vector *v);
// Vector *add_vec(Vector *v1, Vector *v2);
// Vector *sub_vec(Vector *v1, Vector *v2);

double dot_product(Vector *v1, Vector *v2);
vector *add_vector(vector *v1, vector *v2);
vector *sub_vector(vector *v1, vector *v2);
vector *mult_vector(vector *v1, double scalar);
vector *div_vector(vector *v1, double scalar);
vector *cross_vector(vector *v1, vector *v2);
// double mag_vector(vector *v1);
// vector *norm_vector(vector *v1);
vector *rotate_vector(vector *v, double theta, vector *axis);

void print_vector(vector *v1);
void print_vec(Vector *v);

#endif