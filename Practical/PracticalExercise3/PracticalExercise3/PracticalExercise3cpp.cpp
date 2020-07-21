#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNum;

//Q1
void q1();
void rect1();
void rect2();
void rectDirection();

//Direction variable
char q1Direction;
float q1Speed = 0.0001f;
float x1 = 0.0;
float y01 = 0.0;
float x2 = 0.0;
float y2 = 0.0;

//Q2
//Circle
float xPoint1 = 0.0, yPoint1 = 0.0;
float radius = 0.1f;
float angle;

//Fan
float initialFanSpeed = 0.01;
float fanSpeed = 0.01;
//Bird
float initialBirdSpeed = 0.0001;
float birdSpeed = 0.0001;

void q2();
//Background
void land();
void mountain(float v1C1, float v1C2, float v1C3, float v2C1, float v2C2, float v2C3, float v3C1, float v3C2, float v3C3);
void sun();
void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void bird(float lineX1, float lineY1, float lineX2, float lineY2);

//Building
void windmillBuilding(float tx, float ty, float sx, float sy);
void building();
void doorWindow(float x, float y, float r, float innerColor1, float innerColor2, float innerColor3, float outerColor1, float outerColor2, float outerColor3);
void circle(float x, float y, float r, float outerColor1, float outerColor2, float outerColor3);
void circle(float x, float y, float r, float innerColor1, float innerColor2, float innerColor3, float outerColor1, float outerColor2, float outerColor3);
void fan(float angle, float line1x, float line1y, float line2x, float line3x, float vQ1x, float vQ1y, float vQ2x, float vQ2y, float vQ3x, float vQ3y, float vQ4x, float vQ4y);

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
			qNum = 1;
		}
		else if (wParam == VK_NUMPAD2 || wParam == 0x32) {
			qNum = 2;
		}
		else if (wParam == VK_LEFT) {
			q1Direction = 'L';
		}
		else if (wParam == VK_RIGHT) {
			q1Direction = 'R';
		}
		else if (wParam == VK_UP) {
			q1Direction = 'U';
		}
		else if (wParam == VK_DOWN) {
			q1Direction = 'D';
		}
		else if (wParam == VK_SPACE) {
			q1Direction = 'N';
			x1 = 0;
			x2 = 0;
			y01 = 0;
			y2 = 0;
			fanSpeed = 0.0;
			birdSpeed = 0.0;
		}
		else if (wParam == VK_OEM_PLUS || wParam == VK_ADD) {
			if (fanSpeed <= 0.5) {
				fanSpeed += 0.01f;
			}
			if (birdSpeed <= 0.001f) {
				birdSpeed += 0.0001f;
			}

		}
		else if (wParam == VK_OEM_MINUS || wParam == VK_SUBTRACT) {
			if (fanSpeed >= -0.5) {
				fanSpeed -= 0.01f;
			}
			if (birdSpeed >= -0.001f) {
				birdSpeed -= 0.0001f;
			}
		}
		else if (wParam == 0x52) {
			fanSpeed = 0.0f;
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

	//let the rect continuous move after press key
	rectDirection();

	switch (qNum) {
	case 1:
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glLoadIdentity();
		q1();
		break;
	case 2:
		glClearColor(135.0 / 255.0, 206.0 / 255.0, 250.0 / 255.0, 1.0);
		q1Direction = 'N';
		q2();
		break;
	default:
		glClearColor(135.0 / 255.0, 206.0 / 255.0, 250.0 / 255.0, 1.0);
		q2();
	}
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void q1() {
	rect1();
	rect2();
}

void rect1() {
	glPushMatrix();
	glTranslatef(x1, y01, 0.0);
	glColor3d(0.5, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.25, -0.25);
	glVertex2f(0.25, -0.25);
	glVertex2f(0.25, 0.25);
	glEnd();
	glPopMatrix();

}

void rect2() {
	glPushMatrix();
	glTranslatef(x2, y2, 0.0);
	glColor3d(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.25, 0.25);
	glVertex2f(-0.25, -0.25);
	glVertex2f(0.25, -0.25);
	glVertex2f(0.25, 0.25);
	glEnd();
	glPopMatrix();
}

void rectDirection() {
	switch (q1Direction) {
	case 'L':
		x1 -= q1Speed;
		x2 += q1Speed;
		break;
	case 'R':
		x1 += q1Speed;
		x2 -= q1Speed;
		break;
	case 'U':
		y01 += q1Speed;
		y2 -= q1Speed;
		break;
	case 'D':
		y01 -= q1Speed;
		y2 += q1Speed;
		break;
	default:
		x1 = 0;
		x2 = 0;
		y01 = 0;
		y2 = 0;
	}
}

void q2() {
	glPushMatrix();
		glLoadIdentity();
		mountain(248.0 / 255.0, 89.0 / 255.0, 21.0 / 255.0, 254.0 / 255.0, 211.0 / 255.0, 133.0 / 255.0, 255.0 / 255.0, 166.0 / 255.0, 0.0 / 255.0);
			glPushMatrix();
				glTranslatef(0.75, 0.0, 0.0);
				mountain(248.0 / 255.0, 89.0 / 255.0, 21.0 / 255.0, 254.0 / 255.0, 211.0 / 255.0, 133.0 / 255.0, 255.0 / 255.0, 166.0 / 255.0, 0.0 / 255.0);
			glPopMatrix();
		land();
		sun();
	glPopMatrix();

	//Bird Fly
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(initialBirdSpeed, 0.0, 0.0);
		bird(0.525, 0.8, 0.775, 0.8);
		bird(0.275, 0.6, 0.525, 0.6);
		bird(-0.175, 0.75, 0.075, 0.75);
	glPopMatrix();

	initialBirdSpeed += birdSpeed;

	if (initialBirdSpeed > 1.5) {
		initialBirdSpeed = birdSpeed;
	}
	if (initialBirdSpeed < -2.0) {
		initialBirdSpeed = birdSpeed;
	}

	windmillBuilding(-0.65, -0.15, 0.3, 0.3);
	windmillBuilding(0.0, -0.1, 0.4, 0.4);
	windmillBuilding(0.65, -0.15, 0.3, 0.3);

}

//background
void mountain(float v1C1, float v1C2, float v1C3, float v2C1, float v2C2, float v2C3, float v3C1, float v3C2, float v3C3) {
	glBegin(GL_TRIANGLES);
	glColor3d(v1C1, v1C2, v1C3);
	glVertex2f(-1.0, -0.65);

	glColor3d(v2C1, v2C2, v2C3);
	glVertex2f(0.25, -0.65);

	glColor3d(v3C1, v3C2, v3C3);
	glVertex2f(-0.35, 0.2);
	glEnd();
}

void land() {
	glColor3d(51.0 / 255.0, 180.0 / 255.0, 1.0 / 255.0);
	glBegin(GL_QUADS);
	glVertex2f(-1.7, -0.65);
	glVertex2f(-1.7, -1.5);
	glVertex2f(1.7, -1.5);
	glVertex2f(1.7, -0.65);
	glEnd();
}

void sun() {

	xPoint1 = -1.0;
	yPoint1 = 1.0;
	radius = 0.5;

	glColor3f(247 / 255.0, 211 / 255.0, 40 / 255.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		angle = i * 3.142 / 180;
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();

	sunTriangle(-0.95f, 0.475f, -0.80f, 0.50f, -0.85f, 0.30f);
	sunTriangle(-0.7f, 0.55f, -0.50f, 0.425f, -0.575f, 0.65f);
	sunTriangle(-0.475f, 0.85f, -0.525f, 0.70f, -0.275f, 0.725f);
	sunTriangle(-0.475f, 1.0f, -0.475f, 0.90f, -0.30f, 0.965f);
}

void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glColor3f(227 / 255.0, 143 / 255.0, 20 / 255.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glColor3f(247 / 255.0, 211 / 255.0, 40 / 255.0);
	glVertex2f(x3, y3);
	glEnd();
}

void bird(float lineX1, float lineY1, float lineX2, float lineY2) {
	glColor3f(0.0f, 0.0f, 0.0f);

	//left wing
	xPoint1 = lineX1;
	yPoint1 = lineY1;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= 2; angle += 0.01) {

		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));

	}
	glEnd();

	//right wing
	xPoint1 = lineX2;
	yPoint1 = lineY2;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= 2; angle += 0.001) {
		glVertex2f(xPoint1 + radius * -cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();
}

//building
void windmillBuilding(float tx, float ty, float sx, float sy) {

	//draw building, window, door
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(tx, ty, 0.0);
		glScalef(sx, sy, 1.0);

		building();

		//window
		doorWindow(0.0, -0.85, 0.30, 116.0 / 255.0, 117.0 / 255.0, 103.0 / 255.0, 104.0 / 255.0, 107.0 / 255.0, 90.0 / 255.0);

		//door
		doorWindow(0.0, -2.1, 0.35, 168.0 / 255.0, 129.0 / 255.0, 90.0 / 255.0, 117.0 / 255.0, 73.0 / 255.0, 29.0 / 255.0);
	glPopMatrix();

	//draw fan (rotation animation - fan)
	glPushMatrix();
		glTranslatef(tx, ty, 0.0);
			glRotatef(initialFanSpeed, 0.0, 0.0, 1.0);
		glTranslatef(-tx, -ty, 0.0);

		initialFanSpeed += fanSpeed;

		glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			glScalef(sx, sy, 1.0);
			fan(0.0, 0.0, 0.0, 0.5, 0.5, 0.2, 0.2, 0.3, 0.05, 0.6, 0.35, 0.5, 0.5);
			fan(90.0, 0.0, 0.0, 0.5, 0.5, 0.2, 0.2, 0.3, 0.05, 0.6, 0.35, 0.5, 0.5);
			fan(180.0, 0.0, 0.0, 0.5, 0.5, 0.2, 0.2, 0.3, 0.05, 0.6, 0.35, 0.5, 0.5);
			fan(270.0, 0.0, 0.0, 0.5, 0.5, 0.2, 0.2, 0.3, 0.05, 0.6, 0.35, 0.5, 0.5);
		glPopMatrix();
	glPopMatrix();

	//draw fan core
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(tx, ty, 0.0);
		glScalef(sx, sy, 1.0);
		circle(0.0, 0.0, 0.1, 217.0 / 255.0, 186.0 / 255.0, 162.0 / 255.0, 137.0 / 255.0, 99.0 / 255.0, 63.0 / 255.0);
	glPopMatrix();

}

void building() {
	//Roof
	glBegin(GL_TRIANGLES);
	glColor3d(255.0 / 255.0, 66.0 / 255.0, 91.0 / 255.0);
	glVertex2f(0.0, 0.4);

	glColor3d(145.0 / 255.0, 29.0 / 255.0, 42.0 / 255.0);
	glVertex2f(-0.6, -0.3);

	glColor3d(123.0 / 255.0, 0.0 / 255.0, 21.0 / 255.0);
	glVertex2f(0.6, -0.3);
	glEnd();

	//top-left 1
	glBegin(GL_TRIANGLES);
	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(-0.5, -0.3);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(-0.5, -1.2);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);
	glEnd();

	//top-left 2
	glBegin(GL_TRIANGLES);
	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(-0.5, -0.3);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.0, -0.3);
	glEnd();

	//bottom-left 1
	glBegin(GL_TRIANGLES);
	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(-0.5, -1.2);

	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(-0.5, -2.1);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);
	glEnd();

	//bottom-left 2
	glBegin(GL_TRIANGLES);
	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(-0.5, -2.1);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.0, -2.1);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);
	glEnd();

	//bottom-right 1
	glBegin(GL_TRIANGLES);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.0, -2.1);

	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(0.5, -2.1);
	glEnd();

	//bottom-right 2
	glBegin(GL_TRIANGLES);
	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);

	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(0.5, -2.1);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.5, -1.2);
	glEnd();

	//top-right 1
	glColor3d(1.0, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.0, -0.3);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);

	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(0.5, -0.3);
	glEnd();

	//top-right 2
	glColor3d(1.0, 0.5, 0.5);
	glBegin(GL_TRIANGLES);

	glColor3d(229.0 / 255.0, 230.0 / 255.0, 213.0 / 255.0);
	glVertex2f(0.0, -1.2);

	glColor3d(154.0 / 255.0, 159.0 / 255.0, 140.0 / 255.0);
	glVertex2f(0.5, -1.2);

	glColor3d(113.0 / 255.0, 118.0 / 255.0, 99.0 / 255.0);
	glVertex2f(0.5, -0.3);
	glEnd();

}

void doorWindow(float x, float y, float r, float innerColor1, float innerColor2, float innerColor3, float outerColor1, float outerColor2, float outerColor3) {
	xPoint1 = x;
	yPoint1 = y;
	radius = r;

	glBegin(GL_TRIANGLE_FAN);
	//origin
	glVertex2f(xPoint1, yPoint1);

	glColor3d(outerColor1, outerColor2, outerColor3);
	for (float angle = 0; angle < 3.1; angle += 0.1) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle) / 0.75);
	}
	glEnd();
}

void circle(float x, float y, float r, float outerColor1, float outerColor2, float outerColor3) {
	xPoint1 = x;
	yPoint1 = y;
	radius = r;

	glBegin(GL_TRIANGLE_FAN);
	//origin
	glVertex2f(xPoint1, yPoint1);

	glColor3d(outerColor1, outerColor2, outerColor3);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();
}

void circle(float x, float y, float r, float innerColor1, float innerColor2, float innerColor3, float outerColor1, float outerColor2, float outerColor3) {
	xPoint1 = x;
	yPoint1 = y;
	radius = r;

	glBegin(GL_TRIANGLE_FAN);
	//origin
	glColor3d(innerColor1, innerColor2, innerColor3);
	glVertex2f(xPoint1, yPoint1);

	glColor3d(outerColor1, outerColor2, outerColor3);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();
}

void fan(float angle, float line1x, float line1y, float line2x, float line3x, float vQ1x, float vQ1y, float vQ2x, float vQ2y, float vQ3x, float vQ3y, float vQ4x, float vQ4y) {

	//to allocate the fan origin position
	glRotatef(angle, 0.0, 0.0, 1.0);

	glColor3d(177.0 / 255.0, 121.0 / 255.0, 73.0 / 255.0);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(line1x, line1y);
		glVertex2f(line2x, line3x);
	glEnd();

	glColor3d(142.0 / 255.0, 99.0 / 255.0, 57.0 / 255.0);
	glBegin(GL_QUADS);
		glVertex2f(vQ1x, vQ1y);
		glVertex2f(vQ2x, vQ2y);
		glVertex2f(vQ3x, vQ3y);
		glVertex2f(vQ4x, vQ4y);
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