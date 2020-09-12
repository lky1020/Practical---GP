#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <string>
using namespace std;

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

float initialConeSpeed = 0.0f;
float coneSpeed = 0.25f;
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

//Texture
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle
GLuint textures;

string strChips = "Chips_IceCream.bmp";
string strCone = "Cone_Texture.bmp";
string strUmbrella = "Umbrella_Texture.bmp";
string strVanilla = "Vanilla_IceCream.bmp";
string strStrawberry = "Strawberry_IceCream.bmp";
string strChocolate = "Chocolate_IceCream.bmp";
string strTissue = "Tissue_Texture.bmp";

void drawIceCream();
void drawCone(float xPos, float yPos, float zPos);
void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv);
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
		else if (wParam == 0x31 || wParam == VK_NUMPAD1) {
			scope1Translate = 0.001f;
		}
		else if (wParam == 0x32 || wParam == VK_NUMPAD2) {
			if (initialScope1Translate <= 1.2f) {
				scope2Translate = 0.001f;
			}

		}
		else if (wParam == 0x33 || wParam == VK_NUMPAD3) {
			if (initialScope2Translate <= 1.3f) {
				scope3Translate = 0.001f;
			}
		}
		else if (wParam == 0x55) {
			if (initialScope3Translate <= 1.0f) {
				umbrellaSpeed = 0.001f;
				chipsSpeed = 0.001f;
				chipsSideSpeed = 0.001f;
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

//Texture
GLuint loadTexture(LPCSTR fileName) {

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		fileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textures);
	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return textures;
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glEnable(GL_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		drawIceCream();
	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void drawIceCream() {
	glPushMatrix();

		//let the whole ice cream rotate
		glRotatef(initialConeSpeed, 0.0f, 0.5f, 0.0f);
		initialConeSpeed += coneSpeed;

		//draw umbrella
		drawUmbrella(0.0f, 0.50f, 0.0f, 90.0f, -0.5f, 0.0f, 0.0f, 244.0f / 255.0f, 244.0f / 255.0f, 0.0f / 255.0f);

		//draw chips
		glPushMatrix();
			textures = loadTexture(strChips.c_str());
				drawChips(0.0f, 0.0f, 0.0f, 0.0f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);

				drawChips(0.0f, 0.0f, 0.0f, 0.1f, 0.35f, 0.0f, 1.0f, 0.0f, 0.0f);

				drawChips(0.0f, 0.0f, 0.0f, -0.1f, 0.375f, 0.0f, 1.0f, 0.0f, 0.0f);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//draw scope 3
		glPushMatrix();
			glTranslatef(0.0f, initialScope3Translate, 0.0f);

			if (initialScope3Translate >= 0.2f) {
				initialScope3Translate -= scope3Translate;
			}
			textures = loadTexture(strStrawberry.c_str());
				drawScope(0.175f, 30, 30, 1.0f, 1.1f);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//draw scope 2
		glPushMatrix();
			glTranslatef(0.0f, initialScope2Translate, 0.0f);

			if (initialScope2Translate >= 0.1f) {
				initialScope2Translate -= scope2Translate;
			}
			textures = loadTexture(strChocolate.c_str());
				drawScope(0.175f, 30, 30, 0.95f, 1.2f);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//draw scope 1
		glPushMatrix();
			glTranslatef(0.0f, initialScope1Translate, 0.0f);

			if (initialScope1Translate >= 0.0f) {
				initialScope1Translate -= scope1Translate;
			}
			textures = loadTexture(strVanilla.c_str());
				drawScope(0.175f, 30, 30, 0.9f, 1.3f);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
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
		//glColor3d(172.0f / 255.0f, 128.0f / 255.0f, 82.0f / 255.0f);
		textures = loadTexture(strCone.c_str());
			GLUquadricObj* cone = NULL;
			cone = gluNewQuadric();

			gluQuadricDrawStyle(cone, GLU_FILL);
			gluQuadricTexture(cone, TRUE);
			gluQuadricNormals(cone, GLU_SMOOTH);

			gluCylinder(cone, 0.0f, 0.2f, 0.5f, 30, 30);
			gluDeleteQuadric(cone);

		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);

		/*//draw cone with LINE
		//glColor3d(146.0f / 255.0f, 71.0f / 255.0f, 8.0f / 255.0f);
		textures = loadTexture(strCone.c_str());
			GLUquadricObj* coneLine = NULL;
			coneLine = gluNewQuadric();
				
			gluQuadricDrawStyle(coneLine, GLU_LINE);
			gluQuadricTexture(coneLine, TRUE);
			gluQuadricNormals(coneLine, GLU_SMOOTH);

			gluCylinder(coneLine, 0.0f, 0.2f, 0.5f, 15, 5);
			gluDeleteQuadric(coneLine);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);*/
	glPopMatrix();
}

void drawScope(GLfloat radius, int noOfSlice, int noOfStack, float xDiv, float yDiv) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;

	for (sliceA = 0.0; sliceA < PI; sliceA += PI / noOfSlice) {

		glBegin(GL_TRIANGLE_STRIP);

		for (stackA = 0.0; stackA < 2.0 * PI; stackA += PI / noOfStack) {

			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);

			/*if (x / 4 == 0) {
				glTexCoord2f(0.0f, 0.0f);
			}
			else if (x / 3 == 0) {
				glTexCoord2f(1.0f, 0.0f);
			}
			else if (x / 2 == 0) {
				glTexCoord2f(0.0f, 1.0f);
			}
			else {
				glTexCoord2f(1.0f, 1.0f);
			}*/
			// tx = cos(stackA);
			//float ty = sin(stackA);

			glTexCoord2f(x/2, y/2);
			glVertex3f(x / xDiv, y / yDiv, z);

			x = radius * cos(stackA) * sin(sliceA + PI / noOfStack);
			y = radius * sin(stackA) * sin(sliceA + PI / noOfStack);
			z = radius * cos(sliceA + PI / noOfSlice);
			
			/*if (x / 4 == 0) {
				glTexCoord2f(0.0f, 0.0f);
			}
			else if (x / 3 == 0) {
				glTexCoord2f(1.0f, 0.0f);
			}
			else if (x / 2 == 0) {
				glTexCoord2f(0.0f, 1.0f);
			}
			else {
				glTexCoord2f(1.0f, 1.0f);
			}*/

			//tx = cos(stackA);
			//ty = sin(stackA);

			glTexCoord2f(x/2, y/2);
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

			textures = loadTexture(strVanilla.c_str());
				glBegin(GL_LINES);
					glTexCoord2f(0.0f, 0.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0f, 1.0f);
					glVertex3f(0.0f, 0.0f, -0.2f);
				glEnd();
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);

			glLineWidth(1);
		glPopMatrix();

		textures = loadTexture(strUmbrella.c_str());
			GLUquadric* awning = NULL;
			awning = gluNewQuadric();
			gluQuadricDrawStyle(awning, GLU_FILL);
			gluQuadricTexture(awning, TRUE);
			gluQuadricNormals(awning, GLU_SMOOTH);
				gluCylinder(awning, 0.2f, 0.0f, 0.1f, 30, 20);
			gluDeleteQuadric(awning);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void drawTissue(float xPos, float yPos, float zPos) {
	glPushMatrix();
		//initial position of cone
		glTranslatef(xPos, yPos, zPos);
		glRotatef(90.0f, -0.5f, 0.0f, 0.0f);

		//draw cone with FILL
		//glColor3d(1.0f, 1.0f, 1.0f);
		textures = loadTexture(strTissue.c_str());
		GLUquadricObj* cone = NULL;
		cone = gluNewQuadric();
		gluQuadricDrawStyle(cone, GLU_FILL);
		gluQuadricTexture(cone, TRUE);
		gluQuadricNormals(cone, GLU_SMOOTH);

			gluCylinder(cone, 0.0f, 0.125f, 0.3f, 30, 30);
		gluDeleteQuadric(cone);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);
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
			//glColor3d(r, g, b);
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