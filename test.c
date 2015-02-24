// Copyright 2015 Allen Hsu.

#include "test_common.h"

INCLUDE_TEST(intersect);
INCLUDE_TEST(vector);

int main(void) {
	int n_tests = 0;
	int fails = 0;
	RUN_TEST(intersect);
	RUN_TEST(vector);
	if (fails == 0) {
		printf("All tests (%d) succeeded.\n", n_tests);
		return 0;
	}
	double percent = 100.0 * (1.0 - 1.0*fails / n_tests);
	printf("FAIL: %d test(s) failed (%.2lf%% passed).\n", fails, percent);
	return 1;
}
