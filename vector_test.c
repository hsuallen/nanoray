// Copyright 2015 Allen Hsu.

#include "vector.h"

#include <math.h>
#include <stdio.h>

// Macros

#define  V_EQ(s, u, v) CHECK(s,u,v,v_equal,==)
#define V_NEQ(s, u, v) CHECK(s,u,v,!v_equal,!=)
#define  S_EQ(s, x, y) CHECK(s,x,y,s_equal,==)
#define S_NEQ(s, x, y) CHECK(s,x,y,!s_equal,!=)

#define CHECK(s,x,y,pred,symbol) do { \
	if (!pred((x), (y))) { \
		printf("[%d] \"" s "\": " #x " " #symbol " " #y "\n", test_count); \
		fails++; \
	} \
	test_count++; \
} while(0);

// Globals

static int test_count = 0;
static int fails = 0;

// Constants

static const Vector x = VEC(4, 5, 1);
static const Vector y = VEC(3, 6, 2);
static const Vector z = VEC(1, 2, 3);
static const Vector w = VEC(0, 9, 0);

// Tests

static void test_add(void) {
	V_EQ("0+0 = 0", v_add(v_zero, v_zero), v_zero);
	V_EQ("x+0 = x", v_add(x, v_zero), x);
	V_EQ("0+x = x", v_add(v_zero, x), x);
	V_EQ("x+x = x*2", v_add(x, x), v_mul(x, 2));
	V_EQ("z+w", v_add(z, w), VEC(1, 11, 3));
	V_EQ("x+(y+(z+w))", v_add(x, v_add(y, v_add(z, w))), VEC(8, 22, 6));
	V_EQ("((x+y)+z)+w", v_add(v_add(v_add(x, y), z), w), VEC(8, 22, 6));
	V_EQ("y+w = w+y", v_add(y, w), v_add(w, y));
	V_NEQ("x+y != z", v_add(x, y), z);
	V_NEQ("z+z != z", v_add(z, z), z);
}

static void test_sub(void) {
	V_EQ("0-0 = 0", v_sub(v_zero, v_zero), v_zero);
	V_EQ("x-x = 0", v_sub(x, x), v_zero);
	V_EQ("x-(x*(-1)) = x*2", v_sub(x, v_neg(x)), v_mul(x, 2));
	V_EQ("x-y", v_sub(x, y), VEC(1, -1, -1));
	V_EQ("0-w = -w", v_sub(v_zero, w), v_neg(w));
	V_EQ("x-(y-(z-w))", v_sub(x, v_sub(y, v_sub(z, w))), VEC(2, -8, 2));
	V_EQ("((x-y)-z)-w", v_sub(v_sub(v_sub(x, y), z), w), VEC(0, -12, -4));
	V_NEQ("x-y != z", v_sub(x, y), z);
	V_NEQ("x-y != y-x", v_sub(x, y), v_sub(y, x));
	V_NEQ("x-(y-(z-w)) != ((x-y)-z)-w",
		v_sub(x, v_sub(y, v_sub(z, w))),
		v_sub(v_sub(v_sub(x, y), z), w));
}

static void test_mul(void) {
	V_EQ("x*0 = 0", v_mul(x, 0), v_zero);
	V_EQ("x*1 = x", v_mul(x, 1), x);
	V_EQ("x*2 = x+x", v_mul(x, 2), v_add(x, x));
	V_EQ("x*3 = x+(x+x)", v_mul(x, 3), v_add(x, v_add(x, x)));
	V_EQ("(x*2)*0.5 = x", v_mul(v_mul(x, 2), 0.5), x);
	V_EQ("(x*0.5)*2 = x", v_mul(v_mul(x, 0.5), 2), x);
	V_EQ("(x*3)*3 = x*9", v_mul(v_mul(x, 3), 3), v_mul(x, 9));
	V_EQ("x*(-5) = (x*5)*(-1)", v_mul(x, -5), v_mul(v_mul(x, 5), -1));
	V_NEQ("x*2 != x", v_mul(x, 2), x);
}

static void test_neg(void) {
	V_EQ("-x = x*(-1)", v_neg(x), v_mul(x, -1));
	V_EQ("-(-x) = x", v_neg(v_neg(x)), x);
	V_EQ("-(-(-x)) = -x", v_neg(v_neg(v_neg(x))), v_neg(x));
	V_NEQ("-x != x", v_neg(x), x);
}

static void test_dot(void) {
	V_EQ("x*(y•z)", v_mul(x, v_dot(y, z)), VEC(84, 105, 21));
	S_EQ("0•0 = 0", v_dot(v_zero, v_zero), 0);
	S_EQ("x•0 = 0", v_dot(x, v_zero), 0);
	S_EQ("0•x = 0", v_dot(v_zero, x), 0);
	S_EQ("x•y = 44", v_dot(x, y), 44);
	S_EQ("y•x = 44", v_dot(y, x), 44);
	S_EQ("x•(-y) = -(x•y)", v_dot(x, v_neg(y)), -v_dot(x, y));
	S_EQ("(-x)•y = -(x•y)", v_dot(v_neg(x), y), -v_dot(x, y));
	S_EQ("x•(y+z) = (x•y)+(x•z)",
		v_dot(x, v_add(y, z)),
		v_dot(x, y) + v_dot(x, z));
	S_EQ("w•[1 0 -1] = 0", v_dot(w, VEC(1, 0, -1)), 0);
	S_NEQ("x•x != 0", v_dot(x, x), 0);
}

static void test_cross(void) {
	V_EQ("0×0 = 0", v_cross(v_zero, v_zero), v_zero);
	V_EQ("x×0 = 0", v_cross(x, v_zero), v_zero);
	V_EQ("0×x = 0", v_cross(v_zero, x), v_zero);
	V_EQ("x×x = 0", v_cross(x, x), v_zero);
	V_EQ("i×j = k", v_cross(VEC(1, 0, 0), VEC(0, 1, 0)), VEC(0, 0, 1));
	V_EQ("(i+j)×(i-j) = k*(-2)",
		v_cross(VEC(1, 1, 0), VEC(1, -1, 0)), v_mul(VEC(0, 0, 1), -2));
	V_EQ("x×y = -(y×x)", v_cross(x, y), v_neg(v_cross(y, x)));
	S_EQ("|y×z| = |y|*|z|*sin(a)",
		v_norm(v_cross(y, z)),
		v_norm(y)*v_norm(z)*sin(acos(v_dot(y, z)/(v_norm(y)*v_norm(z)))));
	S_NEQ("|x×w| != x•w", v_norm(v_cross(x, w)), v_dot(x, w));
}

static void test_norm(void) {
	S_EQ("|0| = 0", v_norm(v_zero), 0);
	S_EQ("|w| = 9", v_norm(w), 9);
	S_EQ("|z| = sqrt(14)", v_norm(z), sqrt(14));
	S_EQ("|-y|=|y|", v_norm(v_neg(y)), v_norm(y));
	S_EQ("|x-x| = 0", v_norm(v_sub(x, x)), 0);
	S_NEQ("|x+y| != |x|+|y|", v_norm(v_add(x, y)), v_norm(x)+v_norm(y));
}

static void test_norm_sqr(void) {
	S_EQ("|0|² = 0", v_norm_sqr(v_zero), 0);
	S_EQ("|-y|²=|y|²", v_norm_sqr(v_neg(y)), v_norm_sqr(y));
	S_EQ("|x+x|² = |x|²*4", v_norm_sqr(v_add(x, x)), 4*v_norm_sqr(x));
	S_EQ("|x*10|² = |x|²*100", v_norm_sqr(v_mul(x, 10)), 100*v_norm_sqr(x));
	S_EQ("|x|² = x•x", v_norm_sqr(x), v_dot(x, x));
	S_EQ("|w|² = 81", v_norm_sqr(w), 81);
	S_NEQ("|x+x|² != |x|²+|x|²",
		v_norm_sqr(v_add(x, x)),
		v_norm_sqr(x)+v_norm_sqr(x));
}

static void test_unit(void) {
	V_EQ("unit(z*42) = unit(z)", v_unit(v_mul(z, 42)), v_unit(z));
	V_NEQ("unit(0) != 0", v_unit(v_zero), v_zero);
	S_EQ("|unit(x)| = 1", v_norm(v_unit(x)), 1);
	S_EQ("|unit(x)|² = 1", v_norm_sqr(v_unit(x)), 1);
	S_EQ("unit(w).y = 1", v_unit(w).y, 1);
}

// Main

int main(void) {
	test_add();
	test_sub();
	test_mul();
	test_neg();
	test_dot();
	test_cross();
	test_norm();
	test_norm_sqr();
	test_unit();
	if (fails == 0) {
		printf("All tests (%d) succeeded.\n", test_count);
		return 0;
	}
	printf("FAIL: %d test(s) failed.\n", fails);
	return 1;
}
