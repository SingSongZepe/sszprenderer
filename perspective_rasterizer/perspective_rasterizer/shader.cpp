#include "shader.h"

Vec3f texture_fragment_shader(const FragmentShaderPayload& payload)
{ // use a model to render the texture
	
	Vec4f tmp = payload.space_coord;
	Vec3f space_coord = tmp.to_normal_pos_vec();
	
	Vec3f view_dir = (view.e - space_coord).normalized();
	Vec3f normal_dir = payload.normal;

	Vec3f kd = payload.texture->get(payload.tex_coord.x, payload.tex_coord.y).to_vec3().to_vec3f();
	Vec3f ks = ks_;
	Vec3f ka = ka_;

	Vec3f result_color{ 0., 0., 0. };
	for (const Light& light : light_sources)
	{
		Vec3f light_dir = (light.position - space_coord).normalized();
		float r_squd = light.position.distance_squared_to(space_coord);
		// diffuse term 
		float a = normal_dir.dot_product(light_dir);

		Vec3f diffuse_term = kd * light.indensity / r_squd * (std::max(0.f, normal_dir.dot_product(light_dir)));
		
		// specular term
		Vec3f half_dir = (view_dir + light_dir).normalized();
		Vec3f specular_term = ks * light.indensity / r_squd * pow(std::max(0.f, normal_dir.dot_product(half_dir)), P);
		
		// ambient term
		Vec3f ambient_term = ka * light.indensity;

		result_color += diffuse_term + specular_term + ambient_term;
	}

	return result_color.bitwise_min(Vec3f{ 255., 255., 255. });
}
