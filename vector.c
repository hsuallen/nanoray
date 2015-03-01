// Copyright 2015 Allen Hsu.

#include "vector.h"

#include <math.h>
#include <stdio.h>

// Constants

static const Scalar epsilon = 10e-8;

const Vector v_zero = VEC(0, 0, 0);

// Vector operations

Vector v_add(Vector u, Vector v) {
	return (Vector){u.x + v.x, u.y + v.y, u.z + v.z};
}

Vector v_sub(Vector u, Vector v) {
	return (Vector){u.x - v.x, u.y - v.y, u.z - v.z};
}

Vector v_mul(Vector u, Scalar k) {
	return (Vector){u.x * k, u.y * k, u.z * k};
}

Vector v_neg(Vector u) {
	return v_mul(u, -1);
}

Scalar v_dot(Vector u, Vector v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector v_cross(Vector u, Vector v) {
	return (Vector){
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x
	};
}

Scalar v_norm(Vector v) {
	return sqrt(v_norm_sqr(v));
}

Scalar v_norm_sqr(Vector v) {
	return v_dot(v, v);
}

Vector v_unit(Vector v) {
	return v_mul(v, 1.0 / v_norm(v));
}

// Approximate equality predicates

bool s_equal(Scalar x, Scalar y) {
	return fabs(x - y) < epsilon;
}

bool v_equal(Vector u, Vector v) {
	return s_equal(u.x, v.x) && s_equal(u.y, v.y) && s_equal(u.z, v.z);
}

// Printing

void s_print(Scalar x) {
	printf("%.2lf", x);
}

void v_print(Vector v) {
	printf("[%.2lf %.2lf %.2lf]", v.x, v.y, v.z);
}
