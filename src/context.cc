#include "context.hh"
#include "triangle.hh"

namespace msr{

context::context(){
    m_window = nullptr;
    m_camera = nullptr;
    m_shader = nullptr;
    m_scene = nullptr;
    m_framebuffer = nullptr;
    m_isDrawWireFrame = false;
    m_rasterizer = new rasterizer();   
}

context::~context(){}

void context::setWindow(window* window){
    m_window = window;
}

void context::setCamera(camera* camera){
    m_camera = camera;
}

void context::setShader(shader* shader){
    m_shader = shader;
}

void context::setFrameBuffer(framebuffer* fb){
    m_framebuffer = fb;
    m_Width = fb->getWidth();
    m_Height = fb->getHeight();
}

void context::setTexture(texture* tex){
    m_texture = tex;
}

void context::setScene(scene* sce){
    m_scene = sce;
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

void context::setModelMatrix(mat4 ma){
    m_modelMatrix = ma;
}

bool context::isCtxOk(){
    return  m_window && m_framebuffer && m_camera && m_shader && m_scene;
}

void context::setDrawWireFrame(bool flag){
    m_isDrawWireFrame = flag;
}




void context::draw(){

    if(!isCtxOk()){
        std::cerr<<"context not ok, drawing notthing\n";
        return;
    }

    m_shader->setModel(m_modelMatrix);
    m_shader->setView(m_camera->getViewMatrix());
    m_shader->setPerspective(m_camera->getProjectionMatrix());

    m_framebuffer->clearColorBuffer(m_clearColor);
    m_framebuffer->clearZBuffer();

    mat4 n_matrix = transpose(inverse(m_modelMatrix));// normal transform matrix
    
    auto mesh_list = m_scene->getMeshList();
    

    //render per face
    for(auto&mesh: mesh_list)
    for(int i = 0; i < mesh->faceNum(); ++i) {

        triangle tri = triangle();

        // 1. get face vertexs 
        vec2 uv[3];
        vec4 col[3];
        vec3 localVerts[3], nor[3], nw[3];
        for(int j = 0; j < 3; ++j){
            localVerts[j] = mesh->getVertex(i, j);
            uv[j] = mesh->getTexcoord(i,j);
            nor[j] = mesh->getNormal(i,j);
            col[j] = m_frameColor;

            vec4 tn = vec4(nor[j].x,nor[j].y,nor[j].z,0.0);
            vec4 tnn = n_matrix * tn;
            nw[j] = vec3(tnn.x, tnn.y, tnn.z);
        }

        
        tri.setVertices(localVerts);
        tri.setTexCords(uv);
        tri.setNormals(nor);
        tri.setWorldNormals(nw);
        tri.setColors(col);


        // 2. transform to clip coordinates using vertex shader
        vec4 clipPos[3], worldPosH[3];
        for(int k = 0; k < 3; ++k)
            m_shader->vert(localVerts[k],worldPosH[k], clipPos[k]); 

        // 3. clip
        UINT discardCount = 0;
        vec3 worldPos[3];
        for(int k = 0; k < 3; ++k)
        {
            vec4& vertex = clipPos[k];
            float w = vertex.w;
            if(vertex.z < -w || vertex.z > 0.f || vertex.x < -w || vertex.x > w || vertex.y < -w || vertex.y > w)
            {
                discardCount++;
            }
            // perspective division, normalized to (-1, 1)
            vertex = vertex / w;  

            vec4& vw = worldPosH[k];
            vw = vw/vw.w;
            worldPos[k] = vec3(vw.x,vw.y,vw.z);
        }

        tri.setWorldVertices(worldPos);

        // all three points of a triangle outside is clipped, otherwise keep rendering
        if(discardCount==3)
            continue;

        // 4. viewport
        vec3 viewportPos[3];
        for(int k = 0; k < 3; ++k)
        {
            viewportPos[k].x = int((clipPos[k].x + 1.f) * m_Width * 0.5f); //need cast to int for preventing gap between triangles
            viewportPos[k].y = int((1.f - clipPos[k].y) * m_Height * 0.5f);
            viewportPos[k].z = clipPos[k].z;
        }

        tri.setViewPortVertices(viewportPos);

        // render framewire
        if(m_isDrawWireFrame)
        {
            m_rasterizer->drawTriangleLine(tri,m_frameColor,*m_framebuffer);
        }else{
            //m_rasterizer->drawTriangle(tri,m_frameColor,*m_framebuffer);
            m_rasterizer->drawTriangle(tri,*m_shader,*m_framebuffer,*m_camera);
        }
    }
}

void context::show(){
    m_window->drawBuffer();
}

};