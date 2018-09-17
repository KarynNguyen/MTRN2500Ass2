
#include "RectangularPrism.hpp"
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//constructor w/o centre position or rotation
RectangularPrism::RectangularPrism(double length, double width, double depth, float red, float green, float blue) : Shape() {
	//sets dimensions of prism
	x_len = length;
	y_len = width;
	z_len = depth;

	//sets colour of prism
	setColor(red, green, blue);
};

//constructor w/o rotation
RectangularPrism::RectangularPrism(double length, double width, double depth, float red, float green, float blue, double x, double y, double z) : Shape(x, y, z) {
	//sets dimensions of prism
	x_len = length;
	y_len = width;
	z_len = depth;

	//sets colour of prism
	setColor(red, green, blue);
};

//constructor with rotation
RectangularPrism::RectangularPrism(double length, double width, double depth, float red, float green, float blue, double x, double y, double z, double rotation) : Shape(x, y, z, rotation) {
	//sets dimensions of prism
	x_len = length;
	y_len = width;
	z_len = depth;

	//sets colour of prism
	setColor(red, green, blue);
};

//Note: (x,y,z) is the centre of the prism
//draws the 6 faces of the rectangular prism 
void RectangularPrism::draw() {
	//move to RectangularPrism's local frame of reference
	glPushMatrix();
	setColorInGL();
	positionInGL();

	//bottom face
	glBegin(GL_QUADS);
	glVertex3f(x_len / 2.0, 0, -z_len / 2.0);
	glVertex3f(x_len / 2.0, 0, z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, -z_len / 2.0);
	glEnd();

	//top face
	glBegin(GL_QUADS);
	glVertex3f(x_len / 2.0, y_len, -z_len / 2.0);
	glVertex3f(x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(-x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(-x_len / 2.0, y_len, -z_len / 2.0);
	glEnd();

	//left side face
	glBegin(GL_QUADS);
	glVertex3f(x_len / 2.0, y_len, -z_len / 2.0);
	glVertex3f(x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(x_len / 2.0, 0, z_len / 2.0);
	glVertex3f(x_len / 2.0, 0, -z_len / 2.0);
	glEnd();

	//right side face
	glBegin(GL_QUADS);
	glVertex3f(-x_len / 2.0, y_len, -z_len / 2.0);
	glVertex3f(-x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, -z_len / 2.0);
	glEnd();

	//front face
	glBegin(GL_QUADS);
	glVertex3f(x_len / 2.0, y_len, -z_len / 2.0);
	glVertex3f(-x_len / 2.0, y_len, -z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, -z_len / 2.0);
	glVertex3f(x_len / 2.0, 0, -z_len / 2.0);
	glEnd();

	//back face
	glBegin(GL_QUADS);
	glVertex3f(x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(-x_len / 2.0, y_len, z_len / 2.0);
	glVertex3f(-x_len / 2.0, 0, z_len / 2.0);
	glVertex3f(x_len / 2.0, 0, z_len / 2.0);
	glEnd();

	glPopMatrix();
};