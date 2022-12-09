#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <memory.h>

#include "mesh.hh"
#include "shader.hh"
#include "windows.hh"
#include "camera.hh"
#include "framebuffer.hh"
#include "renderer.hh"
#include "texture.hh"
#include "context.hh"
#include "math.hh"
#include "triangle.hh"
#include "pointlight.hh"
#include "scene.hh"

using namespace msr;

const char *TITLE = "my real time soft render";
const char *OBJ_PATH = "../assert/african_head.obj";
const char *OBJ_TEXTURE_PATH =  "../assert/african_head_diffuse.tga";

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr float FOV_INIT = 45.0f;

vec3 CAM_POS_INIT = vec3(1, 1, 3);
vec3 CAM_TARGET_INIT = vec3(0,0,0);
vec3 CAM_UP_INIT = vec3(0,1,0);

int main()
{
    framebuffer ms_framebuffer = framebuffer(WINDOW_WIDTH,WINDOW_HEIGHT);
    window ms_window = window(TITLE, &ms_framebuffer);

    mesh ms_model1 = mesh(OBJ_PATH);
    texture ms_texture = texture(std::string(OBJ_TEXTURE_PATH));

    camera ms_camera = camera(FOV_INIT, float(WINDOW_WIDTH) / WINDOW_HEIGHT,CAM_POS_INIT, CAM_TARGET_INIT,CAM_UP_INIT);

    mat4 modelMatrix = getIdentityMatrix();

    shader ms_shader = shader();
    ms_shader.setModel(modelMatrix);
    ms_shader.setView(ms_camera.getViewMatrix());
    ms_shader.setPerspective(ms_camera.getProjectionMatrix());
    ms_shader.setDiffuseTexture(&ms_texture);

    pointlight ms_light1 = pointlight(vec3(0, 20, 0), vec3(1,1,1), 500);
    pointlight ms_light2 = pointlight(vec3(20, 0, 0), vec3(1,1,1), 500);
    ms_shader.pushLight(&ms_light1);
    ms_shader.pushLight(&ms_light2);

    scene ms_scene = scene();
    ms_scene.addMesh(&ms_model1);


    context ms_context = context();
    ms_context.setFrameBuffer(&ms_framebuffer);
    ms_context.setWindow(&ms_window);
    ms_context.setCamera(&ms_camera);
    ms_context.setScene(&ms_scene);
    ms_context.setTexture(&ms_texture);
    ms_context.setShader(&ms_shader);
    ms_context.setDrawWireFrame(false);
    ms_context.setClearColor(vec4(0.0f,0.0f,0.0f,1.0f));
    ms_context.setModelMatrix(modelMatrix);

    renderer ms_render =  renderer(ms_context);
    ms_render.render();

    return 0;
}