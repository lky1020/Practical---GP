#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "P1 - Intro"

//Function
void triangle();
void lineLoopTriangle();
void pointTriangle();
void quad();
void pahangFlag();
void negeriSembilanFlag();
void englandFlag();
void scotlandFlag();

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
	//triangle();

	//Line Loop Triangle
	//lineLoopTriangle();

	//Point Triangle
	//pointTriangle();

	//Quads
	//quad();

	//Practical 1 exercise
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Pahang Flag
	pahangFlag();

	//Negeri Sembilan Flag
	negeriSembilanFlag();

	//England Falg
	englandFlag();

	//Scotland Flag
	scotlandFlag();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void triangle() {
	glBegin(GL_TRIANGLES);	//GL_TRIANGLES create triangle, //GL_LINE_LOOP create line
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

void lineLoopTriangle() {
	glLineWidth(10.0);	//set width of line (default = 1)
	glBegin(GL_LINE_LOOP);	//GL_TRIANGLES create triangle, //GL_LINE_LOOP create line
	
	//Red vertex
	glColor3d(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);

	//Green vertex
	glColor3d(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);

	//Blue vertex
	glColor3d(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

void pointTriangle() {

	//Point is based on the pixel(so point is square)
	glPointSize(25.0);
	glBegin(GL_POINTS);

	//Red vertex
	glColor3d(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);

	//Green vertex
	glColor3d(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);

	//Blue vertex
	glColor3d(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

void quad() {
	glBegin(GL_QUADS);

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

	glEnd();
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
	glBegin(GL_QUADS);
	//top left (white)
	glColor3d(0.5, 0.5, 0.5);
	glVertex2f(0.5, 0.5);

	glColor3d(1.0, 1.0, 1.0);
	glVertex2f(0.5, 0.4);
	glVertex2f(0.725, 0.4);
	glVertex2f(0.725, 0.5);

	//top right (white)
	glVertex2f(0.775, 0.5);
	glVertex2f(0.775, 0.4);
	glVertex2f(1.0, 0.4);

	glColor3d(0.5, 0.5, 0.5);
	glVertex2f(1.0, 0.5);

	//bottom left (white)
	glColor3d(1.0, 1.0, 1.0);
	glVertex2f(0.5, 0.35);

	glColor3d(0.5, 0.5, 0.5);
	glVertex2f(0.5, 0.25);

	glColor3d(1.0, 1.0, 1.0);
	glVertex2f(0.725, 0.25);
	glVertex2f(0.725, 0.35);

	//bottom right (white)
	glVertex2f(0.775, 0.35);
	glVertex2f(0.775, 0.25);

	glColor3d(0.5, 0.5, 0.5);
	glVertex2f(1.0, 0.25);

	glColor3d(1.0, 1.0, 1.0);
	glVertex2f(1.0, 0.35);

	glColor3d(0.57, 0.0, 0.0); //red

	//left banner (red)
	glVertex2f(0.5, 0.40);
	glVertex2f(0.5, 0.35);
	glVertex2f(0.725, 0.35);
	glVertex2f(0.725, 0.40);

	//down banner (red)
	glVertex2f(0.725, 0.35);
	glVertex2f(0.725, 0.25);
	glVertex2f(0.775, 0.25);
	glVertex2f(0.775, 0.35);

	//right banner (red)
	glVertex2f(0.775, 0.4);
	glVertex2f(0.775, 0.35);
	glVertex2f(1.0, 0.35);
	glVertex2f(10., 0.4);

	//up banner (red)
	glVertex2f(0.725, 0.5);
	glVertex2f(0.725, 0.4);
	glVertex2f(0.775, 0.4);
	glVertex2f(0.775, 0.5);

	//middle square (red)
	glVertex2f(0.725, 0.4);
	glVertex2f(0.725, 0.35);
	glVertex2f(0.775, 0.35);
	glVertex2f(0.775, 0.4);
	glEnd();

}

void scotlandFlag() {
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0); //white
	glVertex2f(-1.0, -0.25);
	glVertex2f(-1.0, -0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, -0.25);
	glEnd();

	glColor3d(0.0, 0.4, 0.74); //blue

	glBegin(GL_TRIANGLES);
	//left
	glVertex2f(-1.0, -0.3);
	glVertex2f(-1.0, -0.45);
	glVertex2f(-0.80, -0.375);

	//down
	glVertex2f(-0.75, -0.4);
	glVertex2f(-0.95, -0.5);
	glVertex2f(-0.55, -0.5);

	//right
	glVertex2f(-0.7, -0.375);
	glVertex2f(-0.5, -0.45);
	glVertex2f(-0.5, -0.3);

	//up
	glVertex2f(-0.95, -0.25);
	glVertex2f(-0.75, -0.35);
	glVertex2f(-0.55, -0.25);
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