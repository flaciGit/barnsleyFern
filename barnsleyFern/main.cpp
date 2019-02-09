#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

GLint keyStates[256];
GLint winWidth = 500;
GLint winHeight = 500;

GLfloat x = (rand() / (RAND_MAX + 1.0));
GLfloat y = (rand() / (RAND_MAX + 1.0));

int numberOfPoints = 100000;

//ortho clipping planes
GLdouble orthoLeft = -6;
GLdouble orthoRight = 6;
GLdouble orthoBottom = -1;
GLdouble orthoTop = 11;

GLfloat zoomChange = 0.1;

void drawPoint() {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void nextPoint() {
	
	GLfloat nextX;
	GLfloat nextY;
	double r = (rand() / (RAND_MAX + 1.0));

	if (r < 0.01) {
		nextX = 0;
		nextY = 0.16 * y;
	}
	else if (r < 0.86) {
		nextX = 0.85 * x + 0.04 * y;
		nextY = -0.04 * x + 0.85 * y + 1.6;
	}
	else if (r < 0.93) {
		nextX = 0.20 * x - 0.26 * y;
		nextY = 0.23 * x + 0.22 * y + 1.6;
	}
	else {
		nextX = -0.15 * x + 0.28 * y;
		nextY = 0.26 * x + 0.24 * y + 0.44;
	}
	x = nextX;
	y = nextY;

}

void drawBarnsleyFern() {

	for (int i = 0; i < numberOfPoints; i++) {
		drawPoint();
		nextPoint();
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(orthoLeft, orthoRight, orthoBottom, orthoTop);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	
	drawBarnsleyFern();

	glutSwapBuffers();
}

void update(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = 1;

	if (keyStates['+']) {

		orthoLeft -= zoomChange;
		orthoRight += zoomChange;
		orthoBottom -= zoomChange;
		orthoTop += zoomChange;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(orthoLeft, orthoRight, orthoBottom, orthoTop);

	}
	if (keyStates['-']) {
		orthoLeft += zoomChange;
		orthoRight -= zoomChange;
		orthoBottom += zoomChange;
		orthoTop -= zoomChange;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(orthoLeft, orthoRight, orthoBottom, orthoTop);
	}
}

void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = 0;
}

void keyOperations(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, keyOperations, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Barnsley fern");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, update, 0);

	glutTimerFunc(0, keyOperations, 0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutMainLoop();
	return 0;
}




