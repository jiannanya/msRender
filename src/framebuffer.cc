
#include "framebuffer.hh"
#include "include.hh"
#include <windows.h>

namespace msr{

framebuffer::framebuffer(int width, int height) {
    m_Width = width;
    m_Height = height;
    m_Channel = 4;

    int size = sizeof(float) * width * height;
    m_Size = size;

    m_ColorBuffer1 = (BYTE *)malloc(size* m_Channel);
    memset(m_ColorBuffer1, 0, size);

    m_ColorBuffer2 = (BYTE *)malloc(size* m_Channel);
    memset(m_ColorBuffer2, 0, size);

    m_ZBuffer = (float *)malloc(size);
    memset(m_ZBuffer, 0, size);    

    m_ColorBufferPtr = m_ColorBuffer1;
};

framebuffer::~framebuffer() {
    if (m_ColorBuffer1) free(m_ColorBuffer1);
    m_ColorBuffer1 = nullptr;

    if (m_ColorBuffer2) free(m_ColorBuffer2);
    m_ColorBuffer2 = nullptr;

    m_ColorBufferPtr = nullptr;

    if(m_ZBuffer)free(m_ZBuffer);
    m_ZBuffer = nullptr;
};


BYTE *framebuffer::getColorBuffer()const {
    return m_ColorBufferPtr;
};

float *framebuffer::getZBuffer(){
    return m_ZBuffer;
}

int framebuffer::getChannelNums()const{
    return m_Channel;
}

// void framebuffer::setColorBuffer(unsigned char *colorBuffer) {
//     clearColorBuffer();
//     m_ColorBuffer = colorBuffer;
// };

void framebuffer::clearColorBuffer(vec4 color) {
    std::cerr<<"clearColorBuffer: "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;
    UINT index_limit = m_Size * m_Channel;
    for(UINT index=0;index<index_limit;index+=m_Channel){
        m_ColorBufferPtr[index+0] = static_cast<BYTE>(color.x * 255);
        m_ColorBufferPtr[index+1] = static_cast<BYTE>(color.y * 255);
        m_ColorBufferPtr[index+2] = static_cast<BYTE>(color.z * 255);
        m_ColorBufferPtr[index+3] = static_cast<BYTE>(color.w * 255);
    }
    // m_ColorBufferPtr[100+0] = static_cast<BYTE>(1.0f * 255);
    // m_ColorBufferPtr[100+1] = static_cast<BYTE>(1.0f * 255);
    // m_ColorBufferPtr[100+2] = static_cast<BYTE>(1.0f * 255);
    // m_ColorBufferPtr[100+3] = static_cast<BYTE>(1.0f * 255);
    
};


int framebuffer::getWidth()const {
    return m_Width;
};


int framebuffer::getHeight()const {
    return m_Height;
};


// void framebuffer::cloneColorBufferTo(framebuffer *destFrameBuffer) {
//     int width = m_Width;
//     int height = m_Height;

//     unsigned char *curColorBuffer = m_ColorBuffer;
//     unsigned char *destColorBuffer = destFrameBuffer->getColorBuffer();

//     for (int r = 0; r < height; r++) {
//         for (int c = 0; c < width; c++) {
//             int flippedR = height - 1 - r;
//             int srcIndex = (r * width + c) * 4;
//             int dstIndex = (flippedR * width + c) * 4;
//             unsigned char *srcPixel = &curColorBuffer[srcIndex];
//             unsigned char *dstPixel = &destColorBuffer[dstIndex];
//             dstPixel[0] = srcPixel[2];  /* blue */
//             dstPixel[1] = srcPixel[1];  /* green */
//             dstPixel[2] = srcPixel[0];  /* red */
//         }
//     }
// };
void framebuffer::swapColorBuffer(){
    if(m_ColorBufferPtr && m_ColorBufferPtr==m_ColorBuffer1 && m_ColorBuffer2)m_ColorBufferPtr=m_ColorBuffer2;
    if(m_ColorBufferPtr && m_ColorBufferPtr==m_ColorBuffer2 && m_ColorBuffer1)m_ColorBufferPtr=m_ColorBuffer1;
}

void framebuffer::setPixelColor(unsigned int x, unsigned int y, vec4 color) {
    if(x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;

    //std::cerr<<"set pixel color: "<<x<<", "<<y<<": "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;
    // gamma correction.
    // unsigned char red = static_cast<unsigned char>(255*pow(color.x,1.0/2.2));
    // unsigned char green = static_cast<unsigned char>(255*pow(color.y,1.0/2.2));
    // unsigned char blue = static_cast<unsigned char>(255*pow(color.z,1.0/2.2));
    // unsigned char alpha = static_cast<unsigned char>(255*color.w);

    UINT index = y * m_Width * m_Channel + x * m_Channel;
    m_ColorBufferPtr[index + 0] = static_cast<BYTE>(color.x * 255);
    m_ColorBufferPtr[index + 1] = static_cast<BYTE>(color.y * 255);
    m_ColorBufferPtr[index + 2] = static_cast<BYTE>(color.z * 255);
    m_ColorBufferPtr[index + 3] = static_cast<BYTE>(color.w * 255);
}

};