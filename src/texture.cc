#include "texture.hh"

namespace msr{

void texture::loadFile(const string& path) {
    data = stbi_load(path.c_str(), &width, &height, &channelCnt, 0);

    if(!data)
    {
        std::cerr << "Texture load failed at path: " << path << std::endl;
    }else{
        std::cout << "lod texture: "<< path <<", channel count: "<<channelCnt<<std::endl;
    }
}

vec4 texture::sample(vec2 uv) {
    uv.x = frac(uv.x);
    uv.y = frac(uv.y);

    int x = clamp(int(width * (1.0f-uv.x)), 0, width - 1);
    int y = clamp(int(height * (1.0f-uv.y)), 0, height - 1);

    return getColor(x, y);
}

vec4 texture::getColor(float x, float y) {
    vec4 ret = {0.f,0.f,0.f,1.f};
    if(!data || x < 0 || y < 0 || x >= width || y >= height)
        return ret;

    int idx = (y * height + x) * channelCnt;

    // Gray
    if(channelCnt == 1) {    
        ret[0] = (float)data[idx];
    }
    // Gray Alpha
    else if(channelCnt == 2) {
        ret[0] = (float)data[idx];
        ret[3] = (float)data[idx + 1];
    }
    // RGB
    else if(channelCnt == 3) {
        ret[0] = (float)data[idx];
        ret[1] = (float)data[idx + 1];
        ret[2] = (float)data[idx + 2];
    }
    // RGBA
    else if(channelCnt == 4) {
        ret[0] = (float)data[idx];
        ret[1] = (float)data[idx + 1];
        ret[2] = (float)data[idx + 2];
        ret[3] = (float)data[idx + 3];
    }

    for(int i=0;i<channelCnt;i++){
        ret[i] = ret[i] / 255;
    }

    return ret;
}

};