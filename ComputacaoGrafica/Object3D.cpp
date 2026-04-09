#include "Object3D.h"
#include <GL/freeglut.h>

void Object3D::move(double x, double y, double z) {
    transform.position.x += x;
    transform.position.y += y;
    transform.position.z += z;
}

void Object3D::scale(double x, double y, double z) {
    transform.scale.x *= x;
    transform.scale.y *= y;
    transform.scale.z *= z;
}

void Object3D::rotate(double x, double y, double z) {
    transform.rotation.x += x;
    transform.rotation.y += y;
    transform.rotation.z += z;
}

void Object3D::draw() const {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    for (auto& e : mesh.edges) {
        auto v1 = mesh.vertices[e.first];
        auto v2 = mesh.vertices[e.second];

        double x = v1.x, y = v1.y, z = v1.z;
        transform.apply(x, y, z);
        glVertex3f((float)x, (float)y, (float)z);

        x = v2.x; y = v2.y; z = v2.z;
        transform.apply(x, y, z);
        glVertex3f((float)x, (float)y, (float)z);
    }

    glEnd();
}