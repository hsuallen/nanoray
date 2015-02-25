// Copyright 2015 Allen Hsu.

#include "test_common.h"

#include "intersect.h"
#include "vector.h"

#include <math.h>

TESTING(intersect);

// Constants

static const Vector ux = VEC(1, 0, 0);
static const Vector uy = VEC(0, 1, 0);
static const Vector uxy = VEC(M_SQRT1_2, M_SQRT1_2, 0);
static const Vector w = VEC(2, 4, 3);

// Tests

static void test_extend(void) {
	V_EQ("0,i -> 0 = 0", extend(RAY(v_zero, ux), 0), v_zero);
	V_EQ("0,i -> 1 = i", extend(RAY(v_zero, ux), 1), ux);
	V_EQ("i,i -> 0 = i", extend(RAY(ux, ux), 0), ux);
	V_EQ("w,i -> 7 = [9 4 3]", extend(RAY(w, ux), 7), VEC(9, 4, 3));
	V_EQ("i,j -> 4 = [1 4 0]", extend(RAY(ux, uy), 4), VEC(1, 4, 0));
	V_EQ("w,unit(i+j) -> 0", extend(RAY(w, uxy), 0), w);
	V_EQ("w,unit(i+j) -> √2", extend(RAY(w, uxy), M_SQRT2), VEC(3, 5, 3));
	V_EQ("w,i -> -5 = [-3 4 3]", extend(RAY(w, ux), -5), VEC(-3, 4, 3));
	V_EQ("i,j -> 1 != j,i -> 1",
		extend(RAY(ux, uy), 1),
		extend(RAY(uy, ux), 1));
}

// Test all

TestResult test_all_intersect(void) {
	BEGIN_TESTS();
	test_extend();
	END_TESTS();
}
