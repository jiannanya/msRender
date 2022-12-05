#include "context.hh"

namespace msr{

context::context(){
    m_window = nullptr;
    m_camera = nullptr;
    m_shader = nullptr;
    m_mesh = nullptr;
    m_framebuffer = nullptr;
    m_isDrawWireFrame = false;
    m_rasterizer = new rasterizer();   
}

context::~context(){
    delete m_window;
    delete m_camera;
    delete m_shader;
    delete m_mesh;
    delete m_framebuffer;
    delete m_rasterizer; 

    m_window = nullptr;
    m_camera = nullptr;
    m_shader = nullptr;
    m_mesh = nullptr;
    m_framebuffer = nullptr;
    m_rasterizer = nullptr; 
}

void context::setWindow(window* window){
    m_window = window;
}

void context::setCamera(camera* camera){
    m_camera = camera;
}

void context::setShader(shader* shader){
    m_shader = shader;
}

void context::setMesh(mesh* mesh){
    m_mesh = mesh;
}

void context::setFrameBuffer(framebuffer* fb){
    m_framebuffer = fb;
    m_Width = fb->getWidth();
    m_Height = fb->getHeight();
}

void context::setTexture(texture* tex){
    m_texture = tex;
}

framebuffer* context::getFrameBuffer()const{
    return m_framebuffer;
}

window* context::getWindow()const{
    return m_window;
}

camera* context::getCamera()const{
    return m_camera;
}

void context::setClearColor(vec4 color){
    m_clearColor = color;
}

bool context::isCtxOk(){
    return  m_window && m_framebuffer && m_camera && m_shader && m_mesh;
}

void context::setDrawWireFrame(bool flag){
    m_isDrawWireFrame = flag;
}




void context::draw(){

    if(!isCtxOk()){
        std::cerr<<"context not ok, drawing notthing\n";
        return;
    }

    m_framebuffer->clearColorBuffer(m_clearColor);

    //render per face
    for(int i = 0; i < m_mesh->faceNum(); ++i) {
        // 1. get face vertexs 
        vec3 originVerts[3];
        for(int j = 0; j < 3; ++j)
            originVerts[j] = m_mesh->getVertex(i, j);

        // 2. transform to clip coordinates
        vec4 clipPos[3];
        for(int j = 0; j < 3; ++j)
            m_shader->vert(originVerts[j], clipPos[j]);

        // 3. clip
        bool isDiscard = false;
        for(int j = 0; j < 3; ++j)
        {
            vec4& vertex = clipPos[j];
            float w = vertex.w;
            if(w == 0.f /*|| vertex.z < 0.f || vertex.z > w || vertex.x < -w || vertex.x > w || vertex.y < -w || vertex.y > w*/)
            {
                isDiscard = true;
                break;
            }
            // normalized to (-1, 1)
            vertex = vertex / w;  
        }
        if(isDiscard)
            continue;

        // 4. transfer to viewport
        vec2 viewportPos[3];
        for(int j = 0; j < 3; ++j)
        {
            viewportPos[j].x = (clipPos[j].x + 1.f) * m_Width * 0.5f;
            viewportPos[j].y = (1.f - clipPos[j].y) * m_Height * 0.5f;
        }

        // render frame
        if(m_isDrawWireFrame)
        {
            m_rasterizer->drawLine(round(viewportPos[0].x), round(viewportPos[0].y), round(viewportPos[1].x), round(viewportPos[1].y), m_frameColor,*m_framebuffer);
            m_rasterizer->drawLine(round(viewportPos[0].x), round(viewportPos[0].y), round(viewportPos[2].x), round(viewportPos[2].y), m_frameColor,*m_framebuffer);
            m_rasterizer->drawLine(round(viewportPos[2].x), round(viewportPos[2].y), round(viewportPos[1].x), round(viewportPos[1].y), m_frameColor,*m_framebuffer);
        }else{
            m_rasterizer->drawTriangle(viewportPos[0],viewportPos[1],viewportPos[2],m_frameColor,*m_framebuffer);
        }
    }
}

};