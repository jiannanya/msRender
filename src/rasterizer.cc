#include "rasterizer.hh"
#include "triangle.hh"

namespace msr{

void rasterizer::drawPixel(int x, int y, const vec4& color,framebuffer& fb){
    fb.setPixelColor(x,y,color);
}

void rasterizer::drawPixel(fragmentdata& fg, shader& sh,framebuffer& fb){
    vec4 color = sh.frag_phong(fg);
    //std::cout<<"pixel: "<<fg.screenPos.x<<", "<<fg.screenPos.y<<", "<<"pixel color: "<<color.x<<", "<<color.y<<", "<<color.z<<std::endl;
    fb.setPixelColor(fg.screenPos.x,fg.screenPos.y,color);
}


void rasterizer::drawLine(int x1, int y1, int x2, int y2, const vec4& color,framebuffer& fb) {
    //std::cout << "drawLine :(" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;

    bool steep = false;
    // traverse by X or Y
    if(std::abs(x2 - x1) < std::abs(y2 - y1)){
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }

    // traverse from smaller value
    if(x2 < x1){
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    // float de = std::abs(dy / float(dx));
    // float e = 0;
    int de2 = std::abs(dy) * 2;
    int e2 = 0;
    int y = y1;
    for(int x = x1; x <= x2; ++x){
        (steep ? drawPixel(y, x, color,fb) : drawPixel(x, y, color,fb));
        // e += de;
        // if(e > 0.5f){
        //     y += (y2 > y1 ? 1 : -1);
        //     e -= 1.f;
        // }
        e2 += de2;
        if(e2 > dx){
            y += (y2 > y1 ? 1 : -1);
            e2 -= dx*2;
        }
    }
}


void rasterizer::drawTriangle(vec3 v1, vec3 v2, vec3 v3, const vec4& color,framebuffer& fb) {
    vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    vec2 bboxmax(0, 0);
    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){
            vec3 bc = barycentric(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) continue;

            drawPixel(p.x, p.y,color,fb);
        }
    }
}

void rasterizer::drawTriangle(triangle &tri,shader& sh,framebuffer& fb, camera& cam){

    vec3 v1 = tri.avp();
    vec3 v2 = tri.bvp();
    vec3 v3 = tri.cvp();

    vec3 vw1 = tri.aw();
    vec3 vw2 = tri.bw();
    vec3 vw3 = tri.cw();

    vec2 uv1 = tri.at();
    vec2 uv2 = tri.bt();
    vec2 uv3 = tri.ct();

    vec3 nw1 = tri.anw();
    vec3 nw2 = tri.bnw();
    vec3 nw3 = tri.cnw();

    vec4 c1 = tri.ac();
    vec4 c2 = tri.bc();
    vec4 c3 = tri.cc();


    vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    vec2 bboxmax(0, 0);
    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            vec3 bc = barycentric(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            //depth test
            p.z = v1.z*bc.x + v2.z*bc.y + v3.z*bc.z;
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);

            //interpolate

            vec3 vw;
            vw.x = vw1.x*bc.x + vw2.x*bc.y + vw3.x*bc.z;
            vw.y = vw1.y*bc.x + vw2.y*bc.y + vw3.y*bc.z;
            vw.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;

            vec2 uv;
            uv.x = uv1.x*bc.x + uv2.x*bc.y + uv3.x*bc.z;
            uv.y = uv1.y*bc.x + uv2.y*bc.y + uv3.y*bc.z;

            vec3 nw;
            nw.x = nw1.x*bc.x + nw2.x*bc.y + nw3.x*bc.z;
            nw.y = nw1.y*bc.x + nw2.y*bc.y + nw3.y*bc.z;
            nw.z = nw1.z*bc.x + nw2.z*bc.y + nw3.z*bc.z;

            vec4 c;
            c.x = c1.x*bc.x + c2.x*bc.y + c3.x*bc.z;
            c.y = c1.y*bc.x + c2.y*bc.y + c3.y*bc.z;
            c.z = c1.z*bc.x + c2.z*bc.y + c3.z*bc.z;
            c.z = c1.w*bc.x + c2.w*bc.y + c3.w*bc.z;

            fragmentdata fg = {p, vw, nw, cam.getPos(), c, uv};

            drawPixel(fg,sh,fb);
        }
    }
}

};