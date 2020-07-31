#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define WINDOW_TITLE "OpenGL Window"


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawSphereWithoutGLU() {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5f;
	int noOfSlice = 30, noOfStack = 30;

	for (sliceA = 0.0; sliceA < PI; sliceA += PI / noOfSlice) {
		
		glBegin(GL_TRIANGLE_STRIP);

		for (stackA = 0.0; stackA < 2.0 * PI; stackA += PI / noOfStack) {

			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA); 
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);

			x = radius * cos(stackA) * sin(sliceA + PI / noOfStack);
			y = radius * sin(stackA) * sin(sliceA + PI / noOfStack);
			z = radius * cos(sliceA + PI / noOfSlice);
			glVertex3f(x, y, z);
		}

		glEnd();
	}
}

void drawSphere() {
	const float PI = 3.141592f;
	GLfloat x, y, z, alpha, beta; // Storage for coordinates and angles        
	GLfloat radius = 0.5f;
	int gradation = 20;

	for (alpha = 0.0; alpha < PI; alpha += PI / gradation)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (beta = 0.0; beta < 2.01*PI; beta += PI / gradation)
		{
			x = radius * cos(beta)*sin(alpha);
			y = radius * sin(beta)*sin(alpha);
			z = radius * cos(alpha);
			glVertex3f(x, y, z);
			x = radius * cos(beta)*sin(alpha + PI / gradation);
			y = radius * sin(beta)*sin(alpha + PI / gradation);
			z = radius * cos(alpha + PI / gradation);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void myWireSphere(float r, int nParal, int nMerid) {
	float x, y, z, i, j;
	const float PI = 3.14159265359f;
	glColor3d(1.0, 0.0, 0.0);
	for (j = 0; j < PI; j += PI / (nParal + 1)) {
		glBegin(GL_LINE_STRIP);
		y = (float)(r*cos(j));
		for (i = 0; i < 2 * PI; i += PI / 60) {
			x = (float)(r*cos(i)*sin(j));
			z = (float)(r*sin(i)*sin(j));
			glVertex3f(x, y, z);
		}
		glEnd();
	}

	for (j = 0; j < PI; j += PI / nMerid) {
		glBegin(GL_LINE_STRIP);
		for (i = 0; i < 2 * PI; i += PI / 60) {
			x = (float)(r*sin(i)*cos(j));
			y = (float)(r*cos(i));
			z = (float)(r*sin(j)*sin(i));
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv, float r, float g, float b) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;

	for (sliceA = 0.0; sliceA < PI; sliceA += PI / noOfSlice) {

		glColor3d(r, g, b);
		glBegin(GL_TRIANGLE_STRIP);

		for (stackA = 0.0; stackA < 2.0 * PI; stackA += PI / noOfStack) {

			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x / xDiv, y / yDiv, z);

			x = radius * cos(stackA) * sin(sliceA + PI / noOfStack);
			y = radius * sin(stackA) * sin(sliceA + PI / noOfStack);
			z = radius * cos(sliceA + PI / noOfSlice);
			glVertex3f(x / xDiv, y / yDiv, z);
		}

		glEnd();
	}
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(0.01f, 0.0f, -0.5f, 0.0f);

	/*GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, 0.5f, 30, 30);
	gluDeleteQuadric(sphere);

	GLUquadricObj *cyliner = NULL;
	cyliner = gluNewQuadric();
	gluQuadricDrawStyle(cyliner, GLU_LINE);
	gluCylinder(cyliner, 0.5f, 0.0f, 0.5f, 30, 30);
	gluDeleteQuadric(cyliner);*/

	
	glColor3d(1.0f, 1.0f, 1.0f);
	drawSphereWithoutGLU();

	drawScope(0.175f, 30, 30, 1.0f, 2.1f, 0.0f, 0.0f, 0.0f);
	//drawSphere();
	//myWireSphere(0.5, 10, 10);
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------