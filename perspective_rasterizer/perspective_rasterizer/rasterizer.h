#ifndef __RASTERIZER_H__
#define __RASRERIZER_H__

#include "geometry.h"
#include "texture.h"
#include "fragment_payload.h"
#include "triangle.h"

#include <vector>
#include <optional>
#include <functional>

class Rasterizer
{
public:
	Rasterizer(int w, int h, TGAImage* img)
	{
		width = w;
		height = h;
		image = img;

		// zbuffer
		depth_buf = std::vector<float>(w * h, -std::numeric_limits<float>::infinity());
	}
	
	void set_model(const Mat4f& m);
	void set_view(const Mat4f& v);
	void set_projection(const Mat4f& p);

	void set_texture(Texture* t);
	
	//void set_vertex_shader(std::function<Vec3f(VertexShaderPayload)> f);
	void set_fragment_shader(std::function<Vec3f(FragmentShaderPayload)> f);

	void set_pixel(const Vec2i& point, const Vec3f& color);

	void draw(std::vector<Triangle*>& tri_list);

	void save_image();

	void clear_buf();

private:
	void draw_triangle(const Triangle& tri, const Vec4f* space_coords);

private:
	Mat4f model;
	Mat4f view;
	Mat4f projection;
	
	TGAImage* image;

	std::optional<Texture> texture;

	std::function<Vec3f(FragmentShaderPayload)> fragment_shader;
	//std::function<Vec3f(VertexShaderPayload)> vertex_shader;

	std::vector<Vec3f> fragment_buf;
	std::vector<float> depth_buf;

	int get_index(int x, int y);

	int width, height;

	int next_id = 0;
	int get_next_id()
	{
		return next_id++;
	}

	Texture* get_texture()
	{
		if (texture.has_value())
		{
			return &texture.value();
		}
		else
		{
			return nullptr;
		}
	}
};


#endif // __RASRERIZER_H__