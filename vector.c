// Copyright 2015 Allen Hsu.

#include "vector.h"
#include <stdio.h>
#include <math.h>

static Scalar epsilon = 10e-8;

Vector v_zero = (Vector){0, 0, 0};

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

bool s_equal(Scalar x, Scalar y) {
	return fabs(x - y) < epsilon;
}

bool v_equal(Vector u, Vector v) {
	return s_equal(u.x, v.x) && s_equal(u.y, v.y) && s_equal(u.z, v.z);
}
