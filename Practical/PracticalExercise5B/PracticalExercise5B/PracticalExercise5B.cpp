#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Practical Exercis 5B"

//Projection
int projectionType = 1;

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

//Bridge Line
float xPoint = 0.0f, yPoint = 0.0f;
float radius = 0.1f;
float angle;

//Bird
float xPoint1 = 0.0f, yPoint1 = 0.0f;
float initialBirdSpeed = 0.01;
float birdSpeed = 0.01f;

//shape
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type);
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum type);
void drawSphere(float radius, int slices, int stacks);
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2);
void drawCircle(float xPoint, float yPoint, float radius);
void drawLine(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

void drawFinalBridge();
void drawBridgeBuilding();
void drawBuildingBase(int type);
void drawPillar(float transX, float transY, float transZ1, float transZ2);
void drawBridge(float cx, float cy, float cz);
void drawRotateBridge(float cx, float cy, float cz);
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

				if(bridgeZoomInOut < 6.0f){
					bridgeZoomInOut += 0.1f;
				}

			}
		}
		else if (wParam == VK_DOWN) {
			if (projectionType == 2) {

				if (bridgeZoomInOut > 3.0f) {
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
		//'X' - rotate x-axis
		else if (wParam == 0x58) {
			x = 0.1f;
			y = 0.0f;
			z = 0.0f;

			viewportRotate = 0.25f;
		}
		//'Y' - rotate y-axis
		else if (wParam == 0x59) {
			x = 0.0f;
			y = 0.1f;
			z = 0.0f;

			viewportRotate = 0.25f;
		}
		//'Z' - rotate z-axis
		else if (wParam == 0x5A) {
			x = 0.0f;
			y = 0.0f;
			z = 0.1f;

			viewportRotate = 0.25f;
		}
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
			bridgeLift = 0.05f;
		}
		//'S' - lift bridge down
		else if (wParam == 0x53) {
			bridgeLift = -0.05f;
		}
		//'A' - rotate bridge left
		else if (wParam == 0x41) {
			bridgeRotate = -0.50f;
		}
		//'D' - rotate bridge left
		else if (wParam == 0x44) {
			bridgeRotate = +0.50f;
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

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(43.0f / 255.0f, 124.0f / 255.0f, 211.0f / 255.0f, 1.0f);

	projection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
void drawRectangle(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, GLenum type) {
	//Back
	glBegin(type);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, maxY, minZ);
	glEnd();

	//Bottom
	glBegin(type);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Left
	glBegin(type);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(minX, minY, maxZ);
	glEnd();

	//Top
	glBegin(type);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();

	//Right
	glBegin(type);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
	glEnd();

	//Front
	glBegin(type);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
	glEnd();
}
void drawPyramid(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float divideX, float divideZ, GLenum type) {

	//face - back
	glBegin(type);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - top
	glBegin(type);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - bottom
	glBegin(type);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - front
	glBegin(type);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX / divideX, maxY, maxZ / divideZ);
	glEnd();

	//face - base
	glBegin(type);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(minX, minY, minZ);
	glEnd();

}
void drawSphere(float radius, int slices, int stacks) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, radius, slices, stacks);

	gluDeleteQuadric(sphere);
}
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks, float cx1, float cy1, float cz1, float cx2, float cy2, float cz2) {
	
	glColor3d(cx1, cy1, cz1);
	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();

	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, baseRadius, topRadius, height, slices, stacks);

	gluDeleteQuadric(cylinder);

	//Upper cover (same rotation with cylinder)
	glColor3d(cx2, cy2, cz2);
	drawCircle(0.0f, 0.0f, baseRadius);

	//Lower cover (not same rotation with cylinder)
	glTranslatef(0.0f, 0.0f, 0.5f);
	drawCircle(0.0f, 0.0f, topRadius);
}
void drawCircle(float xPoint, float yPoint, float radius) {
	
	glBegin(GL_TRIANGLE_FAN);
	//origin
	glVertex2f(xPoint, yPoint);

	for (float angle = 0; angle <= 360; angle += 0.1) {
		glVertex2f(xPoint + radius * cos(angle), yPoint + radius * sin(angle));
	}
	glEnd();
}
void drawLine(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	glBegin(GL_LINES);
	glVertex3f(minX, minY, minZ);
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
				bird(0.525f, 0.8f, 0.775f, 0.8f);
				bird(0.275f, 0.6f, 0.525f, 0.6f);
				bird(-0.175f, 0.75f, 0.075f, 0.75f);
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
			drawCylinder(0.5f, 0.5f, 0.5f, 30, 30, 111.0f / 255.0f, 102.0f / 255.0f, 94.0f / 255.0f, 79.0f / 255.0f, 71.0f / 255.0f, 60.0f / 255.0f);
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
			glColor3f(128.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
			glTranslatef(0.0f, 1.95f, 0.0f);
			drawPyramid(-0.29f, 0.29f, 0.006f, 0.59f, -0.29f, 0.29f, 20.0f, 20.0f, GL_TRIANGLES);
			glColor3d(165.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
			drawPyramid(-0.299f, 0.299f, 0.0055f, 0.61f, -0.29f, 0.29f, 20.0f, 20.0f, GL_LINE_LOOP);
		glPopMatrix();

		//pillar
		drawPillar(0.285f, -0.275f, 0.0f, 1.6f);
		drawPillar(-0.285f, -0.275f, 0.0f, 1.6f);
		drawPillar(0.285f, 0.275f, 0.0f, 1.6f);
		drawPillar(-0.285f, 0.275f, 0.0f, 1.6f);

		//bridge
		drawBridge(0.0f, 0.0f, 0.0f);
		drawRotateBridge(0.0f, 0.0f, 0.0f);

		glColor3f(180.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
		drawRectangle(0.34f, 1.51f, 1.5f, 1.6f, -0.2f, -0.15f, GL_QUADS);
		drawRectangle(0.34f, 1.51f, 1.5f, 1.6f, 0.15f, 0.2f, GL_QUADS);

		//bridgeLine
		bridgeLine(-1.325f, 1.6f, -0.2f, 1.65f, 1.0f);
		bridgeLine(-1.325f, 1.6f, 0.2f, 1.65f, 1.0f);

		//linker line
		//1
		drawLine(-1.4f, 0.0f, -0.2f, -1.4f, 0.6f, -0.2f);
		drawLine(-1.4f, 0.0f, 0.2f, -1.4f, 0.6f, 0.2f);
		drawLine(-1.4f, 0.6f, -0.2f, -1.4f, 0.6f, 0.2f);

		//2
		drawLine(-1.15f, 0.0f, -0.2f, -1.15f, 0.625f, -0.2f);
		drawLine(-1.15f, 0.0f, 0.2f, -1.15f, 0.625f, 0.2f);
		drawLine(-1.15f, 0.625f, -0.2f, -1.15f, 0.625f, 0.2f);

		//3
		drawLine(-0.95f, 0.0f, -0.2f, -0.95f, 0.675f, -0.2f);
		drawLine(-0.95f, 0.0f, 0.2f, -0.95f, 0.675f, 0.2f);
		drawLine(-0.95f, 0.675f, -0.2f, -0.95f, 0.675f, 0.2f);

		//4
		drawLine(-0.75f, 0.0f, -0.2f, -0.75f, 0.775f, -0.2f);
		drawLine(-0.75f, 0.0f, 0.2f, -0.75f, 0.775f, 0.2f);
		drawLine(-0.75f, 0.775f, -0.2f, -0.75f, 0.775f, 0.2f);

		//5
		drawLine(-0.5f, 0.0f, -0.2f, -0.5f, 1.05f, -0.2f);
		drawLine(-0.5f, 0.0f, 0.2f, -0.5f, 1.05f, 0.2f);
		drawLine(-0.5f, 1.05f, -0.2f, -0.5f, 1.05f, 0.2f);

	glPopMatrix();
}
void drawBuildingBase(int type) {

	glLineWidth(2.5);

	//Inner
	//front inner
	glColor3f(143.0f / 255.0f, 91.0f / 255.0f, 63.0f / 255.0f);
	drawRectangle(-0.29f, 0.29f, 0.006f, 0.349f, -0.29f, -0.21f, GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(-0.30f, 0.30f, 0.005f, 0.35f, -0.30f, -0.20f, GL_LINE_LOOP);

	//top inner
	glColor3f(143.0f / 255.0f, 91.0f / 255.0f, 63.0f / 255.0f);
	drawRectangle(-0.29f, 0.29f, 0.351f, 0.504f, -0.29f, 0.29f, GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(-0.30f, 0.30f, 0.35f, 0.505f, -0.30f, 0.30f, GL_LINE_LOOP);

	//back inner
	glColor3f(143.0f / 255.0f, 91.0f / 255.0f, 63.0f / 255.0f);
	drawRectangle(-0.29f, 0.29f, 0.0051f, 0.349f, 0.21f, 0.29f, GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(-0.30f, 0.30f, 0.005f, 0.350f, 0.20f, 0.30f, GL_LINE_LOOP);
	
	//cover
	glColor3f(118.0f / 255.0f, 62.0f / 255.0f, 35.0f / 255.0f);
	drawRectangle(-0.29f, 0.29f, 0.506f, 0.654f, -0.29f, 0.29f, GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawRectangle(-0.3001f, 0.3001f, 0.5051f, 0.6551f, -0.3001f, 0.3001f, GL_LINE_LOOP);

	if (type != 0) {

		glColor3f(143.0f / 255.0f, 91.0f / 255.0f, 63.0f / 255.0f);
		drawRectangle(-0.29f, 0.29f, 0.0051f, 0.349f, -0.19f, 0.19f, GL_QUADS);
	}
	
}
void drawPillar(float transX, float transY, float transZ1, float transZ2) {
	glPushMatrix();

		glRotatef(-90.0f, 0.5f, 0.0f, 0.0f);

		glPushMatrix();
			glTranslatef(transX, transY, transZ1);
			drawCylinder(0.05f, 0.05f, 2.1f, 25, 25, 184.0f / 255.0f, 97.0f / 255.0f, 54.0f / 255.0f, 184.0f / 255.0f, 97.0f / 255.0f, 54.0f / 255.0f);

			//roof
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, transZ2);
				drawCylinder(0.05f, 0.0f, 0.25f, 25, 25, 230.0f / 255.0f, 182.0f / 255.0f, 137.0f / 255.0f, 230.0f / 255.0f, 182.0f / 255.0f, 137.0f / 255.0f);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}
void drawBridge(float cx, float cy, float cz) {
	glPushMatrix();
		glColor3d(cx, cy, cz);
		drawRectangle(-1.5f, 0.45f, 0.005f, 0.1f, -0.2f, 0.2f, GL_QUADS);
	glPopMatrix();
}
void drawRotateBridge(float cx, float cy, float cz) {
	glPushMatrix();
		glColor3d(cx, cy, cz);

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

		drawRectangle(0.45f, 1.5f, 0.005f, 0.1f, -0.2f, 0.2f, GL_QUADS);
	glPopMatrix();
}
void bridgeLine(float lineX, float lineY, float lineZ, float a, float r) {
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);

		//left wing
		xPoint = lineX;
		yPoint = lineY;
		radius = r;

		glLineWidth(2);
		glBegin(GL_LINE_STRIP);

		for (angle = 0; angle <= a; angle += 0.01) {

			glVertex3f(xPoint + radius * cos(angle), yPoint + radius * -sin(angle), lineZ);

		}
		glEnd();
	glPopMatrix();
}

//background
void sun() {

	glColor3f(247.0f / 255.0f, 211.0f / 255.0f, 40.0f / 255.0f);

	glPushMatrix();
		glTranslatef(-1.0f, 1.0f, 0.0f);
		drawSphere(0.5f, 25, 25);
	glPopMatrix();

	sunTriangle(-0.95f, 0.475f, -0.80f, 0.50f, -0.85f, 0.30f);
	sunTriangle(-0.7f, 0.55f, -0.50f, 0.425f, -0.575f, 0.65f);
	sunTriangle(-0.475f, 0.85f, -0.525f, 0.70f, -0.275f, 0.725f);
	sunTriangle(-0.475f, 1.0f, -0.475f, 0.90f, -0.30f, 0.965f);
}
void sunTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glColor3f(227 / 255.0, 143 / 255.0, 20 / 255.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glColor3f(247 / 255.0, 211 / 255.0, 40 / 255.0);
		glVertex2f(x3, y3);
	glEnd();
}
void bird(float lineX1, float lineY1, float lineX2, float lineY2) {
	glColor3f(0.0f, 0.0f, 0.0f);

	//left wing
	xPoint1 = lineX1;
	yPoint1 = lineY1;
	radius = 0.125;

	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	for (angle = 0; angle <= 2; angle += 0.01) {

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