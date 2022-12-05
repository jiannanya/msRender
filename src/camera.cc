#include "camera.hh"
#include "math.hh"

namespace msr{

camera::camera(float fovy, float aspect,vec3 position, vec3 target, vec3 upDir)
    :m_Fovy(fovy)
    ,m_Aspect(aspect) 
    ,m_Position(position)
    ,m_Target(target)
    ,m_UpDir(upDir)
{       
        m_ViewMatrix = getIdentityMatrix();
        m_ProjectionMatrix = getIdentityMatrix();
        updateViewMatrix();
        updateProjectionMatrix(); 
};

void camera::updateAttitude(vec3 position, vec3 target, vec3 upDir) {
    m_Position = position;
    m_Target = target;
    m_UpDir = upDir;
    updateViewMatrix();
}


void camera::updatePosition(vec3 position) {
    m_Position = position;
    updateViewMatrix();
}


void camera::updateViewMatrix() {
    m_ViewMatrix = lookat(m_Position, m_Target, m_UpDir);
    updateViewProjectionMatrix();
}

void camera::updateProjectionMatrix() {
    m_ProjectionMatrix = perspective(m_Fovy, m_Aspect, 0.1f, 10000.0f);
    updateViewProjectionMatrix();
}

void camera::updateViewProjectionMatrix() {
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

mat4 camera::getViewMatrix(){
    return m_ViewMatrix;
}

mat4 camera::getProjectionMatrix(){
    return m_ProjectionMatrix;
}

vec3 camera::getPos(){
    return m_Position;
}

vec3 camera::getTarget(){
    return m_Target;
}

vec3 camera::getUp(){
    return m_UpDir;
}

};