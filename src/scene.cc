
#include "scene.hh"

namespace msr{

void scene::pushMesh(mesh* m){
    meshList.push_back(m);
}

auto scene::getMeshList(){
    return &meshList;
}

}