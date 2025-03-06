
#include "geometry.h"
#include "triangle.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(barycentroidTest, test1)
{
	Vec3f v0{ 0., 0., 0. };
	Vec3f v1{ 1., 0., 1. };
	Vec3f v2{ 1., 1., 2. };

	Vec3f* points = new Vec3f[3];
	points[0] = v0;
	points[1] = v1;
	points[2] = v2;

	Vec3f p0{ 0., 0., 0. };
	Vec3f p1{ 1., 0., 0. };
	Vec3f p2{ 1., 1., 0. };

	Vec3f expected_c0{ 1., 0., 0. };
	Vec3f expected_c1{ 0., 1., 0. };
	Vec3f expected_c2{ 0., 0., 1. };

	//Vec3f c0 = barycentric_coord(points, p0);
	//EXPECT_EQ(c0, expected_c0);
	//std::cout << c0;

	//Vec3f c1 = barycentric_coord(points, p1);
	//EXPECT_EQ(c1, expected_c1);
	//std::cout << c1;

	//Vec3f c2 = barycentric_coord(points, p2);
	//EXPECT_EQ(c2, expected_c2);
	//std::cout << c2;

	//Vec3f p3{ 2. / 3, 1. / 3, 0. };
	//Vec3f expected_c3{ 1. / 3, 1. / 3, 1. / 3 };

	//Vec3f c3 = barycentric_coord(points, p3);
	////EXPECT_EQ(c3, expected_c3);
	//std::cout << c3;


	//Vec3f p4{ 1. / 3, 1. / 3, 0. };
	////Vec3f expected_c3{ 1. / 3, 1. / 3, 1. / 3 };

	//Vec3f c4 = barycentric_coord(points, p4);
	////EXPECT_EQ(c3, expected_c3);
	//std::cout << c4;
}



int main1()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}