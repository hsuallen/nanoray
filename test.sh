#!/bin/bash

clang -Weverything -pedantic -std=c11 -Os test.c \
	intersect.c scene.c vector.c \
	intersect_test.c scene_test.c vector_test.c \
	-o test-nanoray && ./test-nanoray
