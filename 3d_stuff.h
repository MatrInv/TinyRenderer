#pragma once
#include "math_n_co.h"

typedef struct triangles_3d
{
	vec3f V[3];
	//vec3f VT[3];
	//vec3f VN[3];
} triangle;

typedef struct cameras
{
	float k; //pixel dimension kxk
	int xres; //number of pixels along X axis
	int yres; //number of pixels along Y axis
	float focal; //distance between the screen and the camera
	mat4f pose; //pose of the camera
} camera;

typedef struct scene
{
	camera cam; //camera taking the scene
	triangle* poly; //set of triangles
	vec3f* lights; //set of directions of the fields of light
};

vec3f normal(vec3f v0, vec3f v1, vec3f v2); //normal vector of the plane defined by the three points v0, v1, v2
bool ray_triangle_intersection(vec3f v0, vec3f v1, vec3f v2, vec3f O, vec3f D, float* t, vec3f* I); //calculate the intersection point I between a triangle (v0,v1,v2) and a ray casted from the position O in direction D. t is the distance between O and I.