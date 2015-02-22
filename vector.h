// Copyright 2015 Allen Hsu.

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef double Scalar;
typedef struct Vector Vector;

struct Vector {
	Scalar x, y, z;
};

extern Vector v_zero;

Vector v_add(Vector, Vector);
Vector v_sub(Vector, Vector);
Vector v_mul(Vector, Scalar);
Vector v_neg(Vector);
Scalar v_dot(Vector, Vector);
Vector v_cross(Vector, Vector);
Scalar v_norm(Vector);
Scalar v_norm_sqr(Vector);
Vector v_unit(Vector);

bool s_equal(Scalar, Scalar);
bool v_equal(Vector, Vector);

#endif
