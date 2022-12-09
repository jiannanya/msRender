#ifndef CAMERA_HH
#define CAMERA_HH

#include "math.hh"

namespace msr{

class camera {
public:

    vec3 m_Position;
    vec3 m_Target;
    vec3 m_UpDir;

    mat4 m_ViewMatrix;
    mat4 m_ProjectionMatrix;
    mat4 m_ViewProjectionMatrix;

    float m_Fovy;
    float m_Aspect;

    camera(){}
    camera(float fovy, float aspect,vec3 position, vec3 target, vec3 upDir=vec3(0,1,0));

    void updateAttitude(vec3 position, vec3 target, vec3 upDir=vec3(0,1,0));

    void updatePosition(vec3 position);

    mat4 getViewMatrix();
    mat4 getProjectionMatrix();
    vec3 getPos();
    vec3 getTarget();
    vec3 getUp();

private:
    void updateViewMatrix();
    void updateProjectionMatrix();
    void updateViewProjectionMatrix();
};

};

#endif