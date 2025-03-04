
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "view.h"

#include <iostream>
#include <stdio.h>
#include <filesystem>

const TGAColor WHITE_ = TGAColor(255, 255, 255, 255);
const TGAColor RED_   = TGAColor(255, 0, 0, 255);
Model* model = nullptr;
const int width = 800;
const int height = 800;

// define the camera

// three viewpoint to test

//View view{};

//Vec3f camera_position{ 1., 1., 1. };
//Vec3f glaze{-1., -1., -1.};
//Vec3f up{-1., 2., -1.};
//View view{ camera_position, glaze, up };

Vec3f camera_position{ 0., 0., 0. };
Vec3f glaze{ -3., -4., -5. };
Vec3f up{ 2., -4., 2. };
View view{ camera_position, glaze, up };

// draw a line from p0 to p1

void line(const Vec2i& p0, const Vec2i& p1, TGAImage& image, TGAColor color) {

	int x0 = p0.x;
	int y0 = p0.y;
	int x1 = p1.x;
	int y1 = p1.y;

	bool steep_slope = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		steep_slope = true;
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	for (int x = x0; x <= x1; x++) 
	{
		int y = static_cast<int>((y1 - y0) / (float)(x1 - x0) * (x - x0) + y0);
		
		if (steep_slope)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
	}
}

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		model = new Model(argv[1]);
	}
	else
	{
		model = new Model("obj/african_head.obj");
	}
	
	TGAImage* image = new TGAImage(width, height, TGAImage::RGB);
	for (int i = 0; i < model->nfaces(); i++)
	{
		printf("face index: %d\n", i);
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) 
		{
			Vec4f v0 = view.transform(model->vert(face[j]).to_homogeneous_point());
			Vec4f v1 = view.transform(model->vert(face[(j + 1) % 3]).to_homogeneous_point());


			// we throw z coordinate as viewer looks from z to -z
			int x0 = static_cast<int>((v0.x + 1.0) * width  / 2.);
			int y0 = static_cast<int>((v0.y + 1.0) * height / 2.);
			int x1 = static_cast<int>((v1.x + 1.0) * width  / 2.);
			int y1 = static_cast<int>((v1.y + 1.0) * height / 2.);

			Vec2i p0 = Vec2i(x0, y0);
			Vec2i p1 = Vec2i(x1, y1);

			line(p0, p1, *image, WHITE_);
		}
	}

	image->flip_vertically();
	image->write_tga_file("output.tga");

	printf("Hello World!");

	delete model;
	return 0;
}