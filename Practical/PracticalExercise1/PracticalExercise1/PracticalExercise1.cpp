#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 1"

float xPoint1 = 0, yPoint1 = 0, xPoint2 = 0, yPoint2 = 0;
float radius = 0.1;
float angle;

int questionNo = 0;

void pahangFlag();
void negeriSembilanFlag();
void englandFlag();
void scotlandFlag();
void japanFlag();

//smile face: Nintendo Kirby running below the sun and bird
void smileFace();
void face();
void leftHand();
void rightHand();
void leftLeg();
void rightLeg();
void pinkCircle(float x, float y);
void smile(float x, float y);
void eyeOut(float x, float y);
void eyeMiddle(float x, float y);
void eyeInner(float x, float y);
void sun();
void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void bird(float lineX1, float lineY1, float lineX2, float lineY2);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		//'0' and NumPad0 to go to show all flag
		if (wParam == 0X30 || wParam == VK_NUMPAD0) {
			questionNo = 0;
		}
		else if (wParam == 0X31 || wParam == VK_NUMPAD1) {
			questionNo = 1;
		}
		else if (wParam == 0X32 || wParam == VK_NUMPAD2) {
			questionNo = 2;
		}
		else if (wParam == 0X33 || wParam == VK_NUMPAD3) {
			questionNo = 3;
		}
		else if (wParam == 0X34 || wParam == VK_NUMPAD4) {
			questionNo = 4;
		}
		else if (wParam == 0X35 || wParam == VK_NUMPAD5) {
			questionNo = 5;
		}
		else if (wParam == 0X36 || wParam == VK_NUMPAD6) {
			questionNo = 6;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;	//8 bits = 1 byte
	pfd.cColorBits = 32; //32 bits color
	pfd.cDepthBits = 24; // 24 bits depth
	pfd.cStencilBits = 0; //0 bits shadow

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

void display() {
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	//Practical 1 exercise
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	switch (questionNo) {
	case 1:
		//Pahang Flag
		pahangFlag();
		break;

	case 2:
		//Negeri Sembilan Flag
		negeriSembilanFlag();
		break;

	case 3:
		//England Falg
		englandFlag();
		break;

	case 4:
		//Scotland Flag
		scotlandFlag();
		break;

	case 5:
		//Japan Flag
		japanFlag();
		break;

	case 6:
		//Smile Face
		smileFace();
		break;

	default:
		//q1 - q5 (smile face do bigger) press '6' or numPad6
		pahangFlag();
		negeriSembilanFlag();
		englandFlag();
		scotlandFlag();
		japanFlag();
	}


	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

void pahangFlag() {

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-1.0f, 0.5f);
	glVertex2f(-1.0f, 0.375f);
	glVertex2f(-0.5f, 0.375f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, 0.375f);
	glVertex2f(-1.0f, 0.25f);
	glVertex2f(-0.5f, 0.25f);
	glVertex2f(-0.5f, 0.375f);
	glEnd();
}

void negeriSembilanFlag() {


	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-0.25f, 0.5f);
	glVertex2f(-0.25f, 0.25f);
	glVertex2f(0.25f, 0.25f);
	glVertex2f(0.25f, 0.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.25f, 0.5f);
	glVertex2f(0.0f, 0.375f);
	glVertex2f(0.0f, 0.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.25f, 0.5f);
	glVertex2f(-0.25f, 0.375f);
	glVertex2f(0.0f, 0.375f);
	glEnd();
}

void englandFlag() {
	//top left (white)
	glBegin(GL_QUADS);
	glColor3f(0.65f, 0.65f, 0.65f); //dark grey
	glVertex2f(0.5f, 0.5f);

	glColor3f(0.85f, 0.85f, 0.85f); //little grey
	glVertex2f(0.5f, 0.4f);

	glColor3f(1.0f, 1.0f, 1.0f); //white
	glVertex2f(0.725f, 0.4f);

	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(0.725f, 0.5f);
	glEnd();

	//top right (white)
	glBegin(GL_QUADS);
	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(0.775f, 0.5f);
	glVertex2f(0.775f, 0.4f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(1.0f, 0.4f);

	glColor3f(0.65f, 0.65f, 0.65f);
	glVertex2f(1.0f, 0.5f);
	glEnd();

	//bottom left (white)
	glBegin(GL_QUADS);
	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(0.5f, 0.35f);

	glColor3f(0.65f, 0.65f, 0.65f);
	glVertex2f(0.5f, 0.25f);

	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(0.725f, 0.25f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.725f, 0.35f);
	glEnd();

	//bottom right (white)
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.775f, 0.35f);

	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(0.775f, 0.25f);

	glColor3f(0.65f, 0.65f, 0.65f);
	glVertex2f(1.0f, 0.25f);

	glColor3f(0.85f, 0.85f, 0.85f);
	glVertex2f(1.0f, 0.35f);
	glEnd();

	glColor3f(0.57f, 0.0f, 0.0f); //red

	//left banner (red)
	glBegin(GL_QUADS);
	glVertex2f(0.5f, 0.40f);
	glVertex2f(0.5f, 0.35f);
	glVertex2f(0.725f, 0.35f);
	glVertex2f(0.725f, 0.40f);
	glEnd();

	//down banner (red)
	glBegin(GL_QUADS);
	glVertex2f(0.725f, 0.35f);
	glVertex2f(0.725f, 0.25f);
	glVertex2f(0.775f, 0.25f);
	glVertex2f(0.775f, 0.35f);
	glEnd();

	//right banner (red)
	glBegin(GL_QUADS);
	glVertex2f(0.775f, 0.4f);
	glVertex2f(0.775f, 0.35f);
	glVertex2f(1.0f, 0.35f);
	glVertex2f(1.0f, 0.4f);
	glEnd();

	//up banner (red)
	glBegin(GL_QUADS);
	glVertex2f(0.725f, 0.5f);
	glVertex2f(0.725f, 0.4f);
	glVertex2f(0.775f, 0.4f);
	glVertex2f(0.775f, 0.5f);
	glEnd();

	//middle square (red)
	glBegin(GL_QUADS);
	glVertex2f(0.725f, 0.4f);
	glVertex2f(0.725f, 0.35f);
	glVertex2f(0.775f, 0.35f);
	glVertex2f(0.775f, 0.4f);
	glEnd();

}

void scotlandFlag() {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f); //white
	glVertex2f(-1.0f, -0.25f);
	glVertex2f(-1.0f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.5f, -0.25f);
	glEnd();

	glColor3f(0.0f, 0.4f, 0.74f); //blue

	//left
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0f, -0.3f);
	glVertex2f(-1.0f, -0.45f);
	glVertex2f(-0.80f, -0.375f);
	glEnd();

	//down
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.75f, -0.4f);
	glVertex2f(-0.95f, -0.5f);
	glVertex2f(-0.55f, -0.5f);
	glEnd();

	//right
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.7f, -0.375f);
	glVertex2f(-0.5f, -0.45f);
	glVertex2f(-0.5f, -0.3f);
	glEnd();

	//up
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.95f, -0.25f);
	glVertex2f(-0.75f, -0.35f);
	glVertex2f(-0.55f, -0.25f);
	glEnd();
}

void japanFlag() {

	xPoint1 = 0;
	yPoint1 = -0.375;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.25f, -0.25f);
	glVertex2f(-0.25f, -0.50f);
	glVertex2f(0.25f, -0.50f);
	glVertex2f(0.25f, -0.25f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPoint1, yPoint1);

	for (angle = 0; angle <= 360; angle += 0.1) {
		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);

		glVertex2f(xPoint2, yPoint2);
	}
	glEnd();
}

void smileFace() {
	//white background
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//make inner circle color
	glColor3f(242 / 255.0, 65 / 255.0, 207 / 255.0);
	leftHand();

	glColor3f(231 / 255.0, 6 / 255.0, 100 / 255.0);
	rightLeg();

	glColor3f(250 / 255.0, 161 / 255.0, 167 / 255.0);
	face();

	glColor3f(242 / 255.0, 65 / 255.0, 207 / 255.0);
	rightHand();

	glColor3f(231 / 255.0, 6 / 255.0, 100 / 255.0);
	leftLeg();

	pinkCircle(0.25, -0.05);
	pinkCircle(-0.25, -0.05);

	smile(0, -0.20);

	//right eye
	eyeOut(-0.20, 0.05);

	//left eye
	eyeOut(0.20, 0.05);

	sun();

	bird(0.5, 0.8, 0.8, 0.8);
	bird(0.25, 0.6, 0.55, 0.6);
	bird(-0.2, 0.75, 0.1, 0.75);
}

void face() {
	//face
	glBegin(GL_TRIANGLE_FAN);
	xPoint1 = 0;
	yPoint1 = 0;
	radius = 0.5;

	//Origin
	glVertex2f(xPoint1, yPoint1);

	glColor3f(246 / 255.0, 111 / 255.0, 151 / 255.0);
	for (float angle = 0; angle <= 360; angle += 1.0) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();
}

void leftHand() {
	//left hand
	glBegin(GL_TRIANGLE_FAN);
	xPoint1 = 0.40;
	yPoint1 = 0.25;
	radius = 0.2;

	//Origin
	glVertex2f(xPoint1, yPoint1);
	glColor3f(235 / 255.0, 4 / 255.0, 100 / 255.0);
	for (float angle = 0; angle <= 360; angle += 1.0) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}

	glEnd();
}

void rightHand() {
	//right hand
	glBegin(GL_TRIANGLE_FAN);
	xPoint1 = -0.60;
	yPoint1 = -0.10;
	radius = 0.2;

	//Origin
	glVertex2f(xPoint1, yPoint1);
	glColor3f(235 / 255.0, 4 / 255.0, 100 / 255.0);
	for (float angle = 0; angle <= 360; angle += 1.0) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}

	glEnd();
}

void leftLeg() {
	//left leg
	glBegin(GL_TRIANGLE_FAN);
	xPoint1 = 0.25;
	yPoint1 = -0.50;
	radius = 0.2;

	//Origin
	glVertex2f(xPoint1, yPoint1);
	glColor3f(235 / 255.0, 10 / 255.0, 20 / 255.0);
	for (float angle = 0; angle <= 360; angle += 1.0) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}

	glEnd();
}

void rightLeg() {
	//right leg
	glBegin(GL_TRIANGLE_FAN);
	xPoint1 = -0.20;
	yPoint1 = -0.35;
	radius = 0.2;

	//Origin
	glVertex2f(xPoint1, yPoint1);
	glColor3f(235 / 255.0, 10 / 255.0, 20 / 255.0);
	for (float angle = 0; angle <= 360; angle += 1.0) {
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}

	glEnd();
}

void pinkCircle(float x, float y) {
	xPoint1 = x;
	yPoint1 = y;
	radius = 0.05;

	glColor3f(235 / 255.0, 4 / 255.0, 100 / 255.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPoint1, yPoint1);

	for (angle = 0; angle <= 360; angle += 1.0) {

		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);

		glVertex2f(xPoint2 / 0.8, yPoint2);
	}
	glEnd();
}

void smile(float x, float y) {

	xPoint1 = x;
	yPoint1 = y;

	glColor3f(0 / 255.0, 0 / 255.0, 0 / 255.0);
	glLineWidth(1);
	radius = 0.1;

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= 6; angle += 0.0001) {

		if (angle >= 3.4) {
			glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
		}

	}
	glEnd();
}

void eyeOut(float x, float y) {
	xPoint1 = x;
	yPoint1 = y;

	radius = 0.05;

	glColor3f(4 / 255.0, 117 / 255.0, 194 / 255.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPoint1, yPoint1);

	for (angle = 0; angle <= 360; angle += 1.0) {

		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);

		glVertex2f(xPoint2 / 1.05, yPoint2 / 0.45);
	}
	glEnd();

	eyeMiddle(x, y + 0.025);
}

void eyeMiddle(float x, float y) {
	xPoint1 = x;
	yPoint1 = y;

	radius = 0.05;

	glColor3f(0 / 255.0, 0 / 255.0, 0 / 255.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPoint1, yPoint1);

	for (angle = 0; angle <= 360; angle += 1.0) {

		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);
		glVertex2f(xPoint2 / 1.05, yPoint2 / 0.56);
	}
	glEnd();

	eyeInner(x, y + 0.04);
}

void eyeInner(float x, float y) {
	xPoint1 = x;
	yPoint1 = y;

	radius = 0.05;

	glColor3f(255 / 255.0, 255 / 255.0, 255 / 255.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(xPoint1, yPoint1);

	for (angle = 0; angle <= 360; angle += 1.0) {

		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);
		glVertex2f(xPoint2 / 1.05, yPoint2 / 0.7);
	}
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
	xPoint1 = lineX1 + 0.025;
	yPoint1 = lineY1;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINES);

	for (angle = 0; angle <= 2; angle += 0.00001) {

		xPoint2 = xPoint1 + radius * cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);

		glVertex2f(xPoint2, yPoint2);
		//glVertex2f(xPoint2/1.5, yPoint2/0.95); eclipse
	}
	glEnd();

	//right wing
	xPoint1 = lineX2 - 0.025;
	yPoint1 = lineY2;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINES);

	for (angle = 0; angle <= 2; angle += 0.00001) {

		xPoint2 = xPoint1 + radius * -cos(angle);
		yPoint2 = yPoint1 + radius * sin(angle);

		glVertex2f(xPoint2, yPoint2);
		//glVertex2f(xPoint2/1.5, yPoint2/0.95); eclipse
	}
	glEnd();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;	//windows class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);	//windows class size
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure; //procedure for the windows class
	wc.lpszClassName = WINDOW_TITLE; //windows class name
	wc.style = CS_HREDRAW | CS_VREDRAW; //vertical or horizontal

	//Register the windows class
	if (!RegisterClassEx(&wc)) return false;

	/*Create the windows class (WS - windows style, CW - create windows, 800 - width, 600 - height,
	Null for the parent, Null for the menu, Null for the parameter)*/
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

		display();	//the display will keep refresh (complex code can put outside to prevent crash);

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------