
#include "geometry.h"
#include "triangle.h"
#include "value.h"
#include "matrix_maker.h"

#include <gtest/gtest.h>
#include <iostream>

//TEST(modelReadTest, test1)
//{
//	char filename[] = "obj/african_head/african_head.obj";
//	Model* model = new Model(filename);
//
//	for (int i = 0; i < 1; i++)
//	{
//		std::vector<int> face = model->face(i);
//		for (int j = 0; j < face.size(); j++)
//		{
//			std::cout << face[j] << " ";
//		}
//	}
//}
//
//TEST(textureMappingTest, test1)
//{
//	char filename[] = "obj/african_head/african_head.obj";
//	Model* model = new Model(filename);
//
//	int idx = 1;
//	std::vector<int> face = model->face(idx);
//	
//	for (int j = 0; j < face.size(); j++)
//	{
//		std::cout << face[j] << " ";
//		
//		// world coordinates
//		if (j < 3)
//		{
//			Vec3f v = model->vert(face[j]);
//			std::cout << v;
//		}
//		else
//		{
//			Vec2f v = model->tex_coord(face[j]);
//			std::cout << v;
//		}
//	}
//}

TEST(matrixTest, test1)
{
	Mat4f view_ = make_view_matrix(view);
	std::cout << view_ << std::endl;

	Mat4f model = make_model_matrix(0.);
	std::cout << model << std::endl;

	float fov = 90;
	float aspect_ratio = WIDTH / HEIGHT;
	float n = 0.1;
	float f = 100;
	Mat4f projection = make_projection_matrix(fov, aspect_ratio, n, f);
	std::cout << projection << std::endl;

	std::cout << projection * view_ * model << std::endl;
}

TEST(textureMappingTest, test2)
{
	Model* model = new Model("obj/african_head/african_head.obj");

	std::vector<Triangle*> tri_list;

	// rearrange data into triangles
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Triangle* tri = new Triangle();
		tri->set_vertices(model->vert(face[0]).to_homogeneous_point(),
			model->vert(face[1]).to_homogeneous_point(),
			model->vert(face[2]).to_homogeneous_point());

		tri->set_normals(model->normal(face[0]),
			model->normal(face[1]),
			model->normal(face[2]));

		tri->set_tex_coords(model->tex_coord(face[0]),
			model->tex_coord(face[1]),
			model->tex_coord(face[2]));

		tri_list.push_back(tri);
	}
	
	std::cout << tri_list[0]->tex_coords;
}

int main1()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}