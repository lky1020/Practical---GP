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
void drawPyramid(float size);

//Q3
void q3();


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
		else if (wParam == 0x58) {
			x = 1.0f;
			y = 0.0f;
			z = 0.0f;
			pyramidSpeed = 0.01f;
		}
		else if (wParam == 0x59) {
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
			pyramidSpeed = 0.01f;
		}
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
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch (qNum) {
		case 1:
			q1q2();
			break;
		case 3:
			q3();
			break;
		default:
			q1q2();
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
		drawPyramid(0.5f);

	glPopMatrix();
}

void drawPyramid(float size) {
	//base
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size, size, 0.0f);
	glEnd();

	//left side triangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size/2, size/2, size);
	glEnd();

	//top side triangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size/2, size/2, size);
	glEnd();

	//right side triangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size/2, size/2, size);
	glEnd();

	//bottom side triangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size/2, size/2, size);
	glEnd();

}

//Q3
void q3() {

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