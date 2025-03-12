
#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "shader.h"
#include "view.h"
#include "value.h"
#include "triangle.h"
#include "texture.h"
#include "rasterizer.h"
#include "matrix_maker.h"

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>

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

	std::vector<Triangle*> tri_list;

	// rearrange data into triangles
	for (int i = 0; i < model->nfaces(); i++)
	{
		//std::cout << i << std::endl;
		std::vector<int> face = model->face(i);
		Triangle* tri = new Triangle();

		int j = 0;
		tri->set_vertices(model->vert(face[j++]).to_homogeneous_point(),
			model->vert(face[j++]).to_homogeneous_point(),
			model->vert(face[j++]).to_homogeneous_point());
		
		tri->set_tex_coords(model->tex_coord(face[j++]),
			model->tex_coord(face[j++]),
			model->tex_coord(face[j++]));

		tri->set_normals(model->normal(face[j++]),
			model->normal(face[j++]),
			model->normal(face[j++]));

		tri_list.push_back(tri);
	}

	TGAImage* image = new TGAImage(WIDTH, HEIGHT, TGAImage::RGB);
	Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT, image);

	// model matrix
	float ROTATE_ANGLE = 0.;
	rasterizer->set_model(make_model_matrix(ROTATE_ANGLE));

	// view matrix
	rasterizer->set_view(make_view_matrix(view));

	// projection matrix
	float fov = 45;
	float aspect_ratio = WIDTH / HEIGHT;
	float n = 0.1;
	float f = 100;
	rasterizer->set_projection(make_projection_matrix(fov, aspect_ratio, n, f));

	rasterizer->set_texture(texture);

	rasterizer->set_fragment_shader(&texture_fragment_shader);

	//void Rasterizer::draw(std::vector<Triangle*>&tri_list)
	rasterizer->draw(tri_list);

	// write the img into a file
	rasterizer->save_image();

	delete model;
	delete rasterizer;
	return 0;
}