#include "screen_display.h"
#include "3d_stuff.h"

#include <iostream>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#include <cstring>
#include <cfloat>


//use differents geometric criteria to eliminate triangles from trgls and put the remaining in selected for the rendering
bool triangle_selection( triangle* trgl )
{
	//Back-face culling
	
	//In the field of view

	return false;
}

void render(image* img, camera* cam, triangle* triangles[], const int size )
{
	//for every triangle, project edges on the screen to obtain the bounding box
	//cast a ray from the center of the camera to the center of each pixel
	
	float k=0; memcpy(&k, &cam->k, sizeof(float));//pixel metric
	int xres; memcpy(&xres, &cam->xres, sizeof(int));
	int yres; memcpy(&yres, &cam->yres, sizeof(int));

	vec4f O_cam = { 0,0,0,1 };
	vec4f C = dot(cam->pose,O_cam); //center of the camera
	
	vec4f P; //3D point that will define the screen

	vec3f D, I, N, rand_ray, rand_point;
	float intensity, t;
	triangle* trgl;

	uint8_t base_color[3] = { 255,255,255 };
	uint8_t color[3];

	//z-buffer initialisation
	float* zbuffer = (float*) malloc((xres * yres * sizeof(float)));
	for (int l = 0;l < xres * yres;l++)
		zbuffer[l] = FLT_MAX;

	for (int n = 0;n < size;n++) {
		//rendering condition 1 : back face culling = only triangles where N.vec(C,v0) < 0
		trgl = triangles[n];
		N = normal(trgl->V[0], trgl->V[1], trgl->V[2]);
		rand_point = trgl->V[0];
		rand_ray = substract(rand_point, reduct(C)); //one random ray from the camera touching the triangle
		normalize(&rand_ray);
		if (scalarprod(N,rand_ray)<0) //back-face culling
			//rendering condition 2 : only triangles in the field of view = if vec(C,v0) or vec(C,v1) or vec(C,v2) intersect the screen
			//TODO

			//for each pixel (i,j) of the screen
			for (int j = 0; j < yres; j++)
				for (int i = 0; i < xres; i++) {
					
					//P is the position of the pixel in the 3D camera's coordinate system
					P.x = cam->focal; //by convention, camera's direction is along X axis
					P.y = k * (j + 1/2 - yres/2); //the screen is centered on the origin 
					P.z = k * (i + 1/2 - xres/2);
					P.w = 1;

					//P becomes now the position of the pixel but in the world's coordinate system
					P = dot(cam->pose, P);
					
					D = reduct(substract(P, C)); //3D segment between the pixel and the center of the camera
					normalize(&D); //direction of this segment

					//Check if the ray casted from the camera to P collide the triangle trgl
					if (ray_triangle_intersection(trgl->V[0], trgl->V[1], trgl->V[2], reduct(C), D, &t, &I))
					{
						//TODO : only in the bounding box calculated

						//z-buffering
						if (zbuffer[j * xres + i]>=t) 
						{
							zbuffer[j * xres + i] = t;
							//intensity calculation
							intensity = std::abs(scalarprod(D, N));
							color[0] = (uint8_t)((float)base_color[0] * intensity);
							color[1] = (uint8_t)((float)base_color[1] * intensity);
							color[2] = (uint8_t)((float)base_color[2] * intensity);
							set_pixel(img, i, j, color);
						} //else, don't write anything
					}

				}
	}
}

int main() {

	const char* save_abs_path = "triangles_in_perspective.ppm"; //absolute path where the ppm file will be saved
	const int xres = 600, yres = 400; //resolution of the screen

	mat4f pose = T({ 0,0,-200 }); //let us translate the camera 200units back
	transpose(&pose);
	pose = dot(Ry(-M_PI/2),pose); //the camera will face the plane (X,Y)

	camera cam = {0.1,xres,yres,200,pose}; //the camera is 200 units far from the screen (it's the focal), so the screen should be coplanar with the plane (X,Y)

	uint8_t pix[xres * yres * 3] = { 0 };
	image img = {xres,yres,pix};

	vec3f v0 = { 0,0,60 };
	vec3f v1 = { 10,-5,70 };
	vec3f v2 = { 0,-5,70 };
	triangle t0 = { v0,v1,v2 };
	
	vec3f v5 = { 0,-5,90 };
	vec3f v4 = { 4,-3,50 };
	vec3f v3 = { -2,-2,90 };
	triangle t1 = { v3,v4,v5 };

	vec3f v6 = { -8,-6,100 };
	vec3f v7 = { 2,-5,100 };
	vec3f v8 = { 6,-10,100 };
	triangle t2 = { v6,v7,v8 };

	const int sz = 3;
	triangle* T[sz] = { &t0 , &t1 , &t2 };

	print_cam_infos(cam);

	render(&img, &cam , T, sz);

	write_ppm(&img, save_abs_path);
}