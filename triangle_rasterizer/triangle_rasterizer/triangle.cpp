
#include "triangle.h"

// compute the coordinates of p
Vec3f barycentric_coord(Vec2i* points, Vec2i p)
{
	// (u, v, 1) = cross_product([p0p1x, p0p2x, pp0x], [p0p1y, p0p2y, pp0y])
	Vec3f u = Vec3f(points[1].x - points[0].x, points[2].x - points[0].x, points[0].x - p.x)
		.cross_product(Vec3f(points[1].y - points[0].y, points[2].y - points[0].y, points[0].y - p.y));

	// when triangle degenerate to a line
	if (std::abs(u.z) < 1)
	{
		return Vec3f(-1., 1., 1.);
	}
	return Vec3f(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

// after view transformation, then pass the 2D coordinates to this function,
// cause the rasterizer projection is not perspective.
void draw_triangle(Vec2i* points, TGAImage* image, TGAColor color)
{
	Vec2i bl_boundary = Vec2i(0, 0);
	Vec2i tr_boundary = Vec2i(WIDTH - 1, HEIGHT - 1);
	// compute the bounding box of triangle;
	bl_boundary.x = std::max(bl_boundary.x, std::min(points[0].x, std::min(points[1].x, points[2].x)));
	bl_boundary.y = std::max(bl_boundary.y, std::min(points[0].y, std::min(points[1].y, points[2].y)));

	tr_boundary.x = std::min(tr_boundary.x, std::max(points[0].x, std::max(points[1].x, points[2].x)));
	tr_boundary.y = std::min(tr_boundary.y, std::max(points[0].y, std::max(points[1].y, points[2].y)));

	for (int x = bl_boundary.x; x <= tr_boundary.x; x++)
	{
		for (int y = bl_boundary.y; y <= tr_boundary.y; y++)
		{
			Vec3f barycentroid = barycentric_coord(points, Vec2i(x, y));
			if (barycentroid.x < 0 || barycentroid.y < 0 || barycentroid.z < 0)
			{   // not in the triangle
				continue;
			}
			image->set(x, y, color);
		}
	}
}
