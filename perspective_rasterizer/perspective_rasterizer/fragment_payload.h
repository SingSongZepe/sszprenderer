#ifndef __FRAGMENT_PAYLOAD_H__
#define __FRAGMENT_PAYLOAD_H__

#include "geometry.h"
#include "texture.h"

class FragmentShaderPayload
{
public:
	FragmentShaderPayload(const TGAColor& color, const Vec3f& normal, const Vec2f tex_coord, Texture* texture)
		: color(color), normal(normal), tex_coord(tex_coord), texture(texture) {};

	// the position in camera space
	Vec3f space_coord;
	TGAColor color;
	Vec3f normal;
	Vec2f tex_coord;
	Texture* texture;
};


#endif // __FRAGMENT_PAYLOAD_H__