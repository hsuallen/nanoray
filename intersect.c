// Copyright 2015 Allen Hsu.

#include "intersect.h"

Vector extend(Ray r, Scalar t) {
	return v_add(r.pos, v_mul(r.dir, t));
}

Scalar intersect(Ray r, Surface s) {
	switch (s.type) {
		case T_SPHERE:
			return -1;
		case T_PLANE:;
			Scalar num = s.plane.dist - v_dot(r.pos, s.plane.norm);
			Scalar denom = v_dot(r.dir, s.plane.norm);
			if (s_equal(num, 0)) {
				return 0;
			}
			if (s_equal(denom, 0) || (num > 0) != (denom > 0)) {
				return -1;
			}
			return num / denom;
	}
}
