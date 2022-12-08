#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include "math.hh"

namespace msr{

class triangle{
public:
    triangle();

    // vertex local pos
    vec3 a();
    vec3 b();
    vec3 c();

    // vertex world pos
    vec3 aw(); 
    vec3 bw();
    vec3 cw();

    // vertex viewport pos
    vec3 avp(); 
    vec3 bvp();
    vec3 cvp();

    // texture coordinate
    vec2 at();
    vec2 bt();
    vec2 ct();

    // normal local
    vec3 an();
    vec3 bn();
    vec3 cn();

    // normal world
    vec3 anw();
    vec3 bnw();
    vec3 cnw();    

    // color
    vec4 ac();
    vec4 bc();
    vec4 cc();


    void setVertices(vec3 ve[]);
    void setWorldVertices(vec3 vw[]);
    void setViewPortVertices(vec3 vp[]);
    void setTexCords(vec2 vt[]);
    void setNormals(vec3 vn[]);
    void setWorldNormals(vec3 vnw[]);
    void setColors(vec4 vc[]);

private:

    vec3 _ve[3]; //vertex local coordinate
    vec3 _vw[3]; //vertex world coordinate
    vec3 _vp[3]; //vertex viewport coordinate
    vec2 _vt[3]; //vertex texture coordinate
    vec3 _vn[3]; //vertex normal
    vec3 _vnw[3]; // vertex world normal
    vec4 _vc[3]; //vertex color

};

}

#endif