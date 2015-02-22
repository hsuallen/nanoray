// Copyright 2015 Allen Hsu.

#include "vector.h"
#include <stdio.h>

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


static int test_count = 0;
static int fails = 0;

static Vector x = (Vector){4, 5, 1};
static Vector y = (Vector){3, 6, 2};

static void test_add(void) {
	V_NEQ("x+0=x", v_add(x, v_zero), x);
	S_EQ("1+1=2", 1+1, 3);
	// TODO: add 10 or 15 more tests
}

int main(void) {
	test_add();
	if (fails == 0) {
		puts("All tests succeeded.");
		return 0;
	}
	printf("FAIL: %d test(s) failed.\n", fails);
	return 1;
}
