#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

#pragma comment(lib, "winmm.lib")

int WinPosX = 10;
int WinPosY = 100;
int WinWidth = 512;
int WinHeight = 512;
char WinTitle[] = "OpenGLSimpleChart";
GLfloat lgtColor[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lgtPos[4] = { 0.0, 100.0, 0.0, 0.0 };

double t;
const double T = 1 / (2 * 3.14);

double ox = -0.8;
double oy = -0.8;
double wx = 1.6;
double wy = 1.6;

int datacount = 0;
const int DATALENGTH = 160;
double chartdata[DATALENGTH];
const double xscalef = 0.01;
const double yscalef = 0.1;

time_t starttime;


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

	starttime = timeGetTime();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WinWidth, WinHeight);
	glLoadIdentity();

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
	//線の数は点の数-1で描画
	//for (int count = 0; count < datacount; count++) {
	for (int count = 0; count < datacount-1; count++) {
		double x1;
		double y1;
		double x2;
		double y2;

		//if (count > DATALENGTH - 1) {
		if (count > DATALENGTH - 2) {
			break;
		}
		x1 = xscalef * (double)count;
		y1 = yscalef * chartdata[count];

		x2 = xscalef * (double)(count+1);
		y2 = yscalef * chartdata[count+1];
		/*
		glBegin(GL_POINTS);
		glVertex2f(x + ox, y + oy);
		glEnd();
		*/
		glBegin(GL_LINES);
		glVertex2f(x1 + ox, y1 + oy);
		glVertex2f(x2 + ox, y2 + oy);
		glEnd();

	}

	glutSwapBuffers();
}

void Idle() {
	glutPostRedisplay();
	t = (double)(timeGetTime() - starttime) / 1000;

	Sleep(30);

	printf("t = %f\n", t);
	//チャート用に配列をセットする。

	double value;

	value = (double)5 * (cos(t / T) + 1);

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

