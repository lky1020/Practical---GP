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
int functionType = 1;

//Texture
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle
string str;
GLuint textures = 0;

//Umbrella
float initialConeSpeed = 0.0f;
float coneSpeed = 0.1f;
float initialScope1Translate = 1.5f;
float scope1Translate = 0.0f;

float initialScope2Translate = 1.5f;
float scope2Translate = 0.0f;

float initialScope3Translate = 1.5f;
float scope3Translate = 0.0f;

float initialUmbrellaSpeed = 1.5f;
float umbrellaSpeed = 0.0f;

float initialChipsSpeed = 1.5f;
float chipsSpeed = 0.0f;

float initialChipsSideSpeed = 1.5f;
float chipsSideSpeed = 0.0f;

//draw shape
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum shape, GLenum baseShape);
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum shape);

//Question
void q1();
void q2();
void q3();
void q4();

//Umbrella
void drawIceCream();
void drawCone(float xPos, float yPos, float zPos);
void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv, float r, float g, float b);
void drawUmbrella(float transX, float transY, float transZ, float rotAngle, float rotX, float rotY, float rotZ, float r, float g, float b);
void drawTissue(float xPos, float yPos, float zPos);
void drawChips(float x, float y, float z, float transX, float transY, float transZ, float r, float g, float b);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_F1) {
			functionType = 1;
		}
		else if (wParam == VK_F2) {
			functionType = 2;
		}
		else if (wParam == VK_F3) {
			functionType = 3;
		}
		else if (wParam == '1' || wParam == VK_NUMPAD1) {
			shapeNum = 1;
		}
		else if (wParam == '2' || wParam == VK_NUMPAD2) {
			shapeNum = 2;
		}
		else if (wParam == '3' || wParam == VK_NUMPAD3) {
			shapeNum = 3;
		}
		else if (wParam == '4' || wParam == VK_NUMPAD4) {
			shapeNum = 4;
		}
		else if (wParam == 'A') {
			if (functionType == 1) {
				textureType = 1;
			}
			
		}
		else if (wParam == 'S') {
			if (functionType == 1) {
				textureType = 2;
			}
		}
		else if (wParam == 'D') {
			if (functionType == 1) {
				textureType = 3;
			}
		}
		//Umbrella - Scope 1
		else if (wParam == 'J') {
			if (functionType == 2) {
				scope1Translate = 0.0008f;
			}
		}
		//Umbrella - Scope 2
		else if (wParam == 'K') {
			if (functionType == 2) {
				if (initialScope1Translate <= 1.2f) {
					scope2Translate = 0.0008f;
				}
			}
		}
		//Umbrella - Scope 3
		else if (wParam == 'L') {
			if (functionType == 2) {
				if (initialScope2Translate <= 1.3f) {
					scope3Translate = 0.0008f;
				}
			}
		}
		//Umbrella - Umbrella
		else if (wParam == 'U') {
			if (functionType == 2) {
				if (initialScope3Translate <= 1.0f) {
					umbrellaSpeed = 0.0008f;
					chipsSpeed = 0.001f;
					chipsSideSpeed = 0.001f;
				}
			}
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
		case 3:
			q3();
		case 4:
			q4();
			break;
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

void q3() {
	glPushMatrix();
		glLoadIdentity();
		drawIceCream();
	glPopMatrix();
}

void q4() {

}

//Umbrella
void drawIceCream() {
	glPushMatrix();

		//let the whole ice cream rotate
		glRotatef(initialConeSpeed, 0.0f, 0.5f, 0.0f);
		initialConeSpeed += coneSpeed;

		//draw umbrella
		drawUmbrella(0.0f, 0.50f, 0.0f, 90.0f, -0.5f, 0.0f, 0.0f, 244.0f / 255.0f, 244.0f / 255.0f, 0.0f / 255.0f);

		//draw chips
		glPushMatrix();
			drawChips(0.0f, 0.0f, 0.0f, 0.0f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);

			drawChips(0.0f, 0.0f, 0.0f, 0.1f, 0.35f, 0.0f, 1.0f, 0.0f, 0.0f);

			drawChips(0.0f, 0.0f, 0.0f, -0.1f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);
		glPopMatrix();

		//draw scope 3
		glPushMatrix();
			glTranslatef(0.0f, initialScope3Translate, 0.0f);

			if (initialScope3Translate >= 0.2f) {
				initialScope3Translate -= scope3Translate;
			}
			drawScope(0.175f, 30, 30, 1.0f, 1.1f, 238.0f / 255.0f, 233.0f / 255.0f, 213.0f / 255.0f);
		glPopMatrix();

		//draw scope 2
		glPushMatrix();
			glTranslatef(0.0f, initialScope2Translate, 0.0f);

			if (initialScope2Translate >= 0.1f) {
				initialScope2Translate -= scope2Translate;
			}
			drawScope(0.175f, 30, 30, 0.95f, 1.2f, 133.0f / 255.0f, 97.0f / 255.0f, 66.0f / 255.0f);
		glPopMatrix();

		//draw scope 1
		glPushMatrix();
			glTranslatef(0.0f, initialScope1Translate, 0.0f);

			if (initialScope1Translate >= 0.0f) {
				initialScope1Translate -= scope1Translate;
			}
			drawScope(0.175f, 30, 30, 0.9f, 1.4f, 253.0f / 255.0f, 218.0f / 255.0f, 210.0f / 255.0f);
		glPopMatrix();

		//draw cone
		drawCone(0.0f, -0.5f, 0.0f);

		//draw tissue
		drawTissue(0.0f, -0.5f, 0.0f);

	glPopMatrix();
}

void drawCone(float xPos, float yPos, float zPos) {
	glPushMatrix();
		//initial position of cone
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90.0f, -0.5f, 0.0f, 0.0f);

		//draw cone with FILL
		glColor3d(172.0f / 255.0f, 128.0f / 255.0f, 82.0f / 255.0f);
		GLUquadricObj* cone = NULL;
		cone = gluNewQuadric();
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluCylinder(cone, 0.0f, 0.2f, 0.5f, 30, 30);
		gluDeleteQuadric(cone);

		//draw cone with LINE
		glColor3d(146.0f / 255.0f, 71.0f / 255.0f, 8.0f / 255.0f);
		GLUquadricObj* coneLine = NULL;
		coneLine = gluNewQuadric();
		gluQuadricDrawStyle(coneLine, GLU_LINE);
		gluCylinder(coneLine, 0.0f, 0.2f, 0.5f, 15, 5);
		gluDeleteQuadric(coneLine);
	glPopMatrix();
}

void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv, float r, float g, float b) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;

	for (sliceA = 0.0; sliceA < 2.0 * PI; sliceA += PI / noOfSlice) {

		glColor3d(r, g, b);
		glBegin(GL_TRIANGLE_STRIP);

		for (stackA = 0.0; stackA < 2.0 * PI; stackA += PI / noOfStack) {

			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x / xDiv, y / yDiv, z);

			x = radius * cos(stackA) * sin(sliceA + PI / noOfStack);
			y = radius * sin(stackA) * sin(sliceA + PI / noOfStack);
			z = radius * cos(sliceA + PI / noOfSlice);
			glVertex3f(x / xDiv, y / yDiv, z);
		}

		glEnd();
	}
}

void drawUmbrella(float transX, float transY, float transZ, float rotAngle, float rotX, float rotY, float rotZ, float r, float g, float b) {
	glPushMatrix();

		glTranslatef(transX, initialUmbrellaSpeed, transZ);

		if (initialUmbrellaSpeed >= transY) {
			initialUmbrellaSpeed -= umbrellaSpeed;
		}

		glRotatef(rotAngle, rotX, rotY, rotZ);

		glPushMatrix();
			glLineWidth(5);
			glColor3d(1.0f, 1.0f, 1.0f);
			glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -0.2f);
			glEnd();
			glLineWidth(1);
		glPopMatrix();

		glColor3d(r, g, b);
		GLUquadric* awning = NULL;
		awning = gluNewQuadric();
		gluQuadricDrawStyle(awning, GLU_FILL);
		gluCylinder(awning, 0.2f, 0.0f, 0.1f, 30, 20);
		gluDeleteQuadric(awning);

		glColor3d(r - 20.0f, g - 20.0f, b);
		GLUquadric* awningLine = NULL;
		awningLine = gluNewQuadric();
		gluQuadricDrawStyle(awningLine, GLU_LINE);
		gluCylinder(awningLine, 0.2f, 0.0f, 0.1f, 8, 5);
		gluDeleteQuadric(awningLine);

	glPopMatrix();
}

void drawTissue(float xPos, float yPos, float zPos) {
	glPushMatrix();
		//initial position of cone
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90.0f, -0.5f, 0.0f, 0.0f);

		//draw cone with FILL
		glColor3d(1.0f, 1.0f, 1.0f);
		GLUquadricObj* cone = NULL;
		cone = gluNewQuadric();
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluCylinder(cone, 0.0f, 0.125f, 0.3f, 30, 30);
		gluDeleteQuadric(cone);

	glPopMatrix();
}

void drawChips(float x, float y, float z, float transX, float transY, float transZ, float r, float g, float b) {
	glPushMatrix();
		glTranslatef(transX, initialChipsSpeed, transZ);

		if (initialChipsSpeed >= transY) {
			initialChipsSpeed -= chipsSpeed;
		}

		glPushMatrix();
			glPointSize(10);
			glColor3d(r, g, b);
			glBegin(GL_POINTS);
			glVertex3f(x, y, z);
			glEnd();
		glPopMatrix();

	glPopMatrix();
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