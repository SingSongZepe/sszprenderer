
#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "shader.h"
#include "view.h"
#include "value.h"
#include "triangle.h"
#include "texture.h"
#include "rasterizer.h"

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>

const double PI = 3.14159265358979323846;

// the angle is in degrees, and rotates counterclockwise around y-axis
Mat4f make_model_matrix(const float& angle) noexcept
{
	Mat4f rotate = Mat4f::zeros<float, 4>();
	float angle_rad = angle * PI / 180.;
	rotate[0][0] = cos(angle_rad);
	rotate[0][2] = sin(angle_rad);
	rotate[1][1] = 1.;
	rotate[2][0] = -sin(angle_rad);
	rotate[2][2] = cos(angle_rad);
	rotate[3][3] = 1.;

	Mat4f scale = Mat4f::zeros<float, 4>();
	rotate[0][0] = 2.5;
	rotate[1][1] = 2.5;
	rotate[2][2] = 2.5;
	rotate[3][3] = 1.;

	Mat4f translate = Mat4f::identity<float, 4>();

	return translate * rotate * scale;
}

Mat4f make_view_matrix(const View& view) noexcept
{
	return view.view_mat;
}

// where the n is the near clipping space, f is the far clipping space
// aspect_ratio = w / h;
Mat4f make_projection_matrix(float fov, float aspect_ratio, float n, float f)
{
	float fov_rad = fov * PI / 180;

	float h = 2 * tan(fov_rad / 2) * n;
	float w = h * aspect_ratio;

	Mat4f orthorgraphic = Mat4f::zeros<float, 4>();
	orthorgraphic[0][0] = 1 / w;
	orthorgraphic[1][1] = 1 / h;
	orthorgraphic[2][2] = 1 / (f - n);
	orthorgraphic[2][3] = -(f + n) / 2. / (f - n);
	orthorgraphic[3][3] = 1;

	Mat4f perspec2ortho = Mat4f::zeros<float, 4>();
	perspec2ortho[0][0] = n;
	perspec2ortho[1][1] = n;
	perspec2ortho[2][2] = f + n;
	perspec2ortho[2][3] = -n * f;
	perspec2ortho[3][2] = 1;

	return orthorgraphic * perspec2ortho;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		model = new Model("obj/african_head/african_head.obj");
		texture = new Texture("obj/african_head/african_head_diffuse.tga");
	}
	else
	{
		model = new Model(argv[1]);
		texture = new Texture("obj/african_head/african_head_diffuse.tga");
	}                                                                                                                                                            

	std::vector<Triangle> tri_list;

	// rearrange data into triangles
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Triangle tri;
		tri.set_vertices(model->vert(face[0]).to_homogeneous_point(),
			model->vert(face[1]).to_homogeneous_point(),
			model->vert(face[2]).to_homogeneous_point());

		tri.set_normals(model->normal(face[0]),
			model->normal(face[1]),
			model->normal(face[2]));

		tri.set_tex_coords(model->tex_coord(face[0]),
			model->tex_coord(face[1]),
			model->tex_coord(face[2]));

		tri_list.push_back(tri);
	}

	Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT);

	// model matrix
	float ROTATE_ANGLE = 145;
	rasterizer->set_model(make_model_matrix(ROTATE_ANGLE));

	// view matrix
	rasterizer->set_view(make_view_matrix(view));

	// projection matrix
	float fov = 90;
	float aspect_ratio = WIDTH / HEIGHT;
	float n = 0.1;
	float f = 100;
	rasterizer->set_projection(make_projection_matrix(fov, aspect_ratio, n, f));

	rasterizer->set_texture(texture);

	rasterizer->set_fragment_shader();


	delete model;
	delete rasterizer;
	return 0;
}