// Copyright 2015 Allen Hsu.

#ifndef INTERSECT_H
#define INTERSECT_H

#include "vector.h"

#define RAY(p, d) ((Ray){p, d})
#define SPHERE(c, r) ((Surface){T_SPHERE, c, r})
#define PLANE(n, d) ((Plane){T_PLANE, n, d})

typedef struct Ray Ray;

struct Ray {
	Vector pos;
	Vector dir;
};

struct Surface {
	enum { T_SPHERE, T_PLANE } type;
	union {
		struct {
			Vector center;
			Scalar radius;
		} sphere;
		struct {
			Vector normal;
			Scalar dist;
		} plane;
	};
};

Vector extend(Ray r, Scalar t);

#endif
