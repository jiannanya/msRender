#ifndef RENDERER_HH
#define RENDERER_HH

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

    renderer(){};
    explicit renderer(context &c);
    ~renderer(){}

    bool update();
    void render();
    void save(const std::string& path);

private:

    void input_poll_events(void);

    context m_Ctx;


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