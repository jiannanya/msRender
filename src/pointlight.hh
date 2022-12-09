#ifndef POINTLIGHT_HH
#define POINTLIGHT_HH

#include "math.hh"

namespace msr{
//point light
class pointlight{
public:
    pointlight(){}
    pointlight(vec3 pos, vec3 color, float intensity);

    vec3 getpos()const;
    vec3 getcolor()const;
    float getintensity()const;

private:
    vec3 pos;
    vec3 color;
    float intensity;

};

}
#endif