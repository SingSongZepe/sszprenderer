#include "triangle.h"


void Triangle::set_single_vertex(int idx, Vec4f v)
{
	vertices[idx] = v;
}

void Triangle::set_vertices(Vec4f v0, Vec4f v1, Vec4f v2)
{
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
}

void Triangle::set_single_normal(int idx, Vec3f n)
{
	normals[idx] = n;
}
void Triangle::set_normals(Vec3f n0, Vec3f n1, Vec3f n2)
{
	normals[0] = n0;
	normals[1] = n1;
	normals[2] = n2;
}

void Triangle::set_single_color(int idx, Vec3f c)
{
	colors[idx] = c;
}
void Triangle::set_colors(Vec3f c0, Vec3f c1, Vec3f c2)
{
	colors[0] = c0;
	colors[1] = c1;
	colors[2] = c2;
}

void Triangle::set_single_tex_coord(int idx, Vec2f t)
{
	tex_coords[idx] = t;
}
void Triangle::set_tex_coords(Vec2f tc0, Vec2f tc1, Vec2f tc2)
{
	tex_coords[0] = tc0;
	tex_coords[1] = tc1;
	tex_coords[2] = tc2;
}

