// Copyright 2015 Allen Hsu.

#include "intersect.h"

Vector extend(Ray r, Scalar t) {
	return v_add(r.pos, v_mul(r.dir, t));
}
