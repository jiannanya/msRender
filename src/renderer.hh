#ifndef RENDERER_HH
#define RENDERER_HH

#include "include.hh"

#include <string>
#include <fstream>
#include <chrono>
#include "../vendor/std_image/stb_image_write.h"

#include "math.hh"
#include "windows.hh"
#include "context.hh"

namespace msr{

class renderer
{
public:

    explicit renderer(context &c);
    ~renderer(){}

    bool update();
    void render();

private:

    void input_poll_events(void);

    context m_Ctx;
    
    std::chrono::steady_clock::time_point m_CurTime;
    std::chrono::steady_clock::time_point m_PreTime;
    float m_DeltaTime;
    float m_Fps;
    int m_FrameCount;

    bool m_isInTouch;
    float m_distance = 2.0f;
    float m_pitch = 0.0f;
    float m_yaw = 0.0f;

    float m_ratio = 0.01;
    float m_temp;

    float m_touchX, m_touchY, m_preTouchX, m_preTouchY;

    
};

}

#endif