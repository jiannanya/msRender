#ifndef MESH_HH
#define MESH_HH

#include <vector>
#include "math.hh"

using std::vector;
using std::string;

namespace msr{

class mesh
{
public:
    vector<vec3> vertexs;
    vector<vec2> texcoords;
    vector<vec3> normals;

    vector<int> facet_vert;
    vector<int> facet_texcoord;
    vector<int> facet_norm;

    mesh(){}
    mesh(const string& filename);

    int faceNum() const;
    vec3 getVertex(const int i) const;
    vec3 getVertex(const int face_idx, const int offset) const;
    vec2 getTexcoord(const int face_idx, const int offset) const;
    vec3 getNormal(const int face_idx, const int offset) const;
};

};

#endif