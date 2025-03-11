
#include "geometry.h"
#include "triangle.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(modelReadTest, test1)
{
	char filename[] = "obj/african_head/african_head.obj";
	Model* model = new Model(filename);

	for (int i = 0; i < 1; i++)
	{
		std::vector<int> face = model->face(i);
		for (int j = 0; j < face.size(); j++)
		{
			std::cout << face[j] << " ";
		}
	}
}

TEST(textureMappingTest, test1)
{
	char filename[] = "obj/african_head/african_head.obj";
	Model* model = new Model(filename);

	int idx = 1;
	std::vector<int> face = model->face(idx);
	
	for (int j = 0; j < face.size(); j++)
	{
		std::cout << face[j] << " ";
		
		// world coordinates
		if (j < 3)
		{
			Vec3f v = model->vert(face[j]);
			std::cout << v;
		}
		else
		{
			Vec2f v = model->tex_coord(face[j]);
			std::cout << v;
		}
	}
}



int main1()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}