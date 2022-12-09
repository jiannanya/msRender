#ifndef CONTEXT_HH
#define CONTEXT_HH

#include "math.hh"
#include "mesh.hh"
#include "shader.hh"
#include "windows.hh"
#include "camera.hh"
#include "framebuffer.hh"
#include "texture.hh"
#include "rasterizer.hh"
#include "scene.hh"

namespace msr{

class context{
public:
    context();
    ~context();

    void setWindow(window* window);
    void setCamera(camera* camera);
    void setShader(shader* camera);
    void setFrameBuffer(framebuffer* fb);
    void setTexture(texture* tex);
    void setScene(scene* sce);
    

    framebuffer* getFrameBuffer()const;
    window* getWindow()const;
    camera* getCamera()const;

    
    void setClearColor(vec4 color);
    void setDrawWireFrame(bool flag);
    void setModelMatrix(mat4 ma);
    void draw();
    void show();

private:

    bool isCtxOk();

    window* m_window;
    camera* m_camera;
    shader* m_shader;
    framebuffer* m_framebuffer;
    rasterizer* m_rasterizer;
    texture* m_texture;
    scene* m_scene;

    bool m_isDrawWireFrame;
    int m_Width, m_Height;
    vec4 m_frameColor = vec4(1.0f,1.0f,1.0f,1.0f);
    vec4 m_clearColor;
    mat4 m_modelMatrix;



};

};
#endif