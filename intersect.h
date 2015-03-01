// Copyright 2015 Allen Hsu.

#ifndef INTERSECT_H
#define INTERSECT_H

#include "vector.h"

#define RAY(p, d) ((Ray){(p), (d)})
#define SPHERE(c, r) ((Surface){.type = T_SPHERE, .sphere = {(c), (r)}})
#define PLANE(n, d) ((Surface){.type = T_PLANE, .plane = {(n), (d)}})


typedef struct Ray Ray;
typedef struct Surface Surface;

struct Ray {
	Vector pos;
	Vector dir;
};

struct Surface {
	enum { T_SPHERE, T_PLANE } type;
	char _pad[4];
	union {
		struct {
			Vector pos;
			Scalar radius;
		} sphere;
		struct {
			Vector norm;
			Scalar dist;
		} plane;
	};
};

Vector extend(Ray r, Scalar t);
Scalar intersect(Ray r, Surface s);

#endif
