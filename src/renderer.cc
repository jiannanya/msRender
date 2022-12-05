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
        //std::cerr<<"update return false"<<"\n";
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
        //std::cerr<<"update return true"<<"\n";
        return true;
    }
    
}

void renderer::render(){
    m_PreTime = std::chrono::high_resolution_clock::now();

    // m_Ctx.draw();
    // save("out.png");

    while(update()){

        m_Ctx.draw();

        m_FrameCount++;

        if(m_FrameCount%100==0){
            m_CurTime = std::chrono::high_resolution_clock::now();
            m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurTime - m_PreTime).count();
            m_PreTime = m_CurTime;
            std::cerr<<"fps: "<< 100 * 1000 / m_DeltaTime <<" frame count: "<<m_FrameCount++<<"\r";
            
        }
    }

    
}

void renderer::save(const std::string& path) {

    auto fb = m_Ctx.getFrameBuffer();
    int width = fb->getWidth();
    int height = fb->getHeight();
    int channel = fb->getChannelNums();
    BYTE* frameBuffer = fb->getColorBuffer();

    unsigned char* f = frameBuffer;
    
    BYTE* data = new BYTE[width * height * channel];
    for(int i = 0; i < width * height; i++){
        data[i*channel + 0] = frameBuffer[i*channel + 0];
        data[i*channel + 1] = frameBuffer[i*channel + 1];
        data[i*channel + 2] = frameBuffer[i*channel + 2];
        data[i*channel + 3] = frameBuffer[i*channel + 3];
        //std::cerr<<i<<" save: "<< (float)data[i+0]<<", "<< (float)data[i+1]<<", "<< (float)data[i+2]<<", "<< (float)data[i+3]<<std::endl;
    }

    int ret = stbi_write_png(path.c_str(), width, height,channel, data,0);

    if (ret == 0) {
        std::cerr<<"fail to write image png: "<<path.c_str()<<std::endl;
        stbi_image_free(data);
        return;
    }

    stbi_image_free(data);
}

};
