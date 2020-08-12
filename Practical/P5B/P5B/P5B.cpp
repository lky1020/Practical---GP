#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//projection
int projectionType = 1;

float initialTransZ = 1.0f;
float transZ = 1.0f;
float initialRotate = 0.0f;
float rotate = 0.0f;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_UP) {
			initialTransZ += transZ;
		}
		else if (wParam == VK_DOWN) {
			initialTransZ -= transZ;
		}
		else if (wParam == VK_LEFT) {
			rotate = 0.01f;
		}
		else if (wParam == VK_RIGHT) {
			rotate = -0.01f;
		}
		else if (wParam == VK_SPACE) {
			initialTransZ = 1.0f;
			transZ = 1.0f;
			initialRotate = 0.0f;
			rotate = 0.0f;
		}
		else if (wParam == VK_NUMPAD1 || wParam == 0X31) {
			projectionType = 1;
		}
		else if (wParam == VK_NUMPAD2 || wParam == 0X32) {
			projectionType = 2;
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

void drawSphere(float radius, GLenum shapeType) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, shapeType);
	gluSphere(sphere, radius, 30, 30);

	gluDeleteQuadric(sphere); //delete the pointer inside the memory to avoid memory full
}
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type) {
	//Back
	glBegin(type);
	glVertex3f(minX, maxY, minZ);
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glEnd();

	//Bottom
	glBegin(type);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Left
	glBegin(type);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glEnd();

	//Top
	glBegin(type);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ);
	glEnd();

	//Right
	glBegin(type);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Front
	glBegin(type);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glEnd();
}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (projectionType) {
		case 1:
			//orthographic
			glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
			break;
		case 2:
			//Perspective
			gluPerspective(45.0f, 1.0f, -1.0f, 1.0f);
			glFrustum(-5.0f, 5.0f, -5.0f, 5.0f, 1.0f, 6.0f);
			break;
		default:
			break;
	}


	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		
		glTranslatef(0.0f, 0.0f, initialTransZ);

		glRotatef(initialRotate, 0.0f, 0.1f, 0.0f);
		initialRotate += rotate;

		//drawSphere(1.0f, GLU_POINT);
		glPushMatrix();
			glTranslatef(-2.0f, 0.0f, 0.0f);
			drawRectangle(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, GL_LINE_LOOP);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2.0f, 2.0f, 0.0f);
			drawRectangle(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, GL_LINE_LOOP);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0f, 0.0f, 0.0f);
			drawRectangle(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, GL_LINE_LOOP);
		glPopMatrix();


		glPushMatrix();
			glTranslatef(0.0f, -5.0f, 0.0f);
			glScalef(1.5f, 1.0f, 1.5f);
			drawSphere(4.0f, GLU_LINE);
		glPopMatrix();
	glPopMatrix();

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