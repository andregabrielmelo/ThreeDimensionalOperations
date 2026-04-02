#pragma once
#include "Vector3.h"

class Transform 
{
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale = Vector3(1, 1, 1);

    void apply(double& x, double& y, double& z) const;
};
