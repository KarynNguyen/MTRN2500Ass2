
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

RectangularPrism::RectangularPrism(double length, double width, double depth, float red, float green, float blue) {
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

	setColorInGL();
	positionInGL();

	glPushMatrix();
	glTranslated(x_len/2.0, 0, z_len/2.0);

	//bottom face
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z_len);
	glVertex3f(-x_len, 0, -z_len);
	glVertex3f(-x_len, 0,  0);
	glEnd();
	
	//top face
	glBegin(GL_QUADS);
	glVertex3f(0, y_len, 0);
	glVertex3f(0, y_len, -z_len);
	glVertex3f(-x_len, y_len, -z_len);
	glVertex3f(-x_len, y_len,  0);
	glEnd();
	
	//left side face
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z_len);
	glVertex3f(0, y_len, -z_len);
	glVertex3f(0, y_len,  0);
	glEnd();
	
	//right side face
	glBegin(GL_QUADS);
	glVertex3f(-x_len, 0, 0);
	glVertex3f(-x_len, 0, -z_len);
	glVertex3f(-x_len, y_len, -z_len);
	glVertex3f(-x_len, y_len,  0);
	glEnd();

	//front face
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -z_len);
	glVertex3f(-x_len, 0, -z_len);
	glVertex3f(-x_len, y_len, -z_len);
	glVertex3f(0, y_len, -z_len);
	glEnd();

	//back face
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(-x_len, 0, 0);
	glVertex3f(-x_len, y_len, 0);
	glVertex3f(0, y_len, 0);
	glEnd();
	
	glPopMatrix();
};
