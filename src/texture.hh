#ifndef TEXTURE_HH
#define TEXTURE_HH

#include<string>
#include<iostream>

#include "../vendor/std_image/stb_image.h"
#include "math.hh"

using std::string;

namespace msr{

class texture
{
public:
    unsigned char* data;
    int width, height, channelCnt;

    texture() {}
    texture(const string& path) { loadFile(path); }
     ~texture() { stbi_image_free(data); }

    void loadFile(const string& path);
    vec4 sample(vec2 uv);
private:

    vec4 getColor(int x, int y);

   
};

}

#endif