#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float initialConeSpeed = 0.0f;
float coneSpeed = 0.1f;
float initialScope1Translate = 1.5f;
float scope1Translate = 0.0f;

float initialScope2Translate = 1.5f;
float scope2Translate = 0.0f;

float initialScope3Translate = 1.5f;
float scope3Translate = 0.0f;

float initialUmbrellaSpeed = 1.5f;
float umbrellaSpeed = 0.0f;

float initialChipsSpeed = 1.5f;
float chipsSpeed = 0.0f;

float initialChipsSideSpeed = 1.5f;
float chipsSideSpeed = 0.0f;

void drawIceCream();
void drawCone(float xPos, float yPos, float zPos);
void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv, float r, float g, float b);
void drawUmbrella(float transX, float transY, float transZ, float rotAngle, float rotX, float rotY, float rotZ, float r, float g, float b);
void drawTissue(float xPos, float yPos, float zPos);
void drawChips(float x, float y, float z, float transX, float transY, float transZ, float r, float g, float b);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31 ||wParam == VK_NUMPAD1){
			scope1Translate = 0.0008f;
		}
		else if (wParam == 0x32 || wParam == VK_NUMPAD2) {
			if (initialScope1Translate <= 1.2f) {
				scope2Translate = 0.0008f;
			}
			
		}
		else if (wParam == 0x33 || wParam == VK_NUMPAD3) {
			if (initialScope2Translate <= 1.3f) {
				scope3Translate = 0.0008f;
			}
		}
		else if (wParam == 0x55) {
			if (initialScope3Translate <= 1.0f) {
				umbrellaSpeed = 0.0008f;
				chipsSpeed = 0.001f;
				chipsSideSpeed = 0.001f;
			}
		}
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

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		drawIceCream();
	glPopMatrix();
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void drawIceCream() {
	glPushMatrix();

		//let the whole ice cream rotate
		glRotatef(initialConeSpeed, 0.0f, 0.5f, 0.0f);
		initialConeSpeed += coneSpeed;

		//draw umbrella
		drawUmbrella(0.0f, 0.50f, 0.0f, 90.0f, -0.5f, 0.0f, 0.0f, 244.0f / 255.0f, 244.0f / 255.0f, 0.0f / 255.0f);

		//draw chips
		glPushMatrix();
			drawChips(0.0f, 0.0f, 0.0f, 0.0f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);

			drawChips(0.0f, 0.0f, 0.0f, 0.1f, 0.35f, 0.0f, 1.0f, 0.0f, 0.0f);

			drawChips(0.0f, 0.0f, 0.0f, -0.1f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);
		glPopMatrix();

		//draw scope 3
		glPushMatrix();
			glTranslatef(0.0f, initialScope3Translate, 0.0f);

			if (initialScope3Translate >= 0.2f) {
				initialScope3Translate -= scope3Translate;
			}
			drawScope(0.175f, 30, 30, 1.0f, 1.1f, 238.0f / 255.0f, 233.0f / 255.0f, 213.0f / 255.0f);
		glPopMatrix();

		//draw scope 2
		glPushMatrix();
			glTranslatef(0.0f, initialScope2Translate, 0.0f);

			if (initialScope2Translate >= 0.1f) {
				initialScope2Translate -= scope2Translate;
			}
			drawScope(0.175f, 30, 30, 0.95f, 1.2f, 133.0f / 255.0f, 97.0f / 255.0f, 66.0f / 255.0f);
		glPopMatrix();

		//draw scope 1
		glPushMatrix();
			glTranslatef(0.0f, initialScope1Translate, 0.0f);

			if (initialScope1Translate >= 0.0f) {
				initialScope1Translate -= scope1Translate;
			}

			drawScope(0.175f, 30, 30, 0.9f, 1.3f, 253.0f / 255.0f, 218.0f / 255.0f, 210.0f / 255.0f);
		glPopMatrix();

		//draw cone
		drawCone(0.0f, -0.5f, 0.0f);

		//draw tissue
		drawTissue(0.0f, -0.5f, 0.0f);

	glPopMatrix();
}

void drawCone(float xPos, float yPos, float zPos) {
	glPushMatrix();
		//initial position of cone
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90.0f, -0.5f, 0.0f, 0.0f);

		//draw cone with FILL
		glColor3d(172.0f / 255.0f, 128.0f / 255.0f, 82.0f / 255.0f);
		GLUquadricObj *cone = NULL;
		cone = gluNewQuadric();
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluCylinder(cone, 0.0f, 0.2f, 0.5f, 30, 30);
		gluDeleteQuadric(cone);

		//draw cone with LINE
		glColor3d(146.0f / 255.0f, 71.0f / 255.0f, 8.0f / 255.0f);
		GLUquadricObj *coneLine = NULL;
		coneLine = gluNewQuadric();
		gluQuadricDrawStyle(coneLine, GLU_LINE);
		gluCylinder(coneLine, 0.0f, 0.2f, 0.5f, 15, 5);
		gluDeleteQuadric(coneLine);
	glPopMatrix();
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

void drawUmbrella(float transX, float transY, float transZ, float rotAngle, float rotX, float rotY, float rotZ, float r, float g, float b) {
	glPushMatrix();
		
		glTranslatef(transX, initialUmbrellaSpeed, transZ);

		if (initialUmbrellaSpeed >= transY) {
			initialUmbrellaSpeed -= umbrellaSpeed;
		}

		glRotatef(rotAngle, rotX, rotY, rotZ);

		glPushMatrix();
			glLineWidth(5);
			glColor3d(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -0.2f);
			glEnd();
			glLineWidth(1);
		glPopMatrix();

		glColor3d(r, g, b);
		GLUquadric *awning = NULL;
		awning = gluNewQuadric();
		gluQuadricDrawStyle(awning, GLU_FILL);
		gluCylinder(awning, 0.2f, 0.0f, 0.1f, 30, 20);
		gluDeleteQuadric(awning);

		glColor3d(r - 20.0f, g - 20.0f, b);
		GLUquadric *awningLine = NULL;
		awningLine = gluNewQuadric();
		gluQuadricDrawStyle(awningLine, GLU_LINE);
		gluCylinder(awningLine, 0.2f, 0.0f, 0.1f, 8, 5);
		gluDeleteQuadric(awningLine);

	glPopMatrix();
}

void drawTissue(float xPos, float yPos, float zPos) {
	glPushMatrix();
	//initial position of cone
	glTranslatef(xPos, yPos, zPos);
	glRotatef(90.0f, -0.5f, 0.0f, 0.0f);

	//draw cone with FILL
	glColor3d(1.0f, 1.0f, 1.0f);
	GLUquadricObj *cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluCylinder(cone, 0.0f, 0.125f, 0.3f, 30, 30);
	gluDeleteQuadric(cone);

	glPopMatrix();
}

void drawChips(float x, float y, float z, float transX, float transY, float transZ, float r, float g, float b) {
	glPushMatrix();
		glTranslatef(transX, initialChipsSpeed, transZ);

		if (initialChipsSpeed >= transY) {
			initialChipsSpeed -= chipsSpeed;
		}

		glPushMatrix();
			glPointSize(10);
			glColor3d(r, g, b);
			glBegin(GL_POINTS);
			glVertex3f(x, y, z);
			glEnd();
		glPopMatrix();

	glPopMatrix();
}

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