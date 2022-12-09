
#include "scene.hh"

namespace msr{

void scene::addMesh(mesh* m){
    meshList.push_back(m);
}

auto scene::getMeshList(){
    return &meshList;
}

}