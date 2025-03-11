#ifndef __SHADER_H__
#define __SHADER_H__

#include "geometry.h"
#include "fragment_payload.h"
#include "value.h"

//Eigen::Vector3f displacement_fragment_shader(const fragment_shader_payload& payload)
Vec3f texture_fragment_shader(const FragmentShaderPayload& payload);

#endif // !__SHADER_H__

