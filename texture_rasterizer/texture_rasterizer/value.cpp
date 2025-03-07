#include "value.h"

const int WIDTH = 1024;
const int HEIGHT = 1024;

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);

// view
View view = View();

//Vec3f eye_position = Vec3f{ 1., 1., 1. };
//Vec3f gaze_dir = Vec3f{ -1., -1., -1. };
//Vec3f up_dir = Vec3f{ -1., 2., -1. };
//View view{ eye_position, gaze_dir, up_dir };

// model
extern Model* model = nullptr;

// texture
extern Texture* texture = nullptr;

const Light light_source1 = Light(Vec3f(1., 1., 1.), Vec3f(3., 3., 3.));
const Light light_source2 = Light(Vec3f(-1., 1., 0.), Vec3f(3., 3., 3.));
std::vector<Light> light_sources = { light_source1, light_source2 };

// coefficient
const Vec3f ka_ = Vec3f(0.005, 0.005, 0.005);
const Vec3f ks_ = Vec3f(0.7937, 0.7937, 0.7937);
const int P = 100;

