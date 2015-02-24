// Copyright 2015 Allen Hsu.

#include "test_common.h"

#include "intersect.h"
#include "vector.h"

TESTING(intersect);

// Constants

// Tests

static void test_extend(void) {
	S_EQ("1=1", 1, 1);
}

// Test all

TestResult test_all_intersect(void) {
	BEGIN_TESTS();
	test_extend();
	END_TESTS();
}
