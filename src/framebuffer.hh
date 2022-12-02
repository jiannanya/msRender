#ifndef FRAMEBUFFER_HH
#define FRAMEBUFFER_HH

#include "math.hh"
#include <minwindef.h>

namespace msr{

class framebuffer {
public:
    framebuffer(int width, int height);
    ~framebuffer();

    BYTE *getColorBuffer()const;
    float *getZBuffer();
    int getWidth()const;
    int getHeight()const;
    //void setColorBuffer(unsigned char *colorBuffer);
    void clearColorBuffer(vec4 color);
    void swapColorBuffer();
    //void cloneColorBufferTo(framebuffer *destFrameBuffer);
    void setPixelColor(unsigned int x, unsigned int y, vec4 color);

private:
    int m_Width;
    int m_Height;
    int m_Channel;
    int m_Size;
    BYTE *m_ColorBufferPtr;
    BYTE *m_ColorBuffer1;
    BYTE *m_ColorBuffer2; //双重缓存
    float* m_ZBuffer;
};

};


#endif