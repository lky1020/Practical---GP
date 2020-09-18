#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical 8"

//Shape
void drawSphere(float radius);

//Lighting
boolean isLightOn = false;

//light source
GLfloat dx = 0.0f, dy = 1.1f, dz = 0.5f;
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
			if (posD[1] <= 3.0f) {
				posD[1] += 0.1f;
			}

		}
		//'S' - Move light position down
		else if (wParam == 'S' || wParam == 0x53) {
			if (posD[1] >= -3.0f) {
				posD[1] -= 0.1f;
			}

		}
		//'A' - Move light position left 
		else if (wParam == 'A' || wParam == 0x41) {
			if (posD[0] >= -3.0f) {
				posD[0] -= 0.1f;
			}
		}
		//'D' - Move light position right 
		else if (wParam == 'D' || wParam == 0x44) {
			if (posD[0] <= 3.0f) {
				posD[0] += 0.1f;
			}
		}
		//'E' - Move light position near
		else if (wParam == 'E' || wParam == 0x45) {
			if (posD[2] >= -3.0f) {
				posD[2] -= 0.1f;
			}
		}
		//'Q' - Move light position far
		else if (wParam == 'Q' || wParam == 0x51) {
			if (posD[2] <= 3.0f) {
				posD[2] += 0.1f;
			}
		}
		//Switch off or on the light
		else if (wParam == VK_SPACE) {
			isLightOn = !isLightOn;
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

void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//orthographic
	glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

}

void shadow() {
	GLfloat matrix[16] =
	{
		posD[1],	-posD[0],	0,			0,
		0,			0,			0,			0,
		0,			-posD[2],	posD[1],	0,
		0,			-1,			0,			posD[1]
	};

	glDisable(GL_LIGHTING);	//disable lighting for shadow

	glPushMatrix();
		glTranslatef(-posD[0], 1.0f, 0.0f);		//translate shadow above the plane
		glMultMatrixf(matrix);					//multiply with the squish matrix
		glColor3f(0.0f, 0.0f, 0.0f);			//black color for shadow
		glRotatef(25.0f, 0.5f, 0.0f, 0.0f);		//transformation of plane
		drawSphere(0.25f);						//draw the original object as shadow
	glPopMatrix();

	glEnable(GL_LIGHTING);	//disable lighting for shadow
}

void lighting() {
	if (isLightOn) {
		glEnable(GL_LIGHTING);

		shadow();
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
	glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 250.0f / 255.0f, 1.0f);

	projection();

	lighting();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glPushMatrix();
			glDisable(GL_LIGHTING);
				glTranslatef(posD[0], posD[1] + 0.4f, posD[2]);
				drawSphere(0.05f);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glColor3f(1.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			drawSphere(0.25f);
		glPopMatrix();

		glDisable(GL_LIGHTING);

		glPushMatrix();
			glRotatef(25.0f, 0.5f, 0.0f, 0.0f);
			glColor3f(0.5f, 0.5f, 0.5f);
			glBegin(GL_QUADS);
				glVertex3f(-1.5f, 0.5f, 3.0f);
				glVertex3f(-1.5f, -0.5f, -3.5f);
				glVertex3f(1.5f, -0.5f, -3.5f);
				glVertex3f(1.5f, 0.5f, 3.0f);
			glEnd();
		glPopMatrix();

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