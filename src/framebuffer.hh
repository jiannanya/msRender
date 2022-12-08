#ifndef FRAMEBUFFER_HH
#define FRAMEBUFFER_HH

#include "math.hh"
#include <minwindef.h>

namespace msr{

class framebuffer {
public:
    framebuffer(int width, int height);
    ~framebuffer();

    BYTE*& getColorBuffer();//需要返回引用用来创建windows窗口
    float *getZBuffer();
    float getZ(unsigned int x, unsigned int y);
    void setZ(unsigned int x, unsigned int y, float value);
    int getWidth()const;
    int getHeight()const;
    int getChannelNums()const;
    void clearColorBuffer(vec4 color);
    void setPixelColor(unsigned int x, unsigned int y, vec4 color);

private:
    int m_Width;
    int m_Height;
    int m_Channel;
    int m_PixelCount;
    BYTE* m_ColorBuffer;
//    BYTE *m_ColorBuffer1;
    float* m_ZBuffer;
};

};


#endif