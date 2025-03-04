
#include "geometry.h"
#include "view.h"

#include <gtest/gtest.h>

//TEST(simpleTest, test1) 
//{
//	EXPECT_EQ(1, 1);
//}

//TEST(matrixTest, test1)
//{
//	Mat4f mat = Mat4f::zeros<float, 4>();
//	mat.set(0, 1, 10.f);
//	mat.set(3, 2, 2.f);
//	mat.set(2, 0, 8.f);
//
//	std::cout << mat;
//
//	Vec4f v1{ 3.f, 4.f, 6.f, 10.f };
//	Vec4f v2 = mat * v1;
//
//	std::cout << v2;
//}

//TEST(vectorTest, test1)
//{
//	Vec3i v1{ 1, 2, 3 };
//	Vec3i n1 = v1.normalized();
//
//	std::cout << v1;
//	std::cout << n1;
//
//	Vec3f v2{ 1.0, 2.0, 3.0 };
//	Vec3f n2 = v2.normalized();
//
//	std::cout << v2;
//	std::cout << n2;
//}

//TEST(matrixTest, test2)
//{
//	Mat mat1 = Mat<float, 2, 2>();
//	Mat mat2 = Mat<float, 2, 2>();
//
//	Mat<float, 2, 2> mat = mat1 * mat2;
//
//	std::cout << mat;
//}

TEST(viewTest, test1)
{
	Vec3f cameraPosition(3.0f, 5.0f, 2.0f); // Camera position  
	Vec3f gazeDirection(-1.f, -1.f, -1.0f); // Looking towards negative Z direction  
	Vec3f upVector(-1.f, 2.f, -1.f); // Up is in the positive Y direction 

	if (gazeDirection.dot_product(upVector) != 0.0)
	{
		throw std::runtime_error("gaze and up vector should be orthogonal");
	}

	View view{cameraPosition, gazeDirection, upVector};

	Vec4f pointInWorld(1.f, 2.f, 3.f, 1.f);

	Vec4f pointInCameraSpace = view.transform(pointInWorld);

	std::cout << pointInCameraSpace;
}

int main1()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}