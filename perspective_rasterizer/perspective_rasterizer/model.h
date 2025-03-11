#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	// each vert <-map-> tex_coord
	std::vector<Vec2f> tex_coords_;
	std::vector<Vec3f> normals_;
	std::vector<std::vector<int> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	int ntex_coords();
	int nnormals();
	Vec3f vert(int i);
	Vec2f tex_coord(int i);
	Vec3f normal(int i);
	std::vector<int> face(int idx);
};

#endif //__MODEL_H__
