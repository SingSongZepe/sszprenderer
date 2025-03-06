#ifndef __VIEW_H__
#define __VIEW_H__

#include "geometry.h"

struct View
{
	Vec3f e;
	Vec3f g;
	Vec3f t;
	Mat4f view_mat;

	View() : e(Vec3f{0., 0., 0.}), g(Vec3f{0., 0., -1.}), t(Vec3f{0., 1.0, 0.0})
		//, view_mat(construct_view_mat()) you can't just use this function to init the view_mat
	{ 
		if (g.dot_product(t) != 0)
		{
			throw std::runtime_error("g and t are not orthogonal");
		}
		view_mat = construct_view_mat();
	}
	View(Vec3f e, Vec3f g, Vec3f t) : e(e), g(g), t(t)
	{
		if (g.dot_product(t) != 0)
		{
			throw std::runtime_error("g and t are not orthogonal");
		}
		view_mat = construct_view_mat();
	}

	void setCamera(Vec3f _e, Vec3f _g, Vec3f _t)
	{
		if (g.dot_product(t) != 0)
		{
			std::cout << "g and t are not orthogonal\n";
			return;
		}
		this->e = _e;
		this->g = _g;
		this->t = _t;
		this->view_mat = construct_view_mat();
	}

	// when can't the state of camera, you can use this function to update
	// view_mat
	Mat4f construct_view_mat()
	{
		Mat4f rot_mat = Mat4f::identity<float, 4>();
		Mat4f tran_mat = Mat4f::identity<float, 4>();

		Vec3f ug_cross_t = g.cross_product(t).normalized();
		Vec3f ut = t.normalized();
		Vec3f uminus_g = (-g).normalized();

		for (int i = 0; i < 3; i++)
		{
			rot_mat.matrix[0][i] = ug_cross_t.raw[i];
			rot_mat.matrix[1][i] = ut.raw[i];
			rot_mat.matrix[2][i] = uminus_g.raw[i];

			tran_mat.matrix[i][3] = -e.raw[i];
		}

		view_mat = rot_mat * tran_mat;

		return view_mat;
	}

	Vec4f transform(const Vec4f& p) 
	{
		return view_mat * p;
	}
};




#endif  // __VIEW_H__