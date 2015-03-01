// Copyright 2015 Allen Hsu.

#include "intersect.h"

#include <math.h>

static Scalar square(Scalar s) {
	return s * s;
}

static Scalar sgn(Scalar s) {
	return (s >= 0) ? 1 : -1;
}

Vector extend(Ray r, Scalar t) {
	return v_add(r.pos, v_mul(r.dir, t));
}

Scalar intersect(Ray r, Surface s) {
	switch (s.type) {
		case T_SPHERE:;
			Vector rp = v_sub(r.pos, s.sphere.pos);
			Scalar b = 2 * v_dot(r.dir, rp);
			Scalar c = v_norm_sqr(rp) - square(s.sphere.radius);
			Scalar disc = square(b)/4 - c;
			if (disc < 0) {
				return -1;
			}
			Scalar x0 = -b / 2.0 - sgn(b) * sqrt(disc);
			Scalar x1 = c / x0;

			// Ensure that x0 < x1.
			if (x0 > x1) {
				Scalar temp = x1;
				x1 = x0;
				x0 = temp;
			}

			if (x1 < 0) {
				return -1;
			}
			if (x0 < 0) {
				return x1;
			}
			return x0;
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
