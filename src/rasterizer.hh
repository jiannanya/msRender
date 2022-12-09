#ifndef RASTERIZER_HH
#define RASTERIZER_HH

#include "math.hh"
#include "framebuffer.hh"
#include "shader.hh"
#include "triangle.hh"
#include "camera.hh"

namespace msr{

class rasterizer{

public:
    rasterizer(){}
    ~rasterizer(){}

    void drawPixel(float x, float y, const vec4& color,framebuffer& fb);
    void drawPixel(fragmentdata& fg,shader& sh,framebuffer& fb);

    void drawTriangleLine(triangle &tri, const vec4& color,framebuffer& fb);
    void drawTriangle(triangle &tri, const vec4& color,framebuffer& fb);
    void drawTriangle(triangle &tri,shader& sh,framebuffer& fb, camera& cam);
    
    void drawLine(int x1, int y1, int x2, int y2, const vec4& color,framebuffer& fb);


};

};


#endif 