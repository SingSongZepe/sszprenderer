#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "value.h"

// compute the coordinates of p
Vec3f barycentric_coord(Vec3f* points, Vec3f& P);

// after view transformation, then pass the 2D coordinates to this function,
// cause the rasterizer projection is not perspective.
void draw_triangle(Vec3f* points, float* zbuffer, TGAImage* image, TGAColor color);

#endif //  __TRIANGLE_H__