// Copyright 2015 Allen Hsu.

#ifndef INTERSECT_H
#define INTERSECT_H

#include "vector.h"

// #define MK_SPHERE(x, y, z, r) ((Surface){ SPHERE, VEC(x, y, z), r})

struct Ray {
	Vector position;
	Vector direction;
};

struct Surface {
	enum { SPHERE, PLANE } type;
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

#endif
