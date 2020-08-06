#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//Projection
int projectionType = 0;

//Transition & Rotation
float initialBridgeRotate = 0.0f;
float bridgeRotate = 0.0f;
float bridgeZoom = 1.0f;

//shape
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ);
void drawSphere(float radius, int slices, int stacks);
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks);
void drawCircle(float xPoint, float yPoint, float radius);

void drawBridgeBuilding();

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_NUMPAD1 || wParam == 0x31) {
			//Orthographic
			projectionType = 1;
		}
		else if (wParam == VK_NUMPAD2 || wParam == 0x32) {
			//Perspective
			projectionType = 2;
		}
		else if (wParam == VK_UP) {
			bridgeZoom += 0.1f;
		}
		else if (wParam == VK_DOWN) {
			bridgeZoom -= 0.1f;
		}
		else if (wParam == VK_LEFT) {
			bridgeRotate = -0.01f;
		}
		else if (wParam == VK_RIGHT) {
			bridgeRotate = 0.01f;
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -5, 0, 5, 0);
	//Projection
	switch (projectionType) {
	case 1:
		glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
		break;
	case 2:
		gluPerspective(60.0f, 1.0f, -1.0f, 0.1f);
		glFrustum(-5.0f, 5.0f, -5.0f, 5.0f, bridgeZoom, 5.0f);
		break;
	default:
		glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
		//glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
		break;
	}

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(90.0f, 0.1f, 0.0f, 0.0f);
		initialBridgeRotate += bridgeRotate;

		drawBridgeBuilding();
	
	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

//shape
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
	//Back
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, maxY, minZ);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(minX, minY, maxZ);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Front
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
}
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ) {

	//face - back
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - top
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - bottom
	glBegin(GL_LINE_LOOP);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - front
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - base
	glBegin(GL_LINE_LOOP);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(minX, minY, minZ);
	glEnd();

}
void drawSphere(float radius, int slices, int stacks) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, radius, slices, stacks);

	gluDeleteQuadric(sphere);
}
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks) {
	
	glColor3d(111.0f / 255.0f, 102.0f / 255.0f, 94.0f / 255.0f);;
	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, baseRadius, topRadius, height, slices, stacks);

	gluDeleteQuadric(cylinder);

	//Upper cover (same rotation with cylinder)
	glColor3d(79.0f / 255.0f, 71.0f / 255.0f, 60.0f / 255.0f);;
	drawCircle(0.0f, 0.0f, 0.5f);

	//Lower cover (not same rotation with cylinder)
	glTranslatef(0.0f, 0.0f, 0.5f);
	drawCircle(0.0f, 0.0f, 0.5f);
}
void drawCircle(float xPoint, float yPoint, float radius) {
	
	glBegin(GL_TRIANGLE_FAN);
	//origin
	glVertex2f(xPoint, yPoint);

	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex2f(xPoint + radius * cos(angle), yPoint + radius * sin(angle));
	}
	glEnd();
}

void drawBridgeBuilding() {
	glPushMatrix();

		//draw base
		//cylinder
		glPushMatrix();
			glRotatef(90.0f, 0.5f, 0.0f, 0.0f);
			drawCylinder(0.5f, 0.5f, 0.5f, 30, 30);
		glPopMatrix();

		//building
		glBegin(GL_LINES);
			glColor3d(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.30f, 0.005f, -0.30f);
			glVertex3f(-0.30f, 0.005f, 0.30f);
		glEnd();

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