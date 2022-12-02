#include "renderer.hh"

namespace msr{

renderer::renderer(context &c){
    m_Ctx = c;

    m_FrameCount = 0;
    m_distance = 2.0f;
    m_pitch = 0.0f;
    m_yaw = 0.0f;
    m_ratio = 0.01;
}

void renderer::input_poll_events(void) {
    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

bool renderer::update(){
    input_poll_events();
    if(m_Ctx.getWindow()->shouldClose()){
        return false;
    }
    else{
        m_Ctx.getWindow()->updateOperateRecord();

        OperateRecord &operateRecord = *m_Ctx.getWindow()->getOperateRecord();

        if (m_isInTouch) {
            if (operateRecord.isLeftBtnDown) {
                m_pitch += (operateRecord.y - m_preTouchY) * m_ratio;
                m_yaw += -(operateRecord.x - m_preTouchX) * m_ratio;
                m_preTouchY = operateRecord.y;
                m_preTouchX = operateRecord.x;
            } else {
                m_isInTouch = false;
            }
        } else {
            if (operateRecord.isLeftBtnDown) {
                m_isInTouch = true;
                m_preTouchY = operateRecord.y;
                m_preTouchX = operateRecord.x;
            }
        }
        vec3 cameraPos;
        cameraPos.y = std::sin(m_pitch) * m_distance;
        m_temp = std::cos(m_pitch) * m_distance;
        cameraPos.x = std::sin(m_yaw) * m_temp;
        cameraPos.z = std::cos(m_yaw) * m_temp;

        m_Ctx.getCamera()->updatePosition(cameraPos);

        return true;
    }
    
}

void renderer::render(){
    m_PreTime = std::chrono::high_resolution_clock::now();

    while(update()){

        m_Ctx.draw();

        m_FrameCount++;

        if(m_FrameCount==100){
            m_CurTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurTime - m_PreTime).count();
            std::cerr<<"fps: "<< 100 * 1000 / m_DeltaTime <<"/r";
        }
    }

    
}

};
