#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <tuple>

using vertice = std::tuple<double, double, double>;
using listaVertices = std::vector<vertice>;
using aresta = std::pair<int, int>;
using listaArestas = std::vector<aresta>;

struct Poligono {
	vertice posicao;
	vertice escala;
	vertice rotacao;
	listaVertices vertices;
	listaArestas arestas;
};

Poligono criarCubo(double tamanho);
void desenhar(Poligono poligono);
void movimentar(Poligono& poligono, double distanceX, double distanceY, double distanceZ);
void escalar(Poligono& poligono, double scaleX, double scaleY, double scaleZ);
void rotacionar(Poligono& poligono, double angleX, double angleY, double angleZ);
void display();
void redraw(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);

Poligono cubo;
int delay = 10;

int main(int argc, char** argv) {
	cubo = criarCubo(50);

	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Cubo 3D Wireframe");

	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, 1, 1, 500);

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutTimerFunc(10, redraw, 0);

	glutMainLoop();
	return 0;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(100, 100, 100, 0, 0, 0, 0, 1, 0);

	desenhar(cubo);

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0);

	case 'w': movimentar(cubo, 0, 5, 0); break;
	case 's': movimentar(cubo, 0, -5, 0); break;
	case 'a': movimentar(cubo, -5, 0, 0); break;
	case 'd': movimentar(cubo, 5, 0, 0); break;

	case 'q': movimentar(cubo, 0, 0, 5); break;
	case 'e': movimentar(cubo, 0, 0, -5); break;

	case '+': escalar(cubo, 1.1, 1.1, 1.1); break;
	case '-': escalar(cubo, 0.9, 0.9, 0.9); break;

	case 'x': rotacionar(cubo, 0.1, 0, 0); break;
	case 'y': rotacionar(cubo, 0, 0.1, 0); break;
	case 'z': rotacionar(cubo, 0, 0, 0.1); break;
	}
}

void keyboardSpecial(int key, int x, int y) {
	double step = 10;

	switch (key) {
	case GLUT_KEY_UP:
		movimentar(cubo, 0, step, 0);   // +Y
		break;

	case GLUT_KEY_DOWN:
		movimentar(cubo, 0, -step, 0);  // -Y
		break;

	case GLUT_KEY_RIGHT:
		movimentar(cubo, step, 0, 0);   // +X
		break;

	case GLUT_KEY_LEFT:
		movimentar(cubo, -step, 0, 0);  // -X
		break;
	}
}

void redraw(int value) {
	glutPostRedisplay();
	glutTimerFunc(delay, redraw, 0);
}

void movimentar(Poligono& poligono, double distanceX, double distanceY, double distanceZ) {
	std::get<0>(poligono.posicao) += distanceX;
	std::get<1>(poligono.posicao) += distanceY;
	std::get<2>(poligono.posicao) += distanceZ;
}

void escalar(Poligono& poligono, double scaleX, double scaleY, double scaleZ) {
	std::get<0>(poligono.escala) += scaleX;
	std::get<1>(poligono.escala) += scaleY;
	std::get<2>(poligono.escala) += scaleZ;
}

void rotacionar(Poligono& poligono, double angleX, double angleY, double angleZ) {
	std::get<0>(poligono.rotacao) += angleX;
	std::get<1>(poligono.rotacao) += angleY;
	std::get<2>(poligono.rotacao) += angleZ;
}

void aplicarTransformacoes(Poligono& p, double& x, double& y, double& z) {

	// escala
	x *= std::get<0>(p.escala);
	y *= std::get<1>(p.escala);
	z *= std::get<2>(p.escala);

	// rotação X
	double rx = std::get<0>(p.rotacao);
	double ry = std::get<1>(p.rotacao);
	double rz = std::get<2>(p.rotacao);

	double y1 = y * cos(rx) - z * sin(rx);
	double z1 = y * sin(rx) + z * cos(rx);
	y = y1; z = z1;

	// rotação Y
	double x1 = x * cos(ry) + z * sin(ry);
	z1 = -x * sin(ry) + z * cos(ry);
	x = x1; z = z1;

	// rotação Z
	x1 = x * cos(rz) - y * sin(rz);
	y1 = x * sin(rz) + y * cos(rz);
	x = x1; y = y1;

	// translação
	x += std::get<0>(p.posicao);
	y += std::get<1>(p.posicao);
	z += std::get<2>(p.posicao);
}


void desenhar(Poligono poligono) {
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	for (auto& a : poligono.arestas) {
		auto vertice1 = poligono.vertices[a.first];
		auto vetice2 = poligono.vertices[a.second];

		double x, y, z;

		x = std::get<0>(vertice1);
		y = std::get<1>(vertice1);
		z = std::get<2>(vertice1);
		aplicarTransformacoes(poligono, x, y, z);
		glVertex3f(x, y, z);

		x = std::get<0>(vetice2);
		y = std::get<1>(vetice2);
		z = std::get<2>(vetice2);
		aplicarTransformacoes(poligono, x, y, z);
		glVertex3f(x, y, z);
	}

	glEnd();
}

Poligono criarCubo(double tamanho) {
	Poligono p;

	double t = tamanho / 2.0;

	// 8 vértices do cubo
	p.vertices = {
		{-t, -t, -t}, {t, -t, -t},
		{t,  t, -t}, {-t,  t, -t},
		{-t, -t,  t}, {t, -t,  t},
		{t,  t,  t}, {-t,  t,  t}
	};

	// 12 arestas
	p.arestas = {
		{0,1},{1,2},{2,3},{3,0}, // base
		{4,5},{5,6},{6,7},{7,4}, // topo
		{0,4},{1,5},{2,6},{3,7}  // laterais
	};

	p.posicao = { 0,0,0 };
	p.escala = { 1,1,1 };
	p.rotacao = { 0,0,0 };

	return p;
}