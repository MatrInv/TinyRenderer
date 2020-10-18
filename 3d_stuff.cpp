#include "3d_stuff.h"

//distances are in mm

vec3f normal(vec3f v0, vec3f v1, vec3f v2)
{
	vec3f A = substract(v1, v0);
	vec3f B = substract(v2, v0); //these are the two vector describing the plane 
	vec3f C = crossprod(A, B);
	normalize(&C);
	return C;
}

//O and D are respectively the origin and the direction of the ray
//I and t store respectively the coordinates of the intersection and the distance between O and I
bool ray_triangle_intersection(vec3f v0, vec3f v1, vec3f v2, vec3f O, vec3f D, float* t, vec3f* I)
{

	//Step 1 : Intersection calculation

	vec3f N = normal(v0, v1, v2);
	
	if (scalarprod(D, N) == 0)
		return false;

	*t = scalarprod( substract(v0,O) , N ) / scalarprod( D , N ) ; //distance O-I
	
	*I = add( scaled(D, *t) , O ); //coordinates of intersection

	//Step 2 : inside or outside of the triangle ?

	vec3f C; // vector perpendicular to triangle's plane 

	// edge 0
	vec3f e0 = substract(v1 , v0);
	vec3f vp0 = substract(*I , v0);
	C = crossprod(e0, vp0);
	if (scalarprod(C,N) < 0)
		return false;

	// edge 1
	vec3f e1 = substract(v2, v1);
	vec3f vp1 = substract(*I, v1);
	C = crossprod(e1, vp1);
	if (scalarprod(C, N) < 0)
		return false;

	// edge2
	vec3f e2 = substract(v0, v2);
	vec3f vp2 = substract(*I, v2);
	C = crossprod(e2, vp2);
	if (scalarprod(C, N) < 0)
		return false;

	return true;
}

//vec3f barycenter(vec3f trgl);