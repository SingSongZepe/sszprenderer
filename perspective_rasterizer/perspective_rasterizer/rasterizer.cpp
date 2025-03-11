
#include "rasterizer.h"
#include "value.h"

#include <array>
#include <algorithm>

void Rasterizer::set_model(const Mat4f& m)
{
	model = m;
}
void Rasterizer::set_view(const Mat4f& v)
{
	view = v;
}
void Rasterizer::set_projection(const Mat4f& p)
{
	projection = p;
}

void Rasterizer::set_texture(Texture* t)
{
	texture = *t;
}

//void set_vertex_shader(std::function<Vec3f(VertexShaderPayload)> f);
void Rasterizer::set_fragment_shader(std::function<Vec3f(FragmentShaderPayload)> f)
{
	fragment_shader = f;
}

int Rasterizer::get_index(int x, int y)
{
	return (height - y) * width + x;
}

void Rasterizer::set_pixel(const Vec2i& point, const Vec3f& color)
{
	Vec2i p = point;
	fragment_buf[get_index(p[0], p[1])] = color;
}

void Rasterizer::save_image()
{
	image->write_tga_file("output.tga");
}

void Rasterizer::clear_buf()
{
    for (int i = 0; i < width * height; i++)
    {
        depth_buf[i] = -std::numeric_limits<float>::infinity();
    }
}

void Rasterizer::draw(std::vector<Triangle*>& tri_list)
{
	// some coefficients for linear transformation for viewport transformation of z-axis
	float f1 = 1.;
	float f2 = 0.;

	Mat4f mvp = projection * view * model;

	for (const Triangle* tri : tri_list)
	{
		Triangle tri_to_draw = Triangle();

		//std::array<Vec3f, 3> viewspace_pos{
		//	(view * model * tri->vertices[0]).to_normal_pos_vec(),
		//	(view * model * tri->vertices[1]).to_normal_pos_vec(),
		//	(view * model * tri->vertices[2]).to_normal_pos_vec(),
		//};

		std::array<Vec4f, 3> v{
			mvp * tri->vertices[0],
			mvp * tri->vertices[1],
			mvp * tri->vertices[2],
		};

		for (auto& vert : v)
		{
			vert.x /= vert.w;
			vert.y /= vert.w;
			vert.z /= vert.w;
			vert.w = 1.;
		}

		//vert.x() = 0.5 * width * (vert.x() + 1.0);
		// viewport transformation
		for (auto& vert : v)
		{
			vert.x = (vert.x + 1.) * width * 0.5 - 0.5;
			vert.y = (vert.y + 1.) * height * 0.5 - 0.5;
			vert.z = f1 * vert.z + f2;
		}

		tri_to_draw.set_vertices(v[0], v[1], v[2]);
		tri_to_draw.set_normals(tri->normals[0], tri->normals[1], tri->normals[2]);
		tri_to_draw.set_tex_coords(tri->tex_coords[0], tri->tex_coords[1], tri->tex_coords[2]);
		tri_to_draw.set_colors(tri->colors[0], tri->colors[1], tri->colors[2]);
		
		draw_triangle(tri_to_draw);
	}
}

// barycentric coords
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


void Rasterizer::draw_triangle(const Triangle& tri)
{
	Vec3f* screen_points = new Vec3f;
	screen_points[0] = Vec3f{ tri.vertices[0].x, tri.vertices[0].y, tri.vertices[0].z };
	screen_points[1] = Vec3f{ tri.vertices[1].x, tri.vertices[1].y, tri.vertices[1].z };
	screen_points[2] = Vec3f{ tri.vertices[2].x, tri.vertices[2].y, tri.vertices[2].z };

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
            if (depth_buf[idx] < p.z) {
                depth_buf[idx] = p.z;

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

                image->set(p.x, p.y, TGAColor::from_Vec3(fragment_shader(payload)));
            }
        }
    }

    delete[] screen_points;
}