#include "drawing.h"

// Function that simulates putting a pixel to string,
// using GL_POINTS from OpenGL
// Args:
// 		x: x ccordinate of the pixel
// 		y: y coordinate of the pixel
void putpixel(int x, int y) {
	glBegin(GL_POINTS);
		glVertex3f((float)x, (float)y, 0);
	glEnd();
}

// Function that puts a point in 3d space
// Args:
// 		x, y, z: coordinates of the point
void fputpixel(float x, float y, float z) {
	glBegin(GL_POINTS);
	//glBegin(GL_LINE_STRIP);
		glColor4f(0.49, 1.0, 0.999, 0.5);
		glVertex3f(x, y, z);
	glEnd();
}
