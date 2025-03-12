
#include "matrix_maker.h"

extern Mat4f make_model_matrix(const float& angle) noexcept
{
	Mat4f rotate = Mat4f::zeros<float, 4>();
	float angle_rad = angle * PI / 180.;
	rotate[0][0] = cos(angle_rad);
	rotate[0][2] = sin(angle_rad);
	rotate[1][1] = 1.;
	rotate[2][0] = -sin(angle_rad);
	rotate[2][2] = cos(angle_rad);
	rotate[3][3] = 1.;

	Mat4f scale = Mat4f::zeros<float, 4>();
	scale[0][0] = 2.5;
	scale[1][1] = 2.5;
	scale[2][2] = 2.5;
	scale[3][3] = 1.;

	Mat4f translate = Mat4f::identity<float, 4>();
	translate[0][3] = 0.5;
	translate[1][3] = 1.0;
	translate[2][3] = 0.0;

	return translate * rotate * scale;
}

extern Mat4f make_view_matrix(const View& view) noexcept
{
	return view.view_mat;
}

// where the n is the near clipping space, f is the far clipping space
// aspect_ratio = w / h;
extern Mat4f make_projection_matrix(float fov, float aspect_ratio, float n, float f) noexcept
{
	float fov_rad = fov * PI / 180;

	float h = 2 * tan(fov_rad / 2) * n;
	float w = h * aspect_ratio;

	Mat4f orthorgraphic = Mat4f::zeros<float, 4>();
	orthorgraphic[0][0] = 1 / w;
	orthorgraphic[1][1] = 1 / h;
	orthorgraphic[2][2] = 1 / (f - n);
	orthorgraphic[2][3] = -(f + n) / 2. / (f - n);
	orthorgraphic[3][3] = 1;

	Mat4f perspec2ortho = Mat4f::zeros<float, 4>();
	perspec2ortho[0][0] = n;
	perspec2ortho[1][1] = n;
	perspec2ortho[2][2] = f + n;
	perspec2ortho[2][3] = -n * f;
	perspec2ortho[3][2] = 1;

	return orthorgraphic * perspec2ortho;
}