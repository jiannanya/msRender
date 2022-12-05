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

int main()
{

    msr::framebuffer fb(msr::WINDOW_WIDTH,msr::WINDOW_HEIGHT);
    msr::window wd(msr::TITLE, &fb);

    msr::mesh model = msr::mesh(msr::OBJ_PATH);
    msr::texture tex = msr::texture(std::string(msr::OBJ_TEXTURE_PATH));

    msr::camera cam(msr::FOV_INIT, float(msr::WINDOW_WIDTH) / msr::WINDOW_HEIGHT,msr::CAM_POS_INIT, msr::CAM_TARGET_INIT,msr::CAM_UP_INIT);

    msr::Shader_Phong phone_shader = msr::Shader_Phong();
    phone_shader.model = msr::getIdentityMatrix();
    // phone_shader.view = msr::lookat(cam.getPos(), cam.getTarget(), cam.getTarget());
    // phone_shader.persp = msr::perspective(msr::FOV_INIT,float(msr::WINDOW_WIDTH) / msr::WINDOW_HEIGHT, 0.1f, 10000.0f);
    phone_shader.view = cam.getViewMatrix();
    phone_shader.persp = cam.getProjectionMatrix();

    msr::context ctx = msr::context();
    ctx.setFrameBuffer(&fb);
    ctx.setWindow(&wd);
    ctx.setCamera(&cam);
    ctx.setMesh(&model);
    ctx.setTexture(&tex);
    ctx.setShader(&phone_shader);
    ctx.setDrawWireFrame(true);
    ctx.setClearColor(msr::vec4(0.0f,0.0f,0.0f,1.0f));

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