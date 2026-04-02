#pragma once
#include <vector>
#include "Vector3.h"

class Mesh 
{
public:
    std::vector<Vector3> vertices;
    std::vector<std::pair<int, int>> edges;

    static Mesh createCube(double size);
};