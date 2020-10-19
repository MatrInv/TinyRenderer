#include "math_n_co.h"
//#include <math.h>
#include <iostream>

int sign(float f)
{
	if (f == 0)
		return 0;
	return f > 0 ? 1 : -1;
}

vec3f crossprod(vec3f v0, vec3f v1)
{
	vec3f v = { v0.y*v1.z - v0.z*v1.y , v0.z * v1.x - v0.x * v1.z , v0.x * v1.y - v0.y * v1.x };
	return v;
}

float scalarprod(vec3f v0, vec3f v1)
{
	float scl = v0.x*v1.x + v0.y*v1.y + v0.z*v1.z;
	return scl;
}

vec3f scaled(vec3f v0, float f)
{
	vec3f v = { v0.x * f , v0.y * f , v0.z * f };
	return v;
}

vec3f add(vec3f v0, vec3f v1)
{
	vec3f v = { v0.x + v1.x , v0.y + v1.y , v0.z + v1.z };
	return v;
}

vec3f substract(vec3f v0, vec3f v1) 
{
	vec3f v = { v0.x - v1.x , v0.y - v1.y , v0.z - v1.z };
	return v;
}

void normalize(vec3f* v0)
{
	float norm = (float)sqrt((double)v0->x * (double)v0->x + (double)v0->y * (double)v0->y + (double)v0->z * (double)v0->z);
	//float norm = sqrt(v0->x * v0->x + v0->y * v0->y + v0->z * v0->z);
	v0->x /= norm;
	v0->y /= norm;
	v0->z /= norm;
}

vec4f homogeneous(vec3f v)
{
	vec4f vhom = { v.x , v.y , v.z , 1 };
	return vhom;
}

vec3f reduct(vec4f v)
{
	return { v.x , v.y , v.z };
}

vec4f substract(vec4f v0, vec4f v1)
{
	return {v0.x-v1.x , v0.y-v1.y , v0.z-v1.z , v0.w-v1.w };
}

void fill(mat4f* M, float* array)
{
	for(int i=0;i<4*4;i++)
		M->comp[i]=array[i];
}

vec4f dot(mat4f M, vec4f v)
{
	vec4f vres;
	vres.x = M.comp[0] * v.x + M.comp[1] * v.y + M.comp[2] * v.z + M.comp[3] * v.w;
	vres.y = M.comp[4] * v.x + M.comp[5] * v.y + M.comp[6] * v.z + M.comp[7] * v.w;
	vres.z = M.comp[8] * v.x + M.comp[9] * v.y + M.comp[10] * v.z + M.comp[11] * v.w;
	vres.w = M.comp[12] * v.x + M.comp[13] * v.y + M.comp[14] * v.z + M.comp[15] * v.w;
	return vres;
}

vec4f dot(vec4f v, mat4f M)
{
	vec4f vres;
	vres.x = M.comp[0] * v.x + M.comp[4] * v.y + M.comp[8] * v.z + M.comp[12] * v.w;
	vres.y = M.comp[1] * v.x + M.comp[5] * v.y + M.comp[9] * v.z + M.comp[13] * v.w;
	vres.z = M.comp[2] * v.x + M.comp[6] * v.y + M.comp[10] * v.z + M.comp[14] * v.w;
	vres.w = M.comp[3] * v.x + M.comp[7] * v.y + M.comp[11] * v.z + M.comp[15] * v.w;
	return vres;
}

mat4f dot(mat4f M0, mat4f M1)
{
	mat4f M;
	for (int j = 0;j < 4;j++)
		for (int i = 0;i < 4;i++)
			M.comp[j * 4 + i] = M0.comp[j * 4] * M1.comp[i] + 
								M0.comp[j * 4 + 1] * M1.comp[i + 4] + 
								M0.comp[j * 4 + 2] * M1.comp[i + 8] + 
								M0.comp[j * 4 + 3] * M1.comp[i + 12];
	return M;
}

void transpose(mat4f* M)
{
	float tmp;
	for (int j = 1;j < 4;j++)
		for (int i = 0;i < j;i++)
		{
			tmp = M->comp[j * 4 + i];
			M->comp[j * 4 + i] = M->comp[i * 4 + j];
			M->comp[i * 4 + j] = tmp;
		}
}

mat4f Rz(double theta) 
{
	mat4f M;
	float R[4*4] = 
	{ 
		(float) cos(theta) , (float)-sin(theta) , 0.f , 0.f ,
		(float) sin(theta) , (float)cos(theta) , 0.f , 0.f ,
		0.f , 0.f , 1.f , 0.f ,
		0.f , 0.f , 0.f , 1.f
	};
	fill(&M, R);
	return M;
}

mat4f Ry(double theta)
{
	mat4f M;
	float R[4*4] = 
	{
		(float)cos(theta) , 0.f , (float)sin(theta) , 0.f ,
		0.f , 1.f , 0.f , 0.f ,
		(float)-sin(theta) , 0.f , (float)cos(theta) , 0.f ,
		0.f , 0.f , 0.f , 1.f
	};
	fill(&M, R);
	return M;
}

mat4f Rx(double theta)
{
	mat4f M;
	float R[4*4] = 	
	{
		1.f , 0.f , 0.f , 0.f ,
		0.f , (float)cos(theta), (float)-sin(theta) , 0.f ,
		0.f , (float)sin(theta) , (float)cos(theta) , 0.f ,
		0.f , 0.f , 0.f , 1.f
	};
	fill(&M, R);
	return M;
}

mat4f T(vec3f v)
{
	mat4f M;
	float R[4*4] = 
	{
		1.f , 0.f , 0.f , v.x ,
		0.f , 1.f , 0.f , v.y ,
		0.f , 0.f , 1.f , v.z ,
		0.f , 0.f , 0.f , 1.f ,
	};
	fill(&M, R);
	return M;
}

void print_mat(mat4f M) {
	std::cout
		<< M.comp[0] << "  " << M.comp[1] << "  " << M.comp[2] << "  " << M.comp[3] << std::endl
		<< M.comp[4] << "  " << M.comp[5] << "  " << M.comp[6] << "  " << M.comp[7] << std::endl
		<< M.comp[8] << "  " << M.comp[9] << "  " << M.comp[10] << "  " << M.comp[11] << std::endl
		<< M.comp[12] << "  " << M.comp[13] << "  " << M.comp[14] << "  " << M.comp[15] << std::endl << std::endl;
}

void print_vec(vec3f v)
{
	std::cout << v.x << "  " << v.y << "  " << v.z  << std::endl << std::endl;
}

void print_vec(vec4f v)
{
	std::cout << v.x << "  " << v.y << "  " << v.z << "  " << v.w << std::endl << std::endl;
}