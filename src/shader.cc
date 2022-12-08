#include "shader.hh"

namespace msr{

void shader::setModel(mat4 m){
    model = m;
}

void shader::setView(mat4 v){
    view = v;
}

void shader::setPerspective(mat4 pe){
    persp = pe;
}

void shader::setDiffuseTexture(texture* tex){
    diffuseTex = tex;
}

void shader::pushLight(pointlight* pl){
    _lights.push_back(pl);
}

void shader::vert(vec3 inLocalPos, vec4& outWorldPos, vec4& outClipPos) {
    vec4 p(inLocalPos.x, inLocalPos.y, inLocalPos.z, 1.0); //齐次坐标
    outClipPos = persp * view * model * p;
    outWorldPos = model * p;
}

vec4 shader::frag_phong(fragmentdata& fg) {

    //目前不处理透明混合
    vec4 result_color = {0.f, 0.f, 0.f, 1.0f};

    vec4 texture_color = diffuseTex->sample(fg.uv);

    //环境光、漫反射和高光系数
    //kd = texture_color / 255.f;
    kd = {0.f, 0.f, 0.5f, 1.0f};
    ks = 0.7937;
    ka = 0.005f;
    amb_light_intensity = 10.f;



    // auto l1 = light{{20, 20, 20}, {500, 500, 500}};
    // auto l2 = light{{-20, 20, 0}, {500, 500, 500}};//灯光强度、位置

    // std::vector<light> lights = {l1, l2};
    // vec4 amb_light_intensity{10, 10, 10};//环境光强度
    // vec4 eye_pos{0, 0, 10};//眼睛观测位置

    float p = 150;

    vec3 point = fg.worldPos;//着色点坐标
    vec3 normal = fg.worldNor;//着色点法向量
    vec3 camPos = fg.worldCamPos;//相机观测位置
    vec3 amb, dif, spe, l, v,li;

    for (auto& light : _lights)
    {

        li = light->getpos() - point;
        l = normalized(li);
        v = normalized(normalized(camPos - point) + l);

        for(int k=0;k<3;k++){
            dif[k] = kd[k] * light->getintensity() / (li * li) * std::fmax(0, normal * l);
            spe[k] = ks * light->getintensity() / (li * li) * pow(std::fmax(0, normal * v), p);
            amb[k] = ka * amb_light_intensity;
            result_color[k] += (dif[k] + spe[k] + amb[k]);
        }

        
    }

    return result_color;
}

vec4 shader::frag_texture(fragmentdata& fg) {
    return diffuseTex->sample(fg.uv);
}

};