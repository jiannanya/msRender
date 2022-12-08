
#include "triangle.hh"

namespace msr{

triangle::triangle(){
    for(int k=0;k<3;k++){
        _ve[k] = _vn[k]  = {0.f,0.f,0.f};
        _vt[k] = {1.f,1.f};
        _vc[k] = {1.f,1.f,1.f,1.f};
    }
}

vec3 triangle::a(){
    return _ve[0];
}

vec3 triangle::b(){
    return _ve[1];
}

vec3 triangle::c(){
    return _ve[2];
}

vec3 triangle::aw(){
    return _vw[0];
}

vec3 triangle::bw(){
    return _vw[1];
}

vec3 triangle::cw(){
    return _vw[2];
}

vec3 triangle::avp(){
    return _vp[0];
}

vec3 triangle::bvp(){
    return _vp[1];
}

vec3 triangle::cvp(){
    return _vp[2];
}

vec2 triangle::at(){
    return _vt[0];
}
vec2 triangle::bt(){
    return _vt[1];
}
vec2 triangle::ct(){
    return _vt[2];
}

vec3 triangle::an(){
    return _vn[0];
}

vec3 triangle::bn(){
    return _vn[1];
}

vec3 triangle::cn(){
    return _vn[2];
}

vec3 triangle::anw(){
    return _vnw[0];
}

vec3 triangle::bnw(){
    return _vnw[1];
}

vec3 triangle::cnw(){
    return _vnw[2];
}


vec4 triangle::ac(){
    return _vc[0];
}

vec4 triangle::bc(){
    return _vc[1];
}

vec4 triangle::cc(){
    return _vc[2];
}

void triangle::setVertices(vec3 ve[]){
    _ve[0] = ve[0];
    _ve[1] = ve[1];
    _ve[2] = ve[2];
    
}

void triangle::setWorldVertices(vec3 vw[]){
    _vw[0] = vw[0];
    _vw[1] = vw[1];
    _vw[2] = vw[2];
}

void triangle::setViewPortVertices(vec3 vp[]){
    _vp[0] = vp[0];
    _vp[1] = vp[1];
    _vp[2] = vp[2];
}

void triangle::setTexCords(vec2 vt[]){
    _vt[0] = vt[0];
    _vt[1] = vt[1];
    _vt[2] = vt[2];
}

void triangle::setNormals(vec3 vn[]){
    _vn[0] = vn[0];
    _vn[1] = vn[1];
    _vn[2] = vn[2];
}

void triangle::setWorldNormals(vec3 vnw[]){
    _vnw[0] = vnw[0];
    _vnw[1] = vnw[1];
    _vnw[2] = vnw[2];
}

void triangle::setColors(vec4 vc[]){
    _vc[0] = vc[0];
    _vc[1] = vc[1];
    _vc[2] = vc[2];
}

}