
#include "geometry.h"
#include "model.h"
//#include "tgaimage.h"
#include "view.h"
#include "value.h"
#include "triangle.h"

#include <stdio.h>
#include <iostream>
#include <vector>


// define the view
//View view{};

Vec3f eye_position = Vec3f{ 1., 1., 1. };
Vec3f gaze_dir = Vec3f{ -1., -1., -1. };
Vec3f up_dir = Vec3f{ -1., 2., -1. };
View view{ eye_position, gaze_dir, up_dir };

// defind the light source
// parallel light source, denote by simply a vector
Vec3f light_source{ 0., 0., -1. };

// we only transform the x, y to screen, but not z
Vec3f world2screen(const Vec3f& v) 
{
	return Vec3f(int((v.x + 1.0) * WIDTH / 2. + .5), int((v.y + 1.0) * HEIGHT / 2. + .5), v.z);
}

int main(int argc, char** argv)
{
	Model* model = nullptr;

	if (argc != 2)
	{
		model = new Model("obj/bunny.obj");
	}
	else
	{
		model = new Model(argv[1]);
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

		Vec3f v0 = view.transform(model->vert(face[0]).to_homogeneous_point()).to_normal_pos_vec();
		Vec3f v1 = view.transform(model->vert(face[1]).to_homogeneous_point()).to_normal_pos_vec();
		Vec3f v2 = view.transform(model->vert(face[2]).to_homogeneous_point()).to_normal_pos_vec();
		
		points[0] = world2screen(v0);
		points[1] = world2screen(v1);
		points[2] = world2screen(v2);

		// select one out of three
		// fill triangle with color white 
		//draw_triangle(points, image, WHITE);
		
		// fill triangle with random color
		//draw_triangle(points, zbuffer, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));

		// the light source will do affect on the triangle fragment
		// be careful, it is cross product of v2v0 and v1v0, not v1v0 cross v2v0.
		Vec3f unit_norm = (v2 - v0).cross_product(v1 - v0).normalized();
		float indensity = unit_norm.dot_product(light_source);
		draw_triangle(points, zbuffer, image, TGAColor(indensity * 255, indensity * 255, indensity * 255, 255));
		
		delete[] points;
	}

	image->flip_vertically();
	image->write_tga_file("output.tga");

	delete model;
	delete[] zbuffer;
	delete image;
	return 0;
}