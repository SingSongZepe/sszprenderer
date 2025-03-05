
#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "view.h"
#include "value.h"
#include "triangle.h"

#include <stdio.h>
#include <iostream>
#include <vector>

Model* model = nullptr;

// define the view
//View view{};

Vec3f eye_position = Vec3f{ 1., 1., 1. };
Vec3f gaze_dir = Vec3f{ -1., -1., -1. };
Vec3f up_dir = Vec3f{ -1., 2., -1. };
View view{ eye_position, gaze_dir, up_dir };

// defind the light source
// parallel light source, denote by simply a vector
Vec3f light_source{ 0., 0., -1. };

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		model = new Model("obj/african_head.obj");
	}
	else
	{
		model = new Model(argv[1]);
	}                                                                                                                                                                         
	
	TGAImage* image = new TGAImage(WIDTH, HEIGHT, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec3f v0 = view.transform(model->vert(face[0]).to_homogeneous_point()).to_normal_pos_vec();
		Vec3f v1 = view.transform(model->vert(face[1]).to_homogeneous_point()).to_normal_pos_vec();
		Vec3f v2 = view.transform(model->vert(face[2]).to_homogeneous_point()).to_normal_pos_vec();

		int x0 = (v0.x + 1.0) * WIDTH / 2.;
		int y0 = (v0.y + 1.0) * HEIGHT / 2.;
		int x1 = (v1.x + 1.0) * WIDTH / 2.;
		int y1 = (v1.y + 1.0) * HEIGHT / 2.;
		int x2 = (v2.x + 1.0) * WIDTH / 2.;
		int y2 = (v2.y + 1.0) * HEIGHT / 2.;
		
		Vec2i* points = new Vec2i[3];
		points[0] = Vec2i(x0, y0);
		points[1] = Vec2i(x1, y1);
		points[2] = Vec2i(x2, y2);
		
		// select one out of three
		// fill triangle with color white 
		//draw_triangle(points, image, WHITE);
		
		// fill triangle with random color
		//draw_triangle(points, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));

		// the light source will do affect on the triangle fragment
		Vec3f a = v1 - v0;
		Vec3f b = v2 - v0;
		Vec3f unit_norm = a.cross_product(b).normalized();
		float indensity = unit_norm.dot_product(light_source);
		draw_triangle(points, image, TGAColor(indensity * 255, indensity * 255, indensity * 255, 255));
		
		delete[] points;
	}

	image->flip_vertically();
	image->write_tga_file("output.tga");

	delete model;
	delete image;
	return 0;
}