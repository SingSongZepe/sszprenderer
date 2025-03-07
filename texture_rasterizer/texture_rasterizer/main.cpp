
#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "view.h"
#include "value.h"
#include "triangle.h"
#include "texture.h"

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

	TGAImage* image = new TGAImage(WIDTH, HEIGHT, TGAImage::RGB);
	float* zbuffer = new float[WIDTH * HEIGHT];
	// the code is a little tricky
	for (int i = WIDTH * HEIGHT - 1; i--; zbuffer[i] = -std::numeric_limits<float>::max());
	
	for (int i = 0; i < model->nfaces(); i++)
	{
		printf("%d\n", i);

		std::vector<int> face = model->face(i);

		Vec3f* points = new Vec3f[3];
		for (int i = 0; i < 3; i++)
		{
			points[i] = model->vert(face[i]);
		}

		Vec2f* tex_coords = new Vec2f[3];
		for (int i = 0; i < 3; i++)
		{
			tex_coords[i] = model->tex_coord(face[i + 3]);
		}

		Vec3f* normals = new Vec3f[3];
		for (int i = 0; i < 3; i++)
		{
			normals[i] = model->normal(face[i+6]);
		}

		// the light source will do affect on the triangle fragment
		// be careful, it is cross product of v2v0 and v1v0, not v1v0 cross v2v0.
		//Vec3f unit_norm = (v2 - v0).cross_product(v1 - v0).normalized();
		//float indensity = unit_norm.dot_product(light_source);
		draw_triangle(points, tex_coords, normals, zbuffer, image, texture);
		
		delete[] points;
		delete[] tex_coords;
		delete[] normals;
	}

	image->flip_vertically();
	image->write_tga_file("output.tga");

	delete model;
	delete[] zbuffer;
	delete image;
	delete texture;
	return 0;
}