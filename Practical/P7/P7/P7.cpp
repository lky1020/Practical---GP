#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>
using namespace std;

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//draw Shape
void drawCube(float size);

//Texture
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle

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

GLuint loadTexture(LPCSTR fileName) {
	//texture name
	GLuint texture = 0;		

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
					fileName, IMAGE_BITMAP, 0, 0,
					LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	string string;
	string = "Box.bmp";

	GLuint textures[2];

	glRotatef(0.025f, 1.0f, 1.0f, 1.0f);

	textures[0] = loadTexture(string.c_str());
	drawCube(0.5f);
	glDeleteTextures(1, &textures[0]);

	string = "ice.bmp";
	textures[1] = loadTexture(string.c_str());
	drawCube(-0.5f);
	glDeleteTextures(1, &textures[1]);

	glDisable(GL_TEXTURE_2D);

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void drawCube(float size) {
	glBegin(GL_QUADS);

		//glColor3d(1.0f, 0.0f, 0.0f);
		// Face 1 : Bottom
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, 0.0f, size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		//glColor3d(0.0f, 1.0f, 0.0f);
		// Face 2 : Left
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.0f, size, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.0f, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, size);

		//glColor3d(0.0f, 0.0f, 1.0f);
		// Face 3 : Front
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, size, size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, 0.0f, size);

		//glColor3d(1.0f, 1.0f, 0.0f);
		// Face 4 : Right
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, 0.0f, size);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, size, 0.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		//glColor3d(1.0f, 0.0f, 1.0f);
		// Face 5 : Top
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, size, size);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, size, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, size, 0.0f);

		//glColor3d(0.0f, 1.0f, 1.0f);
		// Face 6 : Back
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, 0.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, size, 0.0f);

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
//--------------------------------------------------------------------