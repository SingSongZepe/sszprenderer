#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "tgaimage.h"

struct Texture
{
	TGAImage* image;

	Texture(const char* filename)
	{
		image = new TGAImage();
		image->read_tga_file(filename);
	};
	~Texture()
	{
		delete image;
	}

	TGAColor get(float u, float v)
	{
		int x = (int)image->get_width() * u;
		int y = (int)image->get_height() * (1 - v);
		return image->get(x, y);
	}
};


#endif //__TEXTURE_H__