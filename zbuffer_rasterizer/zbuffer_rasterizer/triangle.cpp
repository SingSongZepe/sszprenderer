#include "triangle.h"

// Compute the barycentric coordinates of point p with respect to triangle defined by points
Vec3f barycentric_coord(Vec3f* points, Vec3f& p)
{
    // (u, v, 1) = cross_product([p0p1x, p0p2x, pp0x], [p0p1y, p0p2y, pp0y])
    Vec3f u = Vec3f(points[2].x - points[0].x, points[1].x - points[0].x, points[0].x - p.x)
        .cross_product(Vec3f(points[2].y - points[0].y, points[1].y - points[0].y, points[0].y - p.y));

    // when triangle degenerate to a line
    if (std::abs(u.z) < 1e-2)
    {
        return Vec3f(-1., 1., 1.);
    }
    return Vec3f(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

// Draw a triangle on the image using the z-buffer algorithm
void draw_triangle(Vec3f* points, float* zbuffer, TGAImage* image, TGAColor color) {
    Vec2f bl_boundary = Vec2f(0, 0);
    Vec2f tr_boundary = Vec2f(WIDTH - 1, HEIGHT - 1);
    
    // Compute the bounding box of the triangle
    bl_boundary.x = std::max(bl_boundary.x, std::min(points[0].x, std::min(points[1].x, points[2].x)));
    bl_boundary.y = std::max(bl_boundary.y, std::min(points[0].y, std::min(points[1].y, points[2].y)));
    
    tr_boundary.x = std::min(tr_boundary.x, std::max(points[0].x, std::max(points[1].x, points[2].x)));
    tr_boundary.y = std::min(tr_boundary.y, std::max(points[0].y, std::max(points[1].y, points[2].y)));

    Vec3f p;
    for (p.x = bl_boundary.x; p.x <= tr_boundary.x; p.x++) {
        for (p.y = bl_boundary.y; p.y <= tr_boundary.y; p.y++) {
            Vec3f barycentroid = barycentric_coord(points, p);

            if (barycentroid.x < 0 || barycentroid.y < 0 || barycentroid.z < 0) {
                // Not in the triangle
                continue;
            }

            // Get the current point interpolated z
            p.z = 0;
            for (int i = 0; i < 3; i++) {
                p.z += barycentroid.raw[i] * points[i].z;
            }

            int idx = int(p.x + p.y * WIDTH);
            if (zbuffer[idx] < p.z) {
                zbuffer[idx] = p.z;
                image->set(p.x, p.y, color);
            }
        }
    }
}
