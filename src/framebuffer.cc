
#include "framebuffer.hh"
#include "include.hh"
#include <windows.h>

namespace msr{

framebuffer::framebuffer(int width, int height){
    m_Width = width;
    m_Height = height;
    m_Channel = 4; //RGBA
    m_PixelCount = width * height;

    m_ColorBuffer = new BYTE[m_PixelCount*m_Channel];
    memset(m_ColorBuffer,0,m_PixelCount*m_Channel);

    m_ZBuffer = new float[m_PixelCount];
    memset(m_ZBuffer,0,m_PixelCount);
  

};

framebuffer::~framebuffer() {
    // if (m_ColorBuffer1) delete m_ColorBuffer1;
    // m_ColorBuffer1 = nullptr;

    // if (m_ColorBuffer2) delete m_ColorBuffer2;
    // m_ColorBuffer2 = nullptr;

    // m_ColorBuffer = nullptr;

    // if(m_ZBuffer)delete m_ZBuffer;
    // m_ZBuffer = nullptr;
};


BYTE*& framebuffer::getColorBuffer() {
    return m_ColorBuffer;
};

float *framebuffer::getZBuffer(){
    return m_ZBuffer;
}

float framebuffer::getZ(unsigned int x, unsigned int y){
    UINT index = y * m_Width + x;
    return m_ZBuffer[index];
}

void framebuffer::setZ(unsigned int x, unsigned int y, float value){
    UINT index = y * m_Width + x;
    m_ZBuffer[index] = value;
}

int framebuffer::getChannelNums()const{
    return m_Channel;
}


void framebuffer::clearColorBuffer(vec4 color) {
    //std::cerr<<"clearColorBuffer: "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;
    UINT index_limit = m_PixelCount * m_Channel;
    for(UINT index=0;index<index_limit;index+=m_Channel){
        m_ColorBuffer[index+0] = static_cast<BYTE>(color.x * 255);
        m_ColorBuffer[index+1] = static_cast<BYTE>(color.y * 255);
        m_ColorBuffer[index+2] = static_cast<BYTE>(color.z * 255);
        m_ColorBuffer[index+3] = static_cast<BYTE>(color.w * 255);
    }
    
};

void framebuffer::clearZBuffer(){
    for (int i=m_PixelCount; i--; m_ZBuffer[i] = -(std::numeric_limits<float>::max)());
}


int framebuffer::getWidth()const {
    return m_Width;
};


int framebuffer::getHeight()const {
    return m_Height;
};


void framebuffer::setPixelColor(unsigned int x, unsigned int y, vec4 color) {
    if(x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;

    //std::cerr<<"set pixel color: "<<x<<", "<<y<<": "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;

    UINT index = y * m_Width * m_Channel + x * m_Channel;

    // BGRA for windows creation
    m_ColorBuffer[index + 0] = static_cast<BYTE>(color.z * 255);
    m_ColorBuffer[index + 1] = static_cast<BYTE>(color.y * 255);
    m_ColorBuffer[index + 2] = static_cast<BYTE>(color.x * 255);
    m_ColorBuffer[index + 3] = static_cast<BYTE>(color.w * 255);
}

};