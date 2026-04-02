#include "Mesh.h"

// Isso daqui ficou meio estranho
Mesh Mesh::createCube(double size) {
    Mesh m;
    double t = size / 2.0;

    m.vertices = {
        {-t,-t,-t},{t,-t,-t},{t,t,-t},{-t,t,-t},
        {-t,-t,t},{t,-t,t},{t,t,t},{-t,t,t}
    };

    m.edges = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    return m;
}