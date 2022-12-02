#ifndef RASTERIZER_HH
#define RASTERIZER_HH

#define NOMINMAX

#include "include.hh"
#include "math.hh"
#include "framebuffer.hh"

namespace msr{

class rasterizer{

public:
    rasterizer(){}
    ~rasterizer(){}

    void drawPixel(int x, int y, const vec4& color,framebuffer& fb);
    void drawTriangle(vec2 v1, vec2 v2, vec2 v3, const vec4& color,framebuffer& fb);
    void drawTriangle_lineSweep(vec2 v1, vec2 v2, vec2 v3, const vec4& color,framebuffer& fb) ;
    void drawLine(int x1, int y1, int x2, int y2, const vec4& color,framebuffer& fb);

};

};


#endif 