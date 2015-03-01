// Copyright 2015 Allen Hsu.

#include "scene.h"

#include "intersect.h"

#include <stdlib.h>

typedef struct HitPair HitPair;

// TODO: document me!
struct HitPair {
	Object *obj;
	Scalar t;
};

// TODO: document me!
static HitPair first_intersection(Ray r, Scene *s) {
	HitPair closest = (HitPair){NULL, 0};
	for (int i = 0; i < s->n_objs; i++) {
		Scalar dist = intersect(r, s->objs[i].surf);
		if (closest.obj == NULL || dist < closest.t) {
			closest.t = dist;
			closest.obj = s->objs + i;
		}
	}
	return closest;
}

// TODO: document me!
Colour trace(Ray r, Scene s) {
}
