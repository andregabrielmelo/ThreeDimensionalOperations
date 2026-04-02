#include "Mesh.h"
#include "Transform.h"

class Object3D{
private:
    Mesh mesh;
    Transform transform;

public:
    Object3D(const Mesh& mesh) : mesh(mesh) {}

    void move(double x, double y, double z);
    void rotate(double x, double y, double z);
    void scale(double x, double y, double z);

    void draw() const;
};