#ifndef GLOBAL_HH
#define GLOBAL_HH

#include "include.hh"
#include "math.hh"

namespace msr{

const char *TITLE = "my real time soft render";
const char *OBJ_PATH = "../assert/african_head.obj";
const char *OBJ_TEXTURE_PATH =  "../assert/african_head_diffuse.tga";

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float FOV_INIT = 45.0f;

vec3 CAM_POS_INIT = vec3(1, 1, 3);
vec3 CAM_TARGET_INIT = vec3(0,0,0);
vec3 CAM_UP_INIT = vec3(0,1,0);



};

#endif