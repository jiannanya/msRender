#ifndef SHADER_HH
#define SHADER_HH

#include "math.hh"
#include "texture.hh"
#include "pointlight.hh"

#include <vector>

namespace msr{

struct fragmentdata{
    vec3 screenPos;
    vec3 worldPos;
    vec3 worldNor;
    vec3 worldCamPos;
    vec4 color;
    vec2 uv;

};

//blinn-phong
class shader
{
public:
    shader(){}
    ~shader(){}

    void setModel(mat4 m);
    void setView(mat4 v);
    void setPerspective(mat4 pe);
    void setDiffuseTexture(texture* tex);
    void pushLight(pointlight* pl);

    void vert(vec3 inPos, vec4& outWorldPos, vec4& outClipPos);
    vec4 frag_phong(fragmentdata& fg);
    vec4 frag_texture(fragmentdata& fg);

private:

    mat4 model;
    mat4 view;
    mat4 persp;

    texture* diffuseTex;

    vec4  kd;
    float ks;
    float ka;
    float amb_light_intensity;
    std::vector<pointlight*> _lights;

};


}

#endif