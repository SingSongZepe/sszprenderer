#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "geometry.h"
#include "model.h"
#include "value.h"
#include "light.h"

// compute the coordinates of p
Vec3f barycentric_coord(Vec3f* points, Vec3f& P);

// after view transformation, then pass the 2D coordinates to this function,
// cause the rasterizer projection is not perspective.
void draw_triangle(Vec3f* points, Vec2f* tex_coords, Vec3f* normals, float* zbuffer, TGAImage* image, Texture* texture);

#endif //  __TRIANGLE_H__