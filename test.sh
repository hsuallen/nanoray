#!/bin/bash

clang -Weverything -pedantic -std=c11 -Os test.c \
	intersect.c vector.c \
	intersect_test.c vector_test.c \
	-o test-nanoray && ./test-nanoray
