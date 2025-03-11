#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "geometry.h"
#include "texture.h"

class Triangle
{
public:
	// homogeneous coord
	Vec4f vertices[3];
	Vec3f colors[3];
	Vec2f tex_coords[3];
	Vec3f normals[3];

	Texture* texture = nullptr;

public:
	Triangle() {};

	void set_single_vertex(int idx, Vec4f v);
	void set_vertices(Vec4f v0, Vec4f v1, Vec4f v2);

	void set_single_normal(int idx, Vec3f n);
	void set_normals(Vec3f n0, Vec3f n1, Vec3f n2);

	void set_single_color(int idx, Vec3f c);
	void set_colors(Vec3f c0, Vec3f c1, Vec3f c2);

	void set_single_tex_coord(int idx, Vec2f t);
	void set_tex_coords(Vec2f tc0, Vec2f tc1, Vec2f tc2);

};

#endif // __TRIANGLE_H__