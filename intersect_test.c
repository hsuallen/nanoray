// Copyright 2015 Allen Hsu.

#include "test_common.h"

#include "intersect.h"
#include "vector.h"

#include <math.h>

TESTING(intersect);

// Constants

static const Vector ux = VEC(1, 0, 0);
static const Vector uy = VEC(0, 1, 0);
static const Vector uz = VEC(0, 0, 1);
static const Vector uxy = VEC(M_SQRT1_2, M_SQRT1_2, 0);
static const Vector uxz = VEC(M_SQRT1_2, 0, M_SQRT1_2);
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
	V_NEQ("0,j -> 1 != 0,i -> 1",
		extend(RAY(v_zero, uy), 1),
		extend(RAY(v_zero, ux), 1));
}

static void test_intersect_plane(void) {
	S_EQ("0,i ∩ k->0 = 0", intersect(RAY(v_zero, ux), PLANE(uz, 0)), 0);
	S_EQ("i,(-i) ∩ k->0 = 0", intersect(RAY(ux, v_neg(ux)), PLANE(uz, 0)), 0);
	S_EQ("0,k ∩ k->0 = 0", intersect(RAY(v_zero, uz), PLANE(uz, 0)), 0);
	S_EQ("j,(-k) ∩ k->0 = 0", intersect(RAY(uy, v_neg(uz)), PLANE(uz, 0)), 0);
	S_EQ("0,k ∩ k->5 = 5", intersect(RAY(v_zero, uz), PLANE(uz, 5)), 5);
	S_EQ("k,i ∩ k->0 = -1", intersect(RAY(uz, ux), PLANE(uz, 0)), -1);
	S_EQ("k,i ∩ -k->0 = -1", intersect(RAY(uz, ux), PLANE(v_neg(uz), 0)), -1);
	S_EQ("k,-k ∩ k->0 = 1", intersect(RAY(uz, v_neg(uz)), PLANE(uz, 0)), 1);
	S_EQ("k,-k ∩ -k->0 = 1",
		intersect(RAY(uz, v_neg(uz)), PLANE(v_neg(uz), 0)), 1);
	S_EQ("k,k ∩ k->0 = -1", intersect(RAY(uz, uz), PLANE(uz, 0)), -1);
	S_EQ("k,k ∩ -k->0 = -1", intersect(RAY(uz, uz), PLANE(v_neg(uz), 0)), -1);
	S_EQ("-3k,4i ∩ k->0 = -1",
			intersect(RAY(v_mul(uz, -3), v_mul(ux, 4)), PLANE(uz, 0)), -1);
	S_EQ("0,[1/√2 0 1/√2] ∩ [1/√2 0 1/√2]->10 = 10",
		intersect(RAY(v_zero, uxz), PLANE(uxz, 10)), 10); 
}

static void test_intersect_sphere(void) {
	S_EQ("0,i ∩ 0R3 = 3", intersect(RAY(v_zero, ux), SPHERE(v_zero, 3)), 3);
	S_EQ("k,k ∩ 0R1 = 0", intersect(RAY(uz, uz), SPHERE(v_zero, 1)), 0);
	S_EQ("k,-k ∩ 0R1 = 0", intersect(RAY(uz, v_neg(uz)), SPHERE(v_zero, 1)), 0);
	S_EQ("3i,-i ∩ 0R1 = 2",
		intersect(RAY(v_mul(ux, 3), v_neg(ux)), SPHERE(v_zero, 1)), 2);
	S_EQ("[5 0 -5],k ∩ 0R5 = 5",
		intersect(RAY(VEC(5, 0, -5), uz), SPHERE(v_zero, 5)), 5);
}

// Test all

TestResult test_all_intersect(void) {
	BEGIN_TESTS();
	test_extend();
	test_intersect_plane();
	test_intersect_sphere();
	END_TESTS();
}
