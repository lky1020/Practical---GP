#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical Execise 6"

//Shape
void drawSphere(float radius);
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ);

char shape = 'O';
float speed = 0.1f;

//rotation
float x = 0.0f, y = 0.0f, z = 0.0f;
float initialRotate = 0.0f;
float rotateSpeed = 0.0f;

//Lighting
boolean isLightOn = false;

//light source
GLfloat dx = 0.0f, dy = 0.0f, dz = 0.0f;
GLfloat diffuseColor[] = { 1.0f, 0.0f, 0.0f };
GLfloat posD[] = { dx, dy, dz };

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		//'W' - Move light position up 
		else if (wParam == 'W' || wParam == 0x57) {
			if (posD[1] <= 1.0f) {
				posD[1] += 0.1f;
			}
			
		}
		//'S' - Move light position down
		else if (wParam == 'S' || wParam == 0x53) {
			if (posD[1] >= -1.0f) {
				posD[1] -= 0.1f;
			}
			
		}
		//'A' - Move light position left 
		else if (wParam == 'A' || wParam == 0x41) {
			if (posD[0] >= -1.0f) {
				posD[0] -= 0.1f;
			}
		}
		//'D' - Move light position right 
		else if (wParam == 'D' || wParam == 0x44) {
			if (posD[0] <= 1.0f) {
				posD[0] += 0.1f;
			}
		}
		//'E' - Move light position near
		else if (wParam == 'E' || wParam == 0x45) {
			if (posD[2] >= -1.0f) {
				posD[2] -= 0.1f;
			}
		}
		//'Q' - Move light position far
		else if (wParam == 'Q' || wParam == 0x51) {
			if (posD[2] <= 1.0f) {
				posD[2] += 0.1f;
			}
		}
		//Rotate ClockWise at all axis
		else if (wParam == VK_UP) {
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;

			rotateSpeed = -speed;
		}
		//Rotate Anti - ClockWise at all axis
		else if (wParam == VK_DOWN) {
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;

			rotateSpeed = speed;
		}
		//Switch off or on the light
		else if (wParam == VK_SPACE) {
			isLightOn = !isLightOn;
		}
		//'O' - Sphere
		else if (wParam == 'O') {
			shape = 'O';
		}
		//'P' - Pyramid
		else if (wParam == 'P') {
			shape = 'P';
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

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}

	//Diffuse
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT0, GL_POSITION, posD);
	glEnable(GL_LIGHT0);
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lighting();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glRotatef(initialRotate, x, y, z);
		initialRotate += rotateSpeed;

		glColor3f(1.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

		switch (shape) {
			case 'O':
				drawSphere(0.5f);
				break;
			case 'P':
				drawPyramid(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 10.0f, 10.0f);
				break;
			default:
				break;
		}


	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

//Shape
void drawSphere(float radius) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, radius, 30, 30);

	gluDeleteQuadric(sphere); //delete the pointer inside the memory to avoid memory full
}
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ) {

	//face - back
	glBegin(GL_TRIANGLES);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - top
	glBegin(GL_TRIANGLES);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - bottom
	glBegin(GL_TRIANGLES);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - front
	glBegin(GL_TRIANGLES);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - base
	glBegin(GL_QUADS);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(minX, minY, minZ);
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