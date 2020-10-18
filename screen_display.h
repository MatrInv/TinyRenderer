#pragma once
#include "math_n_co.h"
#include <cstdint>

typedef struct images
{
	const unsigned int xres, yres;
	uint8_t* pix;
} image;

void write_ppm(image* img, const char* abs_path); //write ppm image fill with img in abs_path
void set_pixel(image* img, unsigned int x, unsigned int y, uint8_t* color); //set the pixel's color at postion (x,y) 
void bresenham(image* img, vec2f p0, vec2f p1); //Bresenham's algorithm for writing an edge (p0,p1) in discrete 2D space (img)
void draw_triangle(image* img, vec2f p0, vec2f p1, vec2f p2); //write the triangle (p0,p1,p2) in img
bool edge_function(vec2f a, vec2f b, vec2f P); //determine which side of the segment (a,b) the point P is
bool inside_triangle(vec2f v0, vec2f v1, vec2f v2, vec2f P); //determine if a point P is inside or outside of the triangle (p1,p2,p3)
void bounding_box(vec2f bbox[2], vec2f v0, vec2f v1, vec2f v2); //determine the bounding box of the triangle (v1,v2,v3) and store it in bbox
void rasterize(image* img, vec2f v0, vec2f v1, vec2f v2); //write the rasterization of the triangle (v0,v1,v2) in img