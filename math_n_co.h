#pragma once
#include <cmath>

typedef struct vectors2f {
	float x, y;
} vec2f;


//VECTOR 3
typedef struct vectors3f
{
	float x, y, z;
} vec3f;

int sign(float f);

vec3f crossprod(vec3f v0, vec3f v1); //crossproduct between v0 and v1

float scalarprod(vec3f v0, vec3f v1); //product between v0 and v1

vec3f scaled(vec3f v0, float f); //scaled version of v0 with f

vec3f add(vec3f v0, vec3f v1);

vec3f substract(vec3f v0, vec3f v1);

void normalize(vec3f* v0);

//TRANSFORMATIONS
typedef struct vectors4f
{
	float x, y, z, w;
} vec4f;

vec4f homogeneous(vec3f v); //turn the non-homogeneous vector v into an homogeneous vector

vec3f reduct(vec4f v); //turn the homogeneous vector v into a non-homogeneous vector

vec4f substract(vec4f v0, vec4f v1);

typedef struct matrix4f
{
	//by default, it's the identity matrix
	float comp[4 * 4] = { 
						1.f , 0.f , 0.f , 0.f ,
						0.f , 1.f , 0.f , 0.f ,
						0.f , 0.f , 1.f , 0.f ,
						0.f , 0.f , 0.f , 1.f 
						};
}mat4f;

void fill(mat4f* M, float* array);

vec4f dot(mat4f M, vec4f v);

vec4f dot(vec4f v, mat4f M);

mat4f dot(mat4f M0, mat4f M1);

void transpose(mat4f* M);

mat4f Rz(double theta); //matrix of rotation around Z axis

mat4f Ry(double theta);

mat4f Rx(double theta);

mat4f T(vec3f v); //translation matrix

void print_mat(mat4f M);

void print_vec(vec3f v);

void print_vec(vec4f v);