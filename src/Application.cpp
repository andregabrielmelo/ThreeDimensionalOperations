#include "Application.h"
#include "Mesh.h"
#include <cstdlib>
#include <GL/freeglut.h>

Application::Application()
    : cube(Mesh::createCube(50)) // initialize cube
{
}

void Application::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(100, 100, 100,   // camera position
        0, 0, 0,         // look at
        0, 1, 0);        // up vector

    cube.draw();

    glutSwapBuffers();
}

void Application::keyboard(unsigned char key) {
    switch (key) {
		// ESC key
        case 27: exit(0);

        case 'w': cube.move(0, 5, 0); break;
        case 's': cube.move(0, -5, 0); break;
        case 'a': cube.move(-5, 0, 0); break;
        case 'd': cube.move(5, 0, 0); break;

        case 'q': cube.move(0, 0, 5); break;
        case 'e': cube.move(0, 0, -5); break;

        case '+': cube.scale(1.1, 1.1, 1.1); break;
        case '-': cube.scale(0.9, 0.9, 0.9); break;

        case 'x': cube.rotate(0.1, 0, 0); break;
        case 'y': cube.rotate(0, 0.1, 0); break;
        case 'z': cube.rotate(0, 0, 0.1); break;
    }
}

void Application::keyboardSpecial(int key) {
    double step = 10;

    switch (key) {
        case GLUT_KEY_UP:    cube.move(0, step, 0); break;
        case GLUT_KEY_DOWN:  cube.move(0, -step, 0); break;
        case GLUT_KEY_RIGHT: cube.move(step, 0, 0); break;
        case GLUT_KEY_LEFT:  cube.move(-step, 0, 0); break;
    }
}

void Application::update() {
    glutPostRedisplay();
}

void Application::reshape(int width, int height) {
    if (height == 0) height = 1;

    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 1, 500);

    glMatrixMode(GL_MODELVIEW);
}