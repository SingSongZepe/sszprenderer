#ifndef __VALUE_H__
#define __VALUE_H__

#include "tgaimage.h"
#include "model.h"
#include "texture.h"
#include "light.h"
#include "view.h"

extern const int WIDTH;
extern const int HEIGHT;
extern const TGAColor WHITE;
extern const TGAColor RED;

// define the view
extern View view;


// model
extern Model* model;

// texture
extern Texture* texture;

// light
// defind the light source
// parallel light source, denote by simply a vector
extern const Light light_source1;
extern const Light light_source2;
extern std::vector<Light> light_sources;

// some coefficient, while kd is the diffuse coefficient, it's value depending on the material.
extern const Vec3f ka_;
//Vec3f kd = payload.color;
extern const Vec3f ks_;
// for specualar term
extern const int P;

#endif // !__VALUE_H__