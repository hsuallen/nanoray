// Copyright 2015 Allen Hsu and Mitchell Kember.

#include <stdbool.h>
#include <stdio.h>

// Data structures

typedef struct TestResult TestResult;

struct TestResult {
	int n_tests;
	int fails;
};

// Comparison and checking

#define  V_EQ(s, u, v) CHECK(s, u, v, v_equal, v_print, true)
#define V_NEQ(s, u, v) CHECK(s, u, v, !v_equal, v_print, false)
#define  S_EQ(s, x, y) CHECK(s, x, y, s_equal, s_print, true)
#define S_NEQ(s, x, y) CHECK(s, x, y, !s_equal, s_print, false)

#define CHECK(label, x, y, pred, print, same) do { \
	if (!pred((x), (y))) { \
		if (first) { \
			printf("failed\n"); \
			first = false; \
		} \
		printf("[%d] \"" label "\": expected ", test_count); \
		if (!same) { \
			printf("anything but "); \
		} \
		print((y)); \
		printf(", got "); \
		print((x)); \
		putchar('\n'); \
		fails++; \
	} \
	test_count++; \
} while(0);

// Unit tests

#define TESTING(s) \
static int test_count = 0; \
static int fails = 0; \
static bool first = true; \
static const char *tests_name = #s; \
INCLUDE_TEST(s)

#define BEGIN_TESTS(s) do { printf("testing %s... ", tests_name); } while(0);

#define END_TESTS() do { \
	if (fails == 0) { \
		printf("ok\n"); \
	} \
	return (TestResult){test_count, fails}; \
} while (0);

// Aggregate tests

#define INCLUDE_TEST(s) TestResult test_all_##s(void)

#define RUN_TEST(s) do { \
	TestResult r = test_all_##s(); \
	n_tests += r.n_tests; \
	fails += r.fails; \
} while (0);
