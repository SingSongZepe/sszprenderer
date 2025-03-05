
#include "geometry.h"
#include "triangle.h"

#include <gtest/gtest.h>

TEST(barycentroidTest, test1)
{

	Vec2i* points = new Vec2i[3];
	points[0] = Vec2i( 0, 0 );
	points[1] = Vec2i{ 3, 0 };
	points[2] = Vec2i{ 3, 3 };

	Vec2i p = Vec2i{ 2, 1 };

	Vec3f barycentroid = barycentric_coord(points, p);

	std::cout << barycentroid;

	delete[] points;
}



int main1()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}