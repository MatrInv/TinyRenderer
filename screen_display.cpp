#include "screen_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


void write_ppm( image* img, const char* abs_path ) 
{
    FILE* imageFile = fopen(abs_path, "wb");
    
    if (imageFile != nullptr) //no opening error
        std::cout << "No opening error" << std::endl;
    else {
        perror("ERROR: Cannot open output file. Exiting.");
        exit(EXIT_FAILURE);
    }

    fprintf(imageFile, "P6\n");               // P6 filetype
    fprintf(imageFile, "%d %d\n", img->xres, img->yres);        // dimensions
    fprintf(imageFile, "255\n");              // Max pixel

    fwrite(img->pix, 1, img->xres * img->yres *3, imageFile);

    fclose(imageFile);
}


void set_pixel(image* img, unsigned int x, unsigned int y, uint8_t* color) 
{
    if (x >= img->xres || y >= img->yres)
        perror("ERROR : Trying to draw a point out of range. Ignoring.");
    else {

        unsigned int pos1d;

        pos1d = (img->xres * y + x) * 3;

        img->pix[pos1d] = color[0];
        img->pix[pos1d+1] = color[1];
        img->pix[pos1d+2] = color[2];
    }

}

void bresenham( image* img, vec2f p0, vec2f p1 ) 
{
    uint8_t color[3] = { 255, 255, 255 }; //WHITE

    float x0 = p0.x; float y0 = p0.y;
    float x1 = p1.x; float y1 = p1.y;

    double dx = fabs(x1 - x0);
    float sx = x0 < x1 ? 1 : -1;
    double dy = -fabs(y1 - y0);
    float sy = y0 < y1 ? 1 : -1;
    double err = dx + dy;  // error value e_xy 

    while (true) {   // loop
        set_pixel(img, (int)x0, (int)y0, color);
        if (x0 == x1 && y0 == y1) //points are at the exact same position
            break;
        double e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy; // e_xy+e_x > 0 
            x0 += sx;
        }
        if (e2 <= dx) // e_xy+e_y < 0 
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_triangle(image* img, vec2f p0, vec2f p1, vec2f p2)
{
    bresenham(img, p0, p1);
    bresenham(img, p1, p2);
    bresenham(img, p2, p0);
}

/*
void swap(vec2f** l, unsigned int i0, unsigned int i1) 
{
    vec2f* mem = l[i0];
    l[i0] = l[i1];
    l[i1] = mem;
}

void sort_by_y(vec2f** l)
{
    if (l[2]->y < l[1]->y) {
        swap(l, 2, 1);
    }
    if (l[1]->y < l[0]->y) {
        swap(l, 1, 0);
    }
}
*/

bool edge_function(vec2f a, vec2f b, vec2f P)
{
    return ((P.x - a.x) * (b.y - a.y) - (P.y - a.y) * (b.x - a.x) >= 0);
}

bool inside_triangle(vec2f v0, vec2f v1, vec2f v2, vec2f P)
{
    bool inside = true;
    inside &= edge_function(v0, v1, P);
    inside &= edge_function(v1, v2, P);
    inside &= edge_function(v2, v0, P);

    return inside;
}

void bounding_box(vec2f bbox[2], vec2f v0, vec2f v1, vec2f v2)
{
    vec2f bmin = v0;
    vec2f bmax = v0;
    vec2f v[2] = { v1, v2 };

    for (int i = 0;i < 2;i++)
    {

        if (v[i].x < bmin.x)
            bmin.x = v[i].x;
        else if (v[i].x > bmax.x)
            bmax.x = v[i].x;

        if (v[i].y < bmin.y)
            bmin.y = v[i].y;
        else if (v[i].y > bmax.y)
            bmax.y = v[i].y;
    }

    bbox[0] = bmin;
    bbox[1] = bmax;
}

void rasterize(image* img, vec2f v0, vec2f v1, vec2f v2)
{
    uint8_t color[3] = { 255, 255, 255 }; //WHITE
    vec2f bbox[2];
    bounding_box(bbox, v0, v1, v2);
    vec2f p;
    for (int y = (int)bbox[0].y; y < bbox[1].y ; y++) {
        for (int x = (int)bbox[0].x; x < bbox[1].x; x++) {
            p = { (float)x,(float)y };
            if (inside_triangle(v0, v1, v2, p))
                set_pixel(img, x, y, color);
        }
    }
}

/*
int main()
{
    const int xres = 100; //width
    const int yres = 75; //height
    uint8_t pix[xres * yres * 3] = { 0 }; //initialize the array with 0

    image img = { xres, yres, pix }; //instantiate an image structure with previous primitives

    vec2f v0 = { 40, 20 };
    vec2f v1 = { 80, 10 };
    vec2f v2 = { 50, 50 };
    vec2f* A[3] = { &v2, &v1, &v0 };

    //TEST 7 : rasterization
    rasterize(&img, *A[0], *A[1], *A[2]);

    //TEST 6 : bounding box
    /*
    vec2f bbox[2] = {v0, v2};
    bounding_box(bbox, *A[0], *A[1], *A[2]);
    vec2f p0 = { bbox[0].x, bbox[0].y };
    vec2f p1 = { bbox[0].x, bbox[1].y };
    vec2f p2 = { bbox[1].x, bbox[1].y };
    vec2f p3 = { bbox[1].x, bbox[0].y };
    bresenham(&img, p0, p1);
    bresenham(&img, p1, p2);
    bresenham(&img, p2, p3);
    bresenham(&img, p3, p0);
    draw_triangle(&img, *A[0], *A[1], *A[2]);
    */

    //TEST 5 : stupid list things whiches are useless
    /*
    sort_by_y(A);
    std::cout << "(" << A[0]->x << "," << A[0]->y << ") ; (" << A[1]->x << "," << A[1]->y << ") ; (" << A[2]->x << "," << A[2]->y << ")" << std::endl;
    */

    //TEST 4 : draw triangle
    /*
    draw_triangle(&img, *A[0], *A[1], *A[2]);
    */
    

    //TEST 3 : draw lines using bresenham's method
    /*
    bresenham(&img, *A[0], *A[1]);
    */

    //TEST 2 : change a pixel's color DONE
    /*
    uint8_t color[3] = { 255,255,255 };
    set_pixel(&img, 50, 50, color);
    */

    //TEST 1 : save an array as ppm file DONE
/*	write_ppm(&img);

    return 0;
}*/