#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "P1 - Intro"

//Function
void pahangFlag();
void negeriSembilanFlag();
void englandFlag();

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
//--------------------------------------------------------------------

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);	//set background to red color
	//glClear(GL_COLOR_BUFFER_BIT);	//is used to clear the black background

	//Triangle
	/*glLineWidth(10);	//set width of line (default = 1)
	glBegin(GL_TRIANGLES);	//GL_TRIANGLES create triangle, //GL_LINE_LOOP create line
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();*/

	//Quads
	/*glBegin(GL_QUADS);

	//Red vertex
	glColor3d(1.0f, 0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);

	//Green vertex
	glColor3d(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.5f, 0.5f);

	//Blue vertex
	glColor3d(0.0f, 0.0f, 1.0f);
	glVertex2f(-0.5f, -0.5f);

	//Color vertex
	glColor3d(1.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);

	glEnd();*/

	//Pahang Flag
	//pahangFlag();

	//Negeri Sembilan Flag
	//negeriSembilanFlag();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void pahangFlag() {
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	glEnd();
}

void negeriSembilanFlag() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-0.8f, 0.5f);
	glVertex2f(0.8f, 0.5f);
	glVertex2f(0.8f, -0.5f);
	glVertex2f(-0.8f, -0.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.8f, 0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.8f, 0.5f);
	glVertex2f(-0.8f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
}

void englandFlag() {

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

		display();	//the display will keep refresh (complex code can put outside to prevent crash);

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------