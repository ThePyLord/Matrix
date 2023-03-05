#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #include <float.h> // For formatting output
#include "vector.h"

/**
 * Create a new vector
 * @param args The number of arguments
 * @param ... The arguments
 * @return The new vector
 * @note The arguments are the elements of the vector
 * @note The number of arguments must be equal to the number of elements
 */
Vector *new_vector(int args, ...)
{
	Vector *v = (Vector *)malloc(sizeof(Vector));
	va_list arg_list;
	va_start(arg_list, args);
	v->size = args;
	v->components = (double *)malloc(sizeof(double) * args);
	for (size_t i = 0; i < args; i++)
	{
		v->components[i] = va_arg(arg_list, double);
	}
	va_end(arg_list);
	free(arg_list);
	return v;
}

/**
 * Get the magnitude of a vector
 * @param v The vector
 * @return The magnitude of the vector
 * @note The magnitude is the square root of the sum of the squares of the components
 * @note The magnitude is the same as the length of the vector
 * @note The magnitude is the same as the norm of the vector
 */
double mag_vec(Vector *v)
{
	double sum = 0;
	for (size_t i = 0; i < v->size; i++)
	{
		assert(v->components[i] > 0);
		sum += (v->components[i] * v->components[i]);
	}
	assert(sqrt(sum) > 0);
	return sqrt(sum);
}

Vector *norm_vec(Vector *v)
{
	double mag = mag_vec(v);
	assert(mag > 0);
	for (size_t i = 0; i < v->size; i++)
	{
		assert(v->components[i] > 0);
		v->components[i] /= mag;
	}
	return v;
}

void print_vec(Vector *v)
{
	printf("Vector: \n");
	printf("\tSize: %i\n", v->size);
	printf("\t( ");
	for (size_t i = 0; i < v->size; i++)
	{
		printf("%.17g ", v->components[i]);
	}
	printf(")");
	printf("\n");
}
/**
 * @brief the vector constructor
 *
 * @param x the x component
 * @param y the y component
 * @param z the z component
 */
// vector *new_vector(double x, double y, double z)
// {
// 	vector *v = malloc(sizeof(vector));
// 	v->x = x;
// 	v->y = y;
// 	v->z = z;
// 	return v;
// }

/**
 * @brief add two vectors
 *
 * @param v1 vector 1
 * @param v2 vector 2
 * @return vector* the sum of the two vectors
 */
vector *add_vector(vector *v1, vector *v2)
{
	vector *v = (vector *)malloc(sizeof(vector));
	v->x = v1->x + v2->x;
	v->y = v1->y + v2->y;
	v->z = v1->z + v2->z;
	return v;
}

/**
 * Subtracts two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The difference of the two vectors.
 */
vector *sub_vector(vector *v1, vector *v2)
{
	vector *v = (vector *)malloc(sizeof(vector));
	v->x = v1->x - v2->x;
	v->y = v1->y - v2->y;
	v->z = v1->z - v2->z;
	return v;
}

/**
 * @brief Multiplies a vector by a scalar
 *
 * @param v the vector
 * @param s the scalar
 * @return vector*
 */
vector *mult_vector(vector *v, double s)
{
	vector *r = (vector *)malloc(sizeof(vector));
	r->x = v->x * s;
	r->y = v->y * s;
	r->z = v->z * s;
	return r;
}

vector *div_vector(vector *v, double s)
{
	vector *r = (vector *)malloc(sizeof(vector));
	r->x = v->x / s;
	r->y = v->y / s;
	r->z = v->z / s;
	return r;
}

/**
 * @brief Calculates the dot product of two vectors
 *
 * @param v1 vector 1
 * @param v2 vector 2
 * @return the dot product
 */
double dot_product(Vector* v1, Vector* v2)
{
	double sum = 0;
	assert(v1->size == v2->size);
	for (size_t i = 0; i < v1->size; i++)
	{
		sum += (v1->components[i] * v2->components[i]);
	}
	if(sum == 0)
		printf("The provided vectors are perpendicular(orthogonal).\n");
	return sum;
} 


vector *cross_vector(vector *v1, vector *v2)
{
	vector *r = (vector *)malloc(sizeof(vector));
	r->x = v1->y * v2->z - v1->z * v2->y;
	r->y = v1->z * v2->x - v1->x * v2->z;
	r->z = v1->x * v2->y - v1->y * v2->x;
	return r;
}

double mag_vector(vector *v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

vector *norm_vector(vector *v)
{
	double m = mag_vector(v);
	return div_vector(v, m);
}

// vector *rotate_vector(vector *v1, vector *v2, double angle)
// {
// 	vector *v = (vector *)malloc(sizeof(vector));
// 	v->x = v1->x * cos(angle) - v1->z * sin(angle);
// 	v->y = v1->y;
// 	v->z = v1->x * sin(angle) + v1->z * cos(angle);
// 	return v;
// }