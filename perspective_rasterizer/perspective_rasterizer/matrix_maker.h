#ifndef __MATRIX_MAKER_H__
#define __MATRIX_MAKER_H__

#include "value.h"
#include "view.h"
#include "geometry.h"

inline constexpr double PI = 3.14159265358979323846;

// the angle is in degrees, and rotates counterclockwise around y-axis
extern Mat4f make_model_matrix(const float& angle) noexcept;

extern Mat4f make_view_matrix(const View& view) noexcept;

// where the n is the near clipping space, f is the far clipping space
// aspect_ratio = w / h;
extern Mat4f make_projection_matrix(float fov, float aspect_ratio, float n, float f) noexcept;

#endif // __MATRIX_MAKER_H__