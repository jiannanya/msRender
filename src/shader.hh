#ifndef SHADER_HH
#define SHADER_HH

#include "math.hh"
#include "texture.hh"

namespace msr{

class shader
{
public:
    virtual void vert(vec3 inPos, vec4& outClipPos) {}
    virtual void frag(vec4 inClipPos, vec4& outColor) {}
};

class Shader_Phong : public shader
{
public:
    mat4 model;
    mat4 view;
    mat4 persp;
    texture* diffuseTex;
    texture* normalTex;
    vec3 lightPos;
    vec3 lightColor;

    virtual void vert(vec3 inPos, vec4& outClipPos);
    virtual void frag(vec4 inClipPos, vec4& outColor);
};

};

#endif