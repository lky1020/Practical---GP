#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int qNum;

//q1q2Q2
float initialPyramidSpeed = 0.0f;
float pyramidSpeed = 0.0f;
float x = 0.0f, y = 0.0f, z = 0.0f;
void q1q2();
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ);

//Q3
float initialArmRotate = 0.0f;
float armRotate = 0.0f;
float initialArmMove = 0.0f;
float armMove = 0.0f;
float initialFingerMove = 0.0f;
float fingerMove = 0.0f;
float initialThumbMove = 0.0f;
float thumbMove = 0.0f;
void q3();
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
void drawHand();
void adjustFingerMove(float translateX, float translateY, float translateZ, float rotateX, float rotateY, float rotateZ, float maxAngle, float minAngle);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_NUMPAD1 || wParam == 0x31 || wParam == VK_NUMPAD2 || wParam == 0x32) {
			qNum = 1;
		}
		else if (wParam == VK_NUMPAD3 || wParam == 0x33) {
			qNum = 3;
		}
		//'X'
		else if (wParam == 0x58) {
			x = 1.0f;
			y = 0.0f;
			z = 0.0f;
			pyramidSpeed = 0.01f;
		}
		//'Y'
		else if (wParam == 0x59) {
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
			pyramidSpeed = 0.01f;
		}
		//'Z'
		else if (wParam == 0x5A) {
			x = 0.0f;
			y = 0.0f;
			z = 1.0f;
			pyramidSpeed = 0.01f; 
		}
		else if (wParam == VK_SPACE) {
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;
			pyramidSpeed = 0.01f;
			initialArmRotate = 0.0f;
			armRotate = 0.0f;
			initialArmMove = 0.0f;
			armMove = 0.0f;
			initialFingerMove = 0.0f;
			fingerMove = 0.0f;
			initialThumbMove = 0.0f;
			thumbMove = 0.0f;
		}
		else if (wParam == VK_LEFT) {
			//AntiClockWise
			armRotate = 0.005f;
		}
		else if (wParam == VK_RIGHT) {
			//Clockwise
			armRotate = -0.005f;
		}
		else if (wParam == VK_UP) {
			//AntiClockWise
			armMove = 0.005f;

		}
		else if (wParam == VK_DOWN) {
			//Clockwise
			armMove = -0.005f;
		}
		//'S' - Stop pyramid move, arm move and rotate
		else if (wParam == 0x53) {
			initialPyramidSpeed = 0.0f;
			pyramidSpeed = 0.0f;
			armMove = 0.0f;
			armRotate = 0.0f;
			fingerMove = 0.0f;
			thumbMove = 0.0f;
		}
		//'C' - close hand
		else if (wParam == 0x43) {
			fingerMove = 0.005f;
			thumbMove = 0.02f;
		}
		//'O' - perform grab
		else if (wParam == 0x4F) {
			fingerMove = -0.005f;
			thumbMove = -0.02f;
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

void testing() {
	
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glTranslatef(-0.8f, 0.0f, 0.0f);
		glRotatef(initialPyramidSpeed, 0.0, 0.0, 1.0f);
		initialPyramidSpeed += pyramidSpeed;

		drawRectangle(0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f);
	glPopMatrix();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch (qNum) {
		case 1:
			q1q2();
			break;
		case 3:
			initialPyramidSpeed = 0.0f;
			pyramidSpeed = 0.0f;
			q3();
			break;
		default:
			q3();
			break;
	}
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

//q1q2
void q1q2() {
	glPushMatrix();
		glRotatef(initialPyramidSpeed, x, y, z);
		initialPyramidSpeed += pyramidSpeed;

		drawPyramid(0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 2.0f, 2.0f);
	glPopMatrix();
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

//Q3
void q3() {
	glPushMatrix();
	glLoadIdentity();
		glScalef(0.4, 0.4, 0.4);
		glTranslatef(-0.8f, 0.0f, 0.0f);
		//Left, Right to rotate
		glRotatef(initialArmRotate, 1.0f, 0.0f, -0.5f);
		initialArmRotate += armRotate;

		drawRectangle(-1.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f);

		glPushMatrix();
			//Up, Down to move arm up down
			glRotatef(initialArmMove, 0.0f, 0.0f, 0.1f);
			initialArmMove += armMove;

			if (initialArmMove >= 45.0f) {

				initialArmMove = 45.0f;
				armMove = 0.0f;

			}else if(initialArmMove <= 0.0f) {

				initialArmMove = 0.0f;
				armMove = 0.0f;

			}

			drawRectangle(0.0f, 1.5f, 0.0f, 0.5f, 0.0f, 0.5f);
			drawHand();
		glPopMatrix();

	glPopMatrix();
}

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

void drawHand() {
	//Palm
	drawRectangle(1.5f, 2.0f, -0.05f, 0.55f, 0.15f, 0.35f);
	glPushMatrix();
		//Thumb
		drawPyramid(1.5, 1.7f, 0.55f, 0.65f, 0.2f, 0.3f, 1.08f, 2.0f);

		glPushMatrix();
			//initial position of the thumb finger(inner, outer) - no animation
			glTranslatef(1.56f, 0.70f, 0.3f);
				glRotatef(42.0f, 0.0f, 0.0f, 0.5f);
			glTranslatef(-1.56f, -0.70f, -0.3f);

			//inner
			glTranslatef(1.56f, 0.65f, 0.3f);
			glRotatef(initialThumbMove, 0.0f, -0.5f, 0.0f);
			initialThumbMove += thumbMove;
			glTranslatef(-1.56f, -0.65f, -0.3f);

			if (initialThumbMove >= 45.0f) {

				initialThumbMove = 45.0f;
				thumbMove = 0.0f;

			}
			else if (initialThumbMove <= 0.0f) {

				initialThumbMove = 0.0f;
				thumbMove = 0.0f;

			}
			drawRectangle(1.56f, 1.76f, 0.50f, 0.65f, 0.2f, 0.3f);
		
			//outer
			adjustFingerMove(1.76f, 0.65f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
			drawRectangle(1.76f, 1.96, 0.50f, 0.65f, 0.2f, 0.3f);
		glPopMatrix();
	glPopMatrix();

	//Index Finger
	glPushMatrix();
		//inner
		drawRectangle(2.00f, 2.10f, 0.40f, 0.50f, 0.2f, 0.3f);

		//middle
		adjustFingerMove(2.10f, 0.50f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.10f, 2.25f, 0.40f, 0.50f, 0.2f, 0.3f);

		//outer
		adjustFingerMove(2.25f, 0.50f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.25f, 2.45f, 0.40f, 0.50f, 0.2f, 0.3f);
		
	glPopMatrix();
	
	//Middle Finger
	glPushMatrix();
		//inner
		drawRectangle(2.00f, 2.20f, 0.25f, 0.35f, 0.2f, 0.3f);

		//middle
		adjustFingerMove(2.20f, 0.35f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.20f, 2.35f, 0.25f, 0.35f, 0.2f, 0.3f);

		//outer
		adjustFingerMove(2.35f, 0.35f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.35f, 2.55f, 0.25f, 0.35f, 0.2f, 0.3f);
	glPopMatrix();

	//Ring Finger
	glPushMatrix();
		//inner
		drawRectangle(2.00f, 2.10f, 0.10f, 0.20f, 0.2f, 0.3f);

		//middle
		adjustFingerMove(2.10f, 0.20f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.10f, 2.25f, 0.10f, 0.20f, 0.2f, 0.3f);

		//outer
		adjustFingerMove(2.25f, 0.20f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.25f, 2.45f, 0.10f, 0.20f, 0.2f, 0.3f);
	glPopMatrix();

	//Little Finger
	glPushMatrix();
		//inner
		drawRectangle(2.00f, 2.10f, -0.05f, 0.05f, 0.2f, 0.3f);

		//middle
		adjustFingerMove(2.10f, 0.05f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.10f, 2.15f, -0.05f, 0.05f, 0.2f, 0.3f);

		//outer
		adjustFingerMove(2.15f, 0.05f, 0.3f, 0.0f, 0.5f, 0.0f, 90.0f, 0.0f);
		drawRectangle(2.15f, 2.25f, -0.05f, 0.05f, 0.2f, 0.3f);
	glPopMatrix();
}

void adjustFingerMove(float translateX, float translateY, float translateZ, float rotateX, float rotateY, float rotateZ, float maxAngle, float minAngle) {
	glTranslatef(translateX, translateY, translateZ);
		glRotatef(initialFingerMove, rotateX, -rotateY, rotateZ);
		initialFingerMove += fingerMove;
	glTranslatef(-translateX, -translateY, -translateZ);

	if (initialFingerMove >= maxAngle) {

		initialFingerMove = maxAngle;
		fingerMove = 0.0f;

	}
	else if (initialFingerMove <= minAngle) {

		initialFingerMove = minAngle;
		fingerMove = minAngle;

	}
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