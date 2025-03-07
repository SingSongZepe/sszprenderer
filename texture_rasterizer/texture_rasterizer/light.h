#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "geometry.h"

class Light
{
public:
	Vec3f position;
	Vec3f indensity;
	
	Light(Vec3f position, Vec3f indensity)
		: position(position), indensity(indensity)
	{ }
};

#endif // __LIGHT_H__

