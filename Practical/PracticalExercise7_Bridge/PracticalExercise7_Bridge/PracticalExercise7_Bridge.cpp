#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <string>
using namespace std;

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical Exercis 5B"

//Projection
int projectionType = 1;

//Texture
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle
GLuint textures;
string strSideWall = "London_Side_Wall.bmp";
string strStreet = "London_Street.bmp";
string strStreetBackground = "London_Street_Background.bmp";
string strGreyBase = "London_Grey_Base.bmp";
string strSunColor = "Sun_Color.bmp";
string strRoof = "London_Roof.bmp";
string strPillar = "London_Roof.bmp";
string strSplitLine = "London_Split_Line.bmp";
string strBlackLine = "London_Black_Line.bmp";
string strBackground = "dayTime.bmp";
string strSea = "Sea_Texture.bmp";

//Transition & Rotation
float x = 0.0f, y = 0.0f, z = 0.0f;
float initialViewportRotate = 0.0f;
float viewportRotate = 0.0f;
float initialBridgeRotate = 0.0f;
float bridgeRotate = 0.0f;
float bridgeZoomInOut = 0.0f;
float bridgeZoomLeftRight = 0.0f;
float intitialBridgeLift = 0.0f;
float bridgeLift = 0.0f;

//Speed
float rotateSpeed = 2.0f;
float liftSpeed = 1.5f;
float viewportRotateSpeed = 2.0f;

//Bridge Line
float xPoint = 0.0f, yPoint = 0.0f;
float radius = 0.1f;
float angle;

//Bird
float xPoint1 = 0.0f, yPoint1 = 0.0f;
float initialBirdSpeed = 0.01;
float birdSpeed = 0.1f;

//shape
void drawLondonRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type);
void drawLondonRectangleTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type, string frontBack, string topBottom, string leftRight);
void drawLondonRectangleTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type, string front, string back, string top, string bottom, string left, string right);
void drawLondonPyramidTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum shape, GLenum baseShape);
void drawLondonSphere(float radius, int slices, int stacks);
void drawLondonCoverCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, string cylinderTexture, string circleTexture);
void drawLondonCircle(float xPoint, float yPoint, float radius, string circleTexture);
void drawLondonLine(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

void drawFinalBridge();
void drawBridgeBuilding();
void drawBuildingBase(int type);
void drawPillar(float transX, float transY, float transZ1, float transZ2);
void drawBridge();
void drawRotateBridge();
void bridgeLine(float lineX, float lineY, float lineZ, float a, float r);

//background
void sun();
void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void bird(float lineX1, float lineY1, float lineX2, float lineY2);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_NUMPAD1 || wParam == 0x31) {
			//Orthographic
			projectionType = 1;
			bridgeZoomInOut = 0.0f;
			bridgeZoomLeftRight = 0.0f;
		}
		else if (wParam == VK_NUMPAD2 || wParam == 0x32) {
			//Perspective
			projectionType = 2;
			bridgeZoomInOut = 3.0f;
			bridgeZoomLeftRight = 0.0f;
		}
		else if (wParam == VK_UP) {
			if (projectionType == 2) {

				if (bridgeZoomInOut < 6.0f) {
					bridgeZoomInOut += 0.1f;
				}

			}
		}
		else if (wParam == VK_DOWN) {
			if (projectionType == 2) {

				if (bridgeZoomInOut > 0.0f) {
					bridgeZoomInOut -= 0.1f;
				}

			}
		}
		else if (wParam == VK_LEFT) {
			if (projectionType == 2) {

				if (bridgeZoomLeftRight < 1.0f) {
					bridgeZoomLeftRight += 0.1f;
				}

			}
		}
		else if (wParam == VK_RIGHT) {
			if (projectionType == 2) {

				if (bridgeZoomLeftRight > -1.0f) {
					bridgeZoomLeftRight -= 0.1f;
				}

			}
		}
		/*//'X' - rotate x-axis
		else if (wParam == 0x58) {
			x = 0.1f;
			y = 0.0f;
			z = 0.0f;

			viewportRotate = viewportRotateSpeed;
		}
		//'Y' - rotate y-axis
		else if (wParam == 0x59) {
			x = 0.0f;
			y = 0.1f;
			z = 0.0f;

			viewportRotate = viewportRotateSpeed;
		}
		//'Z' - rotate z-axis
		else if (wParam == 0x5A) {
			x = 0.0f;
			y = 0.0f;
			z = 0.1f;

			viewportRotate = viewportRotateSpeed;
		}*/
		else if (wParam == VK_SPACE) {
			initialBridgeRotate = 0.0f;
			bridgeRotate = 0.0f;
			initialViewportRotate = 0.0f;
			viewportRotate = 0.0f;
			intitialBridgeLift = 0.0f;
			bridgeLift = 0.0f;

			if (projectionType == 1) {
				bridgeZoomInOut = 0.0f;
			}
			else if (projectionType == 2) {
				bridgeZoomInOut = 3.0f;
			}

		}
		//'W' - lift bridge up
		else if (wParam == 0x57) {
			bridgeLift = liftSpeed;
		}
		//'S' - lift bridge down
		else if (wParam == 0x53) {
			bridgeLift = -liftSpeed;
		}
		//'A' - rotate bridge left
		else if (wParam == 0x41) {
			bridgeRotate = -rotateSpeed;
		}
		//'D' - rotate bridge left
		else if (wParam == 0x44) {
			bridgeRotate = +rotateSpeed;
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

	//Viewport transformation
	glRotatef(initialViewportRotate, x, y, z);
	initialViewportRotate += viewportRotate;

	glTranslatef(bridgeZoomLeftRight, 0.0f, 0.0f);

	//Projection
	switch (projectionType) {
	case 1:
		glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f);
		break;
	case 2:
		gluPerspective(20.0f, 1.0f, -1.0f, 1.0f);
		glFrustum(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 7.0f);
		break;
	default:
		break;
	}

}

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

void drawSphere(float radius) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, radius, 30, 30);

	gluDeleteQuadric(sphere); //delete the pointer inside the memory to avoid memory full
}

//Draw Background
void drawBackground() {
	glPushMatrix();
		glPushMatrix();
			textures = loadTexture(strBackground.c_str());
				drawSphere(4.25f);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, -1.0f, 0.0f);
			glRotatef(90.0f, 0.1f, 0.0f, 0.0f);
			drawLondonCoverCylinder(4.0f, 4.0f, 3.0f, 20, 20, strSea, strSea);
		glPopMatrix();

	glPopMatrix();
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//background
	glPushMatrix();

		if (projectionType == 1) {
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, 2.0f);
		}

		glDisable(GL_DEPTH_TEST);
			drawBackground();
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, bridgeZoomInOut);
			glRotatef(initialBridgeRotate, 0.0f, 1.0f, 0.0f);
		glTranslatef(-0.0f, -0.0f, -bridgeZoomInOut);

		initialBridgeRotate += bridgeRotate;

		drawFinalBridge();
	glPopMatrix();

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

//shape
void drawLondonRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type) {
	//Back
	glBegin(type);
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
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Left
	glBegin(type);
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
	glBegin(type);
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
	glBegin(type);
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
	glBegin(type);
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
void drawLondonRectangleTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type, string frontBack, string topBottom, string leftRight) {
	//Back
	textures = loadTexture(frontBack.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, minZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Bottom
	textures = loadTexture(topBottom.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Left
	textures = loadTexture(leftRight.c_str());
	glBegin(type);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Top
	textures = loadTexture(topBottom.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Right
	textures = loadTexture(leftRight.c_str());
	glBegin(type);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Front
	textures = loadTexture(frontBack.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);
}
void drawLondonRectangleTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type, string front, string back, string top, string bottom, string left, string right) {
	//Back
	textures = loadTexture(back.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, minZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Bottom
	textures = loadTexture(bottom.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Left
	textures = loadTexture(left.c_str());
	glBegin(type);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Top
	textures = loadTexture(top.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, maxY, minZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Right
	textures = loadTexture(right.c_str());
	glBegin(type);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(maxX, minY, minZ);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(maxX, minY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Front
	textures = loadTexture(front.c_str());
	glBegin(type);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(maxX, minY, maxZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);
}
void drawLondonPyramidTexture(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum shape, GLenum baseShape) {

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
void drawLondonSphere(float radius, int slices, int stacks) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, radius, slices, stacks);

	gluDeleteQuadric(sphere);
}
void drawLondonCoverCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, string cylinderTexture, string circleTexture) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();

	textures = loadTexture(cylinderTexture.c_str());
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluCylinder(cylinder, baseRadius, topRadius, height, slices, stacks);

	gluDeleteQuadric(cylinder);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//Upper cover (same rotation with cylinder)
	drawLondonCircle(0.0f, 0.0f, baseRadius, circleTexture);

	//Lower cover (not same rotation with cylinder)
	glTranslatef(0.0f, 0.0f, 0.5f);
	drawLondonCircle(0.0f, 0.0f, topRadius, circleTexture);
}
void drawLondonCircle(float xPoint, float yPoint, float radius, string circleTexture) {

	textures = loadTexture(circleTexture.c_str());

	glBegin(GL_TRIANGLE_FAN);
	//origin
	glVertex2f(xPoint, yPoint);

	for (float angle = 0; angle <= 360; angle += 0.1) {

		if (xPoint / 4 == 0) {
			glTexCoord2f(0.0f, 0.0f);
		}
		else {
			glTexCoord2f(0.0f, 1.0f);
		}
		
		glVertex2f(xPoint + radius * cos(angle), yPoint + radius * sin(angle));
	}
	glEnd();

	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);
}
void drawLondonLine(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	glBegin(GL_LINES);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
}

void drawFinalBridge() {
	glPushMatrix();
	//left
	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, bridgeZoomInOut);
	drawBridgeBuilding();
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(1.5f, -1.0f, bridgeZoomInOut);
	glRotatef(-180.0f, 0.0f, 0.1f, 0.0f);
	drawBridgeBuilding();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, 1.0f, bridgeZoomInOut);
	sun();

	//Bird Fly
	glPushMatrix();
		glTranslatef(initialBirdSpeed, 0.0f, 0.0f);
		textures = loadTexture(strBlackLine.c_str());
			bird(0.525f, 0.8f, 0.775f, 0.8f);
			bird(0.275f, 0.6f, 0.525f, 0.6f);
			bird(-0.175f, 0.75f, 0.075f, 0.75f);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	initialBirdSpeed += birdSpeed;

	if (initialBirdSpeed > 3.5f) {
		initialBirdSpeed = birdSpeed;
	}
	if (initialBirdSpeed < -2.0f) {
		initialBirdSpeed = birdSpeed;
	}

	glPopMatrix();
	glPopMatrix();
}
void drawBridgeBuilding() {
	glPushMatrix();

		//draw base
		glPushMatrix();
			glRotatef(90.0f, 0.5f, 0.0f, 0.0f);
			drawLondonCoverCylinder(0.5f, 0.5f, 0.5f, 30, 30, strGreyBase, strBlackLine);
		glPopMatrix();

		//building
		//ground floor
		drawBuildingBase(0);

		//1st floor
		glPushMatrix();
			glTranslatef(0.0f, 0.65f, 0.0f);
			drawBuildingBase(1);
		glPopMatrix();

		//2nd floor
		glPushMatrix();
			glTranslatef(0.0f, 1.3f, 0.0f);
			drawBuildingBase(1);
		glPopMatrix();

		//Roof
		glPushMatrix();
			glTranslatef(0.0f, 1.95f, 0.0f);

			textures = loadTexture(strRoof.c_str());
				drawLondonPyramidTexture(-0.29f, 0.29f, 0.006f, 0.59f, -0.29f, 0.29f, 20.0f, 20.0f, GL_TRIANGLES, GL_QUADS);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		
			textures = loadTexture(strSplitLine.c_str());
				drawLondonPyramidTexture(-0.299f, 0.299f, 0.0055f, 0.61f, -0.29f, 0.29f, 20.0f, 20.0f, GL_LINE_LOOP, GL_LINE_LOOP);
			glDeleteTextures(1, &textures);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		//pillar
		drawPillar(0.285f, -0.275f, 0.0f, 1.6f);
		drawPillar(-0.285f, -0.275f, 0.0f, 1.6f);
		drawPillar(0.285f, 0.275f, 0.0f, 1.6f);
		drawPillar(-0.285f, 0.275f, 0.0f, 1.6f);

		//bridge
		drawBridge();
		drawRotateBridge();

		drawLondonRectangleTexture(0.34f, 1.51f, 1.5f, 1.6f, -0.2f, -0.15f, GL_QUADS, strSideWall, strSideWall, strSideWall);
		drawLondonRectangleTexture(0.34f, 1.51f, 1.5f, 1.6f, 0.15f, 0.2f, GL_QUADS, strSideWall, strSideWall, strSideWall);

		//bridgeLine
		textures = loadTexture(strBlackLine.c_str());
			bridgeLine(-1.325f, 1.6f, -0.2f, 1.65f, 1.0f);
			bridgeLine(-1.325f, 1.6f, 0.2f, 1.65f, 1.0f);

			//linker line
			//1
			drawLondonLine(-1.4f, 0.1f, -0.2f, -1.4f, 0.6f, -0.2f);
			drawLondonLine(-1.4f, 0.1f, 0.2f, -1.4f, 0.6f, 0.2f);
			drawLondonLine(-1.4f, 0.6f, -0.2f, -1.4f, 0.6f, 0.2f);

			//2
			drawLondonLine(-1.15f, 0.1f, -0.2f, -1.15f, 0.625f, -0.2f);
			drawLondonLine(-1.15f, 0.1f, 0.2f, -1.15f, 0.625f, 0.2f);
			drawLondonLine(-1.15f, 0.625f, -0.2f, -1.15f, 0.625f, 0.2f);

			//3
			drawLondonLine(-0.95f, 0.1f, -0.2f, -0.95f, 0.675f, -0.2f);
			drawLondonLine(-0.95f, 0.1f, 0.2f, -0.95f, 0.675f, 0.2f);
			drawLondonLine(-0.95f, 0.675f, -0.2f, -0.95f, 0.675f, 0.2f);

			//4
			drawLondonLine(-0.75f, 0.1f, -0.2f, -0.75f, 0.775f, -0.2f);
			drawLondonLine(-0.75f, 0.1f, 0.2f, -0.75f, 0.775f, 0.2f);
			drawLondonLine(-0.75f, 0.775f, -0.2f, -0.75f, 0.775f, 0.2f);

			//5
			drawLondonLine(-0.5f, 0.1f, -0.2f, -0.5f, 1.05f, -0.2f);
			drawLondonLine(-0.5f, 0.1f, 0.2f, -0.5f, 1.05f, 0.2f);
			drawLondonLine(-0.5f, 1.05f, -0.2f, -0.5f, 1.05f, 0.2f);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void drawBuildingBase(int type) {

	glLineWidth(2.5);

	//Inner
	//front inner

	drawLondonRectangleTexture(-0.29f, 0.29f, 0.006f, 0.349f, -0.29f, -0.21f, GL_QUADS, strSideWall, strSideWall, strSideWall);

	textures = loadTexture(strSplitLine.c_str());
	drawLondonRectangle(-0.30f, 0.30f, 0.005f, 0.35f, -0.30f, -0.20f, GL_LINE_LOOP);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//top inner
	drawLondonRectangleTexture(-0.29f, 0.29f, 0.351f, 0.504f, -0.29f, 0.29f, GL_QUADS, strSideWall, strSideWall, strSideWall);

	textures = loadTexture(strSplitLine.c_str());
	drawLondonRectangle(-0.30f, 0.30f, 0.35f, 0.505f, -0.30f, 0.30f, GL_LINE_LOOP);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//back inner
	drawLondonRectangleTexture(-0.29f, 0.29f, 0.0051f, 0.349f, 0.21f, 0.29f, GL_QUADS, strSideWall, strSideWall, strSideWall);

	textures = loadTexture(strSplitLine.c_str());
	drawLondonRectangle(-0.30f, 0.30f, 0.005f, 0.350f, 0.20f, 0.30f, GL_LINE_LOOP);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	//cover
	drawLondonRectangleTexture(-0.29f, 0.29f, 0.506f, 0.654f, -0.29f, 0.29f, GL_QUADS, strSideWall, strSideWall, strSideWall);

	textures = loadTexture(strSplitLine.c_str());
	drawLondonRectangle(-0.3001f, 0.3001f, 0.5051f, 0.6551f, -0.3001f, 0.3001f, GL_LINE_LOOP);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);

	if (type != 0) {

		drawLondonRectangleTexture(-0.29f, 0.29f, 0.0051f, 0.349f, -0.19f, 0.19f, GL_QUADS, strSideWall, strSideWall, strSideWall);
	}

}
void drawPillar(float transX, float transY, float transZ1, float transZ2) {
	glPushMatrix();

		glRotatef(-90.0f, 0.5f, 0.0f, 0.0f);

		glPushMatrix();
			glTranslatef(transX, transY, transZ1);
			drawLondonCoverCylinder(0.05f, 0.05f, 2.1f, 25, 25, strPillar, strGreyBase);

			//roof
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, transZ2);
				drawLondonCoverCylinder(0.05f, 0.0f, 0.25f, 25, 25, strRoof, strGreyBase);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}
void drawBridge() {
	glPushMatrix();
		drawLondonRectangleTexture(-1.5f, 0.45f, 0.005f, 0.1f, -0.2f, 0.2f, GL_QUADS, strStreetBackground, strStreetBackground, strStreet, strStreetBackground, strStreetBackground, strStreetBackground);
	glPopMatrix();
}
void drawRotateBridge() {
	glPushMatrix();

	glTranslatef(0.45f, 0.1f, 0.2f);
	glRotatef(intitialBridgeLift, 0.0f, 0.0f, 0.1f);
	intitialBridgeLift += bridgeLift;
	glTranslatef(-0.45f, -0.1f, -0.2f);

	if (intitialBridgeLift >= 55.0f) {

		intitialBridgeLift = 55.0f;
		bridgeLift = 0.0f;

	}
	else if (intitialBridgeLift <= 0.0f) {

		intitialBridgeLift = 0.0f;
		bridgeLift = 0.0f;

	}

	drawLondonRectangleTexture(0.45f, 1.5f, 0.005f, 0.1f, -0.2f, 0.2f, GL_QUADS, strStreetBackground, strStreetBackground, strStreet, strStreetBackground, strStreetBackground, strStreetBackground);
	glPopMatrix();
}
void bridgeLine(float lineX, float lineY, float lineZ, float a, float r) {
	glPushMatrix();

	//left wing
	xPoint = lineX;
	yPoint = lineY;
	radius = r;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= a; angle += 0.01) {
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(xPoint + radius * cos(angle), yPoint + radius * -sin(angle), lineZ);

	}
	glEnd();
	glPopMatrix();
}

//background
void sun() {

	glPushMatrix();
		glTranslatef(-1.0f, 1.0f, 0.0f);

		textures = loadTexture(strSunColor.c_str());
			drawLondonSphere(0.5f, 25, 25);
		glDeleteTextures(1, &textures);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	textures = loadTexture(strSunColor.c_str());
		sunTriangle(-0.95f, 0.475f, -0.80f, 0.50f, -0.85f, 0.30f);
		sunTriangle(-0.7f, 0.55f, -0.50f, 0.425f, -0.575f, 0.65f);
		sunTriangle(-0.475f, 0.85f, -0.525f, 0.70f, -0.275f, 0.725f);
		sunTriangle(-0.475f, 1.0f, -0.475f, 0.90f, -0.30f, 0.965f);
	glDeleteTextures(1, &textures);
	glDisable(GL_TEXTURE_2D);
}
void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(x1, y1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(x2, y2);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x3, y3);
	glEnd();
}
void bird(float lineX1, float lineY1, float lineX2, float lineY2) {

	//left wing
	xPoint1 = lineX1;
	yPoint1 = lineY1;
	radius = 0.125;

	glLineWidth(2);

	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= 2; angle += 0.01) {
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(xPoint1 + radius * cos(angle), yPoint1 + radius * sin(angle));
	}
	glEnd();

	//right wing
	xPoint1 = lineX2;
	yPoint1 = lineY2;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= 2; angle += 0.001) {
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(xPoint1 + radius * -cos(angle), yPoint1 + radius * sin(angle));
	}
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