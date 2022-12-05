#include "math.hh"

namespace msr{

float frac(float t) {
    float r = t - (int)t;
    if(r < 0.f)
        r = 1.0f - std::abs(r);

    return r;
}

vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

vec3 normalized(const vec3& v) {
    vec3 ret(v.x, v.y, v.z);
    ret.normalize();
    return ret;
}

vec3 barycentric(vec2& A, vec2& B, vec2& C, vec2& p) {
    vec3 xvec(C.x - A.x, B.x - A.x, A.x - p.x);
    vec3 yvec(C.y - A.y, B.y - A.y, A.y - p.y);
    vec3 u = cross(xvec, yvec);
    if(std::abs(u.z) < 0.999f)
        return vec3(-1, 1, 1); // will thrown away by rasterizator

    return vec3(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
}

mat4 getIdentityMatrix() {
    mat4 ret;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            ret[i][j] = (i == j ? 1.0f : 0.0f);
    return ret;
}

mat4 getTranslateMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][3] = x;
    ret[1][3] = y;
    ret[2][3] = z;
    return ret;
}

mat4 getScaleMatrix(float x, float y, float z) {
    mat4 ret = getIdentityMatrix();
    ret[0][0] = x;
    ret[1][1] = y;
    ret[2][2] = z;
    return ret;
}

mat4 lookat(vec3 eye, vec3 target, vec3 upd) {
    mat4 ret = getIdentityMatrix();

    vec3 forward = eye - target;
    forward.normalize();

    vec3 left = cross(upd,forward);
    left.normalize();

    vec3 up = cross(forward,left);
    up.normalize();

    ret[0][0] = left.x;
    ret[1][0] = left.y;
    ret[2][0] = left.z;
    ret[0][1] = up.x;
    ret[1][1] = up.y;
    ret[2][1] = up.z;
    ret[0][2] = forward.x;
    ret[1][2] = forward.y;
    ret[2][2] = forward.z;

    ret[0][3] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    ret[1][3] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
    ret[2][3] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;


    return ret;
}

mat4 perspective(float fov, float aspect, float znear, float zfar) {
    float fax = 1.0f / (float)tan(fov * 0.5f);
    mat4 ret = getIdentityMatrix();
    ret[0][0] = fax / aspect;
    ret[1][1] = fax;
    ret[2][2] = zfar / (zfar - znear);
    ret[3][2] = -znear * zfar / (zfar - znear);
    ret[2][3] = 1.f;
    return ret;
}

};