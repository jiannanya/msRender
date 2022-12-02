#ifndef CONTEXT_HH
#define CONTEXT_HH

#define NOMINMAX

#include "include.hh"
#include "math.hh"
#include "mesh.hh"
#include "shader.hh"
#include "windows.hh"
#include "camera.hh"
#include "framebuffer.hh"
#include "texture.hh"
#include "rasterizer.hh"

namespace msr{

class context{
public:
    context();
    ~context();

    void setWindow(window* window);
    void setCamera(camera* camera);
    void setShader(shader* camera);
    void setMesh(mesh* mesh);
    void setFrameBuffer(framebuffer* fb);
    void setTexture(texture* tex);

    framebuffer* getFrameBUffer()const;
    window* getWindow()const;
    camera* getCamera()const;

    
    void clearColor(vec4 color);
    void setDrawWireFrame(bool flag);
    void draw();

private:

    bool isCtxOk();

    window* m_window;
    camera* m_camera;
    shader* m_shader;
    mesh*   m_mesh;
    framebuffer* m_framebuffer;
    rasterizer* m_rasterizer;
    texture* m_texture;
    bool m_isDrawWireFrame;
    int m_Width, m_Height;
    vec4 m_frameColor = vec4(1.0f,1.0f,1.0f,1.0f);



};

};
#endif