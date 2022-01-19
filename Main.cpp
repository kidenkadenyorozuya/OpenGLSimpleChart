#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int WinPosX = 10;
int WinPosY = 100;
int WinWidth = 512;
int WinHeight = 512;
char WinTitle[] = "OpenGLSimpleChart";
GLfloat lgtColor[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lgtPos[4] = { 0.0, 100.0, 0.0, 0.0 };

double t;

double ox = -0.8;
double oy = -0.8;
double wx = 1.6;
double wy = 1.6;

int datacount = 0;
const int DATALENGTH = 160;
double chartdata[DATALENGTH];
const double xscalef = 0.01;
const double yscalef = 0.1;

void Initialize();
void Display();
void Idle();
void Shutdown();
void Reshape(int x, int y);
void Keyboard(unsigned char key, int x, int y);


///
///
///
void Initialize() {
	//
	glClearColor(0.0, 0.0, 0.0, 1.0);

	//
	glEnable(GL_DEPTH_TEST);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WinWidth, WinHeight);
	glLoadIdentity();

	for (int count = 0; count < 1000000; count++) {

	}

	glBegin(GL_LINES);

	//目盛り
	glVertex2f(ox, oy);
	glVertex2f(ox, oy + wy);

	glVertex2f(ox, oy);
	glVertex2f(ox + wx, oy);

	glEnd();

	//http://hooktail.org/computer/index.php?OpenGL%A4%F2%BB%C8%A4%C3%A4%C6%A4%DF%A4%E8%A4%A6
	glColor3f(0.2, 0.3, 0.5);
	glPointSize(3.0);
	for (int count = 0; count < datacount; count++) {
		double x;
		double y;

		if (count > DATALENGTH - 1) {
			break;
		}
		x = xscalef * (double)count;
		y = yscalef * chartdata[count];
		glBegin(GL_POINTS);
		glVertex2f(x + ox, y + oy);
		glEnd();

	}

	glutSwapBuffers();
}

void Idle() {
	glutPostRedisplay();
	t += 0.1;

	printf("t = %f\n", t);
	//チャート用に配列をセットする。

	double value;

	value = (double)5 * (cos(t / 10) + 1);

	//
	if (datacount >  DATALENGTH - 1) {
		for (int count = 0; count < DATALENGTH - 1; count++) {
			chartdata[count] = chartdata[count + 1];
		}
		chartdata[DATALENGTH - 1] = value;
	}
	else {
		chartdata[datacount] = value;
	}
	printf("%d\n", datacount);
	datacount++;
}

void Shutdown() {

}

void Reshape(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	}

}


///
///
///
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(WinPosX, WinPosY);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(WinTitle);
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);


	Initialize();

	glutMainLoop();

	Shutdown();

	return 0;


}

