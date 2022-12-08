#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "include.hh"
#include "global.hh"
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

int main()
{

    msr::framebuffer fb(msr::WINDOW_WIDTH,msr::WINDOW_HEIGHT);
    msr::window wd(msr::TITLE, &fb);

    msr::mesh model = msr::mesh(msr::OBJ_PATH);
    msr::texture tex = msr::texture(std::string(msr::OBJ_TEXTURE_PATH));

    msr::camera cam(msr::FOV_INIT, float(msr::WINDOW_WIDTH) / msr::WINDOW_HEIGHT,msr::CAM_POS_INIT, msr::CAM_TARGET_INIT,msr::CAM_UP_INIT);

    msr::mat4 modelMatrix = msr::getIdentityMatrix();

    msr::shader phone_shader = msr::shader();
    phone_shader.setModel(modelMatrix);
    phone_shader.setView(cam.getViewMatrix());
    phone_shader.setPerspective(cam.getProjectionMatrix());
    phone_shader.setDiffuseTexture(&tex);

    msr::pointlight light1 = msr::pointlight(msr::vec3(0, 0, 20), msr::vec3(1,1,1), 500);
    msr::pointlight light2 = msr::pointlight(msr::vec3(0, 20, 0), msr::vec3(1,1,1), 500);
    msr::pointlight light3 = msr::pointlight(msr::vec3(20, 0, 0), msr::vec3(1,1,1), 500);
    phone_shader.pushLight(&light1);
    phone_shader.pushLight(&light2);
    phone_shader.pushLight(&light3);


    msr::context ctx = msr::context();
    ctx.setFrameBuffer(&fb);
    ctx.setWindow(&wd);
    ctx.setCamera(&cam);
    ctx.setMesh(&model);
    ctx.setTexture(&tex);
    ctx.setShader(&phone_shader);
    ctx.setDrawWireFrame(false);
    ctx.setClearColor(msr::vec4(0.0f,0.0f,0.0f,1.0f));
    ctx.setModelMatrix(modelMatrix);

    msr::renderer render(ctx);
    render.render();


    //render.filpFrameBuffer();
    //render.saveToBmp("out.bmp");

// #if defined(WIN32) || defined(_WIN32)
// 	system("mspaint out.bmp");
// #endif
//    std::cout<<"end main"<<std::endl;
    return 0;
}