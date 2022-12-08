#ifndef SCENE_HH
#define SCENE_HH

#include "mesh.hh"
#include <vector>

namespace msr{

class scene{
public:
    scene(){}
    void pushMesh(mesh* m);
    auto getMeshList();

private:

    std::vector<mesh*> meshList;



};

}


#endif