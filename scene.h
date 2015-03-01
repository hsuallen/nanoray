// Copyright 2015 Allen Hsu.

#ifndef SCENE_H
#define SCENE_H

#include "colour.h"
#include "intersect.h"

typedef struct Scene Scene;
typedef struct Settings Settings;
typedef struct Object Object;
typedef struct Material Material;
typedef struct Light Light;
typedef struct Camera Camera;

struct Settings {
	Colour sky;
	int x_res;
	int y_res;
	int samples;
	char _pad[4];
};

struct Object {
	Surface surf;
	unsigned int mat_id;
	char _pad[4];
};

struct Material {
	Colour diffuse;
	Scalar refl;
};

struct Light {
	enum { T_POINT, T_INF, T_SPOT } type;
	char _pad[4];
	Colour colour;
	union {
		struct {
			Vector pos;
		} point;
		struct {
			Vector dir;
		} inf;
		struct {
			Vector pos;
			Vector dir;
			Scalar size;
			Scalar blend;
		} spot;
	};
};

struct Camera {
	enum { T_ORTHO, T_PERSPECTIVE } type;
	char _pad[4];
	Vector pos;
	Vector look;
	Vector up;
	union {
		Scalar scale;
		Scalar f_length;
	};
};

struct Scene {
	Settings settings;
	Object *objs;
	Material *mats;
	Light *lights;
	Camera cam;
	int n_objs, n_mats, n_lights;
	char _pad[4];
};

Colour trace(Ray, Scene);

#endif
