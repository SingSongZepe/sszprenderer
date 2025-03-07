#include "triangle.h"
#include "shader.h"
#include "fragment_payload.h"
#include "value.h"

// we only transform the x, y to screen, but not z
Vec3f world2screen(const Vec3f& v)
{
    return Vec3f(int((v.x + 1.0) * WIDTH / 2. + .5), int((v.y + 1.0) * HEIGHT / 2. + .5), v.z);
}

// Compute the barycentric coordinates of point p with respect to triangle defined by points
// be careful about the order of points responding to its order in the (u, v, 1)
Vec3f barycentric_coord(Vec3f* points, Vec3f& p)
{
    // (u, v, 1) = cross_product([p0p1x, p0p2x, pp0x], [p0p1y, p0p2y, pp0y])
    Vec3f u = Vec3f(points[1].x - points[0].x, points[2].x - points[0].x, points[0].x - p.x)
        .cross_product(Vec3f(points[1].y - points[0].y, points[2].y - points[0].y, points[0].y - p.y));

    // when triangle degenerate to a line
    if (std::abs(u.z) < 1e-2)
    {
        return Vec3f(-1., 1., 1.);
    }
    return Vec3f(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
}

// Draw a triangle on the image using the z-buffer algorithm
void draw_triangle(Vec3f* points, Vec2f* tex_coords, Vec3f* normals, float* zbuffer, TGAImage* image, Texture* texture) 
{
    Vec3f* screen_points = new Vec3f[3];
    for (int i = 0; i < 3; i++)
    {
        screen_points[i] = world2screen(view.transform(points[i].to_homogeneous_point()).to_normal_pos_vec());
    }

    Vec2f bl_boundary = Vec2f(0, 0);
    Vec2f tr_boundary = Vec2f(WIDTH - 1, HEIGHT - 1);

    // Compute the bounding box of the triangle
    bl_boundary.x = std::max(bl_boundary.x, std::min(screen_points[0].x, std::min(screen_points[1].x, screen_points[2].x)));
    bl_boundary.y = std::max(bl_boundary.y, std::min(screen_points[0].y, std::min(screen_points[1].y, screen_points[2].y)));

    tr_boundary.x = std::min(tr_boundary.x, std::max(screen_points[0].x, std::max(screen_points[1].x, screen_points[2].x)));
    tr_boundary.y = std::min(tr_boundary.y, std::max(screen_points[0].y, std::max(screen_points[1].y, screen_points[2].y)));

    Vec3f p;
    for (p.x = bl_boundary.x; p.x <= tr_boundary.x; p.x++) {
        for (p.y = bl_boundary.y; p.y <= tr_boundary.y; p.y++) {
            Vec3f barycentroid = barycentric_coord(screen_points, p);

            if (barycentroid.x < 0 || barycentroid.y < 0 || barycentroid.z < 0) {
                // Not in the triangle
                continue;
            }

            // Get the current point interpolated z
            p.z = 0;
            for (int i = 0; i < 3; i++) {
                p.z += barycentroid[i] * screen_points[i].z;
            }

            int idx = int(p.x + p.y * WIDTH);
            if (zbuffer[idx] < p.z) {
                zbuffer[idx] = p.z;

                // get interpolated (u, v)
                Vec2f tex_coord{};
                for (int i = 0; i < 3; i++)
                {
                    tex_coord += tex_coords[i] * barycentroid[i];
                }

                // get interpolated normal
                Vec3f normal{};
                for (int i = 0; i < 3; i++)
                {
                    normal += normals[i] * barycentroid[i];
                }

                Vec3f space_coord{};
                for (int i = 0; i < 3; i++)
                {
                    space_coord += points[i] * barycentroid[i];
                }

                // construct the fragment shader payload
                FragmentShaderPayload payload{ TGAColor{0, 0, 0, 0}, normal, tex_coord, texture };
                payload.space_coord = space_coord;

                image->set(p.x, p.y, texture_fragment_shader(payload));
            }
        }
    }
    
    delete[] screen_points;
}
