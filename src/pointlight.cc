#include "pointlight.hh"

namespace msr{

pointlight::pointlight(vec3 pos, vec3 color,float intensity)
    : pos(pos)
    , color(color)
    , intensity(intensity)
{

}

vec3 pointlight::getpos()const{
    return pos;
}

vec3 pointlight::getcolor()const{
    return color;
}

float pointlight::getintensity()const{
    return intensity;
}

}
