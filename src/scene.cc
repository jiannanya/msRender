
#include "scene.hh"

namespace msr{

scene::scene(){
    meshList = std::vector<mesh*>();
}

void scene::addMesh(mesh* m){
    meshList.push_back(m);
}

std::vector<mesh*> scene::getMeshList(){
    return meshList;
}

}