#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int num = 0;

void q1();
void q2();
void q3();
void q4();

//q1()'s action
float v1X = -0.2f;
float v1Y = 0.2f;
float v2X = -0.2f;
float v2Y = -0.2f;
float v3X = 0.2f;
float v3Y = -0.2f;
float v4X = 0.2f;
float v4Y = 0.2f;

//for translatef
float posMove = 0.05f;
float negMove = -0.05f;

char action;
void shape();
void shapePosition();
void q1Left(); //L
void q1Right(); //R
void q1Up(); //U
void q1Down(); //D
void q1R(); //r
void q1G(); //g
void q1B(); //b
void q1Space(); //S

//Q2
float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;
boolean outerAscending = true;
float innerRed = 1.0f;
float innerGreen = 1.0f;
float innerBlue = 1.0f;
boolean innerAscending = false;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31 || wParam == VK_NUMPAD1) {
			glPopMatrix();
			num = 1;
			glPushMatrix();
		}
		else if (wParam == 0x32 || wParam == VK_NUMPAD2) {
			glPopMatrix();
			num = 2;
			glPushMatrix();
		}
		else if (wParam == 0x33 || wParam == VK_NUMPAD3) {
			glPopMatrix();
			num = 3;
			glPushMatrix();
		}
		else if (wParam == 0x34 || wParam == VK_NUMPAD4) {
			glPopMatrix();
			num = 4;
			glPushMatrix();
		}
		else if (wParam == VK_LEFT) {
			action = 'L';
		}
		else if (wParam == VK_RIGHT) {
			action = 'R';
		}
		else if (wParam == VK_UP) {
			action = 'U';
		}
		else if (wParam == VK_DOWN) {
			action = 'D';
		}
		else if (wParam == 0x52) {
			action = 'r';
		}
		else if (wParam == 0x47) {
			action = 'g';
		}
		else if (wParam == 0x42) {
			action = 'b';
		}
		else if (wParam == 0x20) {
			action = 'S';
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
	glClear(GL_COLOR_BUFFER_BIT);

	switch (num) {
	case 1:
		q1();
		break;
	case 2:
		q2();
		break;
	case 3:
		q3();
		break;
	case 4:
		q4();
		break;
	default:
		q1();
		break;

	}
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void q1() {
	glLoadIdentity();
	
	switch (action) {
		case 'L':
			q1Left();
			break;
		case 'R':
			q1Right();
			break;
		case 'U':
			q1Up();
			break;
		case 'D':
			q1Down();
			break;
		case 'r':
			q1R();
			break;
		case 'g':
			q1G();
			break;
		case 'b':
			q1B();
			break;
		case 'S':
			q1Space();
			break;
		default:
			break;
	}

	shape();
	shapePosition();
	action = 'n';
}
void shape() {

	glBegin(GL_QUADS);
	glVertex2f(v1X, v1Y);
	glVertex2f(v2X, v2Y);
	glVertex2f(v3X, v3Y);
	glVertex2f(v4X, v4Y);
	glEnd();
}
void shapePosition() {
	switch (action) {
	case 'L':
		v1X += negMove;
		v2X += negMove;
		v3X += negMove;
		v4X += negMove;
		break;
	case 'R':
		v1X += posMove;
		v2X += posMove;
		v3X += posMove;
		v4X += posMove;
		break;
	case 'U':
		v1Y += posMove;
		v2Y += posMove;
		v3Y += posMove;
		v4Y += posMove;
		break;
	case 'D':
		v1Y += negMove;
		v2Y += negMove;
		v3Y += negMove;
		v4Y += negMove;
		break;
	}
}
void q1Left() {
	glTranslatef(negMove, 0.0, 0.0);
}
void q1Right() {
	glTranslatef(posMove, 0.0, 0.0);
}
void q1Up() {
	glTranslatef(0.0, posMove, 0.0);
}
void q1Down() {
	glTranslatef(0.0, negMove, 0.0);
}
void q1R() {
	glColor3d(1.0, 0.0, 0.0);
}
void q1G() {
	glColor3d(0.0, 1.0, 0.0);
}
void q1B() {
	glColor3d(0.0, 0.0, 1.0);
}
void q1Space() {
	glColor3d(1.0, 1.0, 1.0);
	v1X = -0.2f;
	v1Y = 0.2f;
	v2X = -0.2f;
	v2Y = -0.2f;
	v3X = 0.2f;
	v3Y = -0.2f;
	v4X = 0.2f;
	v4Y = 0.2f;
}

void q2() {
	glRotatef(0.1, 0.0, 0.0, 1.0);

	//up
	glBegin(GL_TRIANGLES);
	glColor3d(red, innerGreen, innerBlue);
	glVertex2f(0.0, 0.5);

	glColor3d(innerRed, green, innerBlue);
	glVertex2f(-0.2, 0.2);
	glVertex2f(0.2, 0.2);
	glEnd();

	//left
	glBegin(GL_TRIANGLES);
	glColor3d(red, innerGreen, innerBlue);
	glVertex2f(-0.6, 0.1);

	glColor3d(innerRed, green, innerBlue);
	glVertex2f(-0.3, -0.1);
	glVertex2f(-0.2, 0.2);
	glEnd();

	//bottom left
	glBegin(GL_TRIANGLES);
	glColor3d(innerRed, green, innerBlue);
	glVertex2f(-0.3, -0.1);

	glColor3d(red, innerGreen, innerBlue);
	glVertex2f(-0.4, -0.5);

	glColor3d(innerRed, green, innerBlue);
	glVertex2f(0.0, -0.3);
	glEnd();

	//bottom right
	glBegin(GL_TRIANGLES);
	glColor3d(innerRed, green, innerBlue);
	glVertex2f(0.0, -0.3);

	glColor3d(red, innerGreen, innerBlue);
	glVertex2f(0.4, -0.5);

	glColor3d(innerRed, green, innerBlue);
	glVertex2f(0.3, -0.1);
	glEnd();

	//right
	glBegin(GL_TRIANGLES);
	glColor3d(innerRed, green, innerBlue);
	glVertex2f(0.2, 0.2);
	glVertex2f(0.3, -0.1);

	glColor3d(red, innerGreen, innerBlue);
	glVertex2f(0.6, 0.1);
	glEnd();

	glColor3d(innerRed, green, blue);
	//middle left
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.3, -0.1);
	glVertex2f(0.0, -0.3);
	glEnd();

	//middle
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, 0.2);
	glVertex2f(0.0, -0.3);
	glVertex2f(0.2, 0.2);
	glEnd();

	//middle right
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, -0.3);
	glVertex2f(0.3, -0.1);
	glVertex2f(0.2, 0.2);
	glEnd();

	//ascending
	if (red != 0.8f && outerAscending && !innerAscending) {
		red += 0.01f;
		innerRed -= 0.01f;
	}

	if (red >= 0.8f && innerRed <= 0.2f && green != 0.8f && innerGreen != 0.2f && outerAscending && !innerAscending) {
		green += 0.01f;
		innerGreen -= 0.01f;
	}

	if (green >= 0.8f && innerGreen <= 0.2f && blue != 0.8f && innerBlue != 0.2f && outerAscending && !innerAscending) {
		blue += 0.01f;
		innerBlue -= 0.01f;

		if (blue >= 0.8f) {
			outerAscending = false;
			innerAscending = true;
		}
	}

	//descending
	if (red != 0.2f && innerRed != 0.8f && !outerAscending && innerAscending) {
		red -= 0.01f;
		innerRed += 0.01f;
	}

	if (red <= 0.2f && innerRed >= 0.8f && green != 0.2f && innerGreen != 0.8f && !outerAscending && innerAscending) {
		green -= 0.01f;
		innerGreen += 0.01f;
	}

	if (green <= 0.2f && innerGreen >= 0.8f && blue != 0.2f && innerBlue != 0.8f && !outerAscending && innerAscending) {
		blue -= 0.01f;
		innerBlue += 0.01f;

		if (blue <= 0.2f) {
			outerAscending = true;
			innerAscending = false;
		}
	}
	
}

void q3() {
	glColor3d(1.0, 0.0, 0.0);
	glPointSize(10);
	glRotatef(1.5, 0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2f(-0.5, -0.5);
	glEnd();
}

void q4() {
	glColor3d(1.0, 0.0, 0.0);
	glScalef(1.2, 1.2, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.2, -0.2);
	glVertex2f(0.2, -0.2);
	glVertex2f(0.2, 0.2);
	glEnd();
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
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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