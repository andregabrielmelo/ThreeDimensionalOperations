#include <GL/freeglut.h>
#include "Application.h"

// Global pointer (needed for GLUT callbacks)
Application* app = nullptr;

void displayWrapper() {
    app->display();
}

void keyboardWrapper(unsigned char key, int x, int y) {
    app->keyboard(key);
}

void specialWrapper(int key, int x, int y) {
    app->keyboardSpecial(key);
}

void timerWrapper(int value) {
    app->update();
    glutTimerFunc(10, timerWrapper, 0);
}

void reshapeWrapper(int width, int height) {
    app->reshape(width, height);
}

int main(int argc, char** argv) {
    // Create application
    app = new Application();

    // GLUT setup
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cubo 3D OOP");

    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 1, 1, 500);

    glMatrixMode(GL_MODELVIEW);

    // Register callbacks
    glutDisplayFunc(displayWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutSpecialFunc(specialWrapper);
    glutTimerFunc(10, timerWrapper, 0);
    glutReshapeFunc(reshapeWrapper);

    // Start loop
    glutMainLoop();
    return 0;
}