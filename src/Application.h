#pragma once
#include "Object3D.h"

class Application 
{
private:
    Object3D cube;

public:
    Application();

    void display();
    void keyboard(unsigned char key);
    void keyboardSpecial(int key);
    void update(); // for timer/redraw
    void reshape(int width, int height);
};