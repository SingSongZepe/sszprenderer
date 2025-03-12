#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) 
        {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        }
        else if (!line.compare(0, 3, "vt "))
        { // read texture coordinates
            iss >> trash >> trash;
            Vec2f v;
            for (int i = 0; i < 2; i++)
            {
                iss >> v.raw[i];
            }
            tex_coords_.push_back(v);
        }
        else if (!line.compare(0, 3, "vn "))
        { // read normals
            iss >> trash >> trash;
            Vec3f v;
            for (int i = 0; i < 3; i++)
            {
                iss >> v.raw[i];
            }
            normals_.push_back(v);
        }
        else if (!line.compare(0, 2, "f ")) 
        { // read faces
            std::vector<int> f;
            int idx, vt_idx, n_idx;
            iss >> trash;
            std::vector<int> vts;
            std::vector<int> norms;
            while (iss >> idx >> trash >> vt_idx >> trash >> n_idx) {
                idx--; // in wavefront obj all indices start at 1, not zero
                vt_idx--;
                n_idx--;
                f.push_back(idx);
				vts.push_back(vt_idx);
                norms.push_back(n_idx);
            }
            for (const int& vt : vts)
            {
                f.push_back(vt);
            }
            for (const int& norm : norms)
            {
                f.push_back(norm);
            }
            faces_.push_back(f);
        } 
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() 
{}

int Model::nverts() 
{
    return (int)verts_.size();
}

int Model::nfaces() 
{
    return (int)faces_.size();
}

int Model::ntex_coords()
{
    return (int)tex_coords_.size();
}

int Model::nnormals()
{
    return (int)normals_.size();
}

std::vector<int> Model::face(int idx) 
{
    return faces_[idx];
}

Vec3f Model::vert(int i) 
{
    return verts_[i];
}

Vec2f Model::tex_coord(int i)
{
    return tex_coords_[i];
}

Vec3f Model::normal(int i)
{
    return normals_[i];
}
