#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <string>
using namespace std;

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

//variable
int shapeNum = 1;
int textureType = 1;

//Texture
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle
string str;
GLuint textures = 0;

//draw shape
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum shape, GLenum baseShape);
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum shape);

//Question
void q1();
void q2();

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == '1' || wParam == VK_NUMPAD1) {
			shapeNum = 1;
		}
		else if (wParam == '2' || wParam == VK_NUMPAD2) {
			shapeNum = 2;
		}
		else if (wParam == 'A') {
			textureType = 1;
		}
		else if (wParam == 'S') {
			textureType = 2;
		}
		else if (wParam == 'D') {
			textureType = 3;
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

	glRotatef(0.01f, 1.0f, 1.0f, 1.0f);

	//Start draw
	switch (shapeNum) {
		case 1:
			q1();
			break;
		case 2:
			q2();
			break;
		default:
			break;
	}

	glDisable(GL_TEXTURE_2D);

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

//draw shape
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum shape, GLenum baseShape) {

	//face - back
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - top
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - bottom
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - front
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - base
	glBegin(baseShape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
	glEnd();

}
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum shape) {
	//Back
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, minZ);
	glEnd();

	//Bottom
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Left
	glBegin(shape);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
	glEnd();

	//Top
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();

	//Right
	glBegin(shape);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Front
	glBegin(shape);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
}

//Question
void q1() {
	str = "pixelBrick.bmp";
	textures = loadTexture(str.c_str());
	drawPyramid(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 20, 20, GL_TRIANGLES, GL_QUADS);
	glDeleteTextures(1, &textures);
}

void q2() {

	switch (textureType) {
		case 1:
			str = "Box.bmp";
			break;
		case 2:
			str = "metal.bmp";
			break;
		case 3:
			str = "pixelBrick.bmp";
			break;
		default:
			break;
	}

	textures = loadTexture(str.c_str());

	drawRectangle(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, GL_QUADS);
	glDeleteTextures(1, &textures);
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