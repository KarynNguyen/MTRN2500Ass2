
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
	//glPushMatrix();
	setColorInGL();
	positionInGL();

	double xCoordPos = getX() + x_len / 2.0;		//x coordinate in positive direction
	double xCoordNeg = getX() - x_len / 2.0;		//x coordinate in negative direction
	double yCoordPos = getY() + y_len / 2.0;		//y coordinate in positive direction
	double yCoordNeg = getY() - y_len / 2.0;		//y coordinate in negative direction
	double zCoordPos = getZ() + z_len / 2.0;		//z coordinate in positive direction
	double zCoordNeg = getZ() - z_len / 2.0;		//z coordinate in negative direction

													//top face
	glBegin(GL_QUADS);
	glVertex3f(xCoordPos, yCoordPos, zCoordPos);
	glVertex3f(xCoordPos, yCoordPos, zCoordNeg);
	glVertex3f(xCoordNeg, yCoordPos, zCoordNeg);
	glVertex3f(xCoordNeg, yCoordPos, zCoordPos);
	glEnd();

	//bottom face
	glBegin(GL_QUADS);
	glVertex3f(xCoordPos, yCoordNeg, zCoordPos);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordPos);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordNeg);
	glVertex3f(xCoordPos, yCoordNeg, zCoordNeg);
	glEnd();


	//left side face
	glBegin(GL_QUADS);
	glVertex3f(xCoordPos, yCoordPos, zCoordPos);
	glVertex3f(xCoordPos, yCoordNeg, zCoordPos);
	glVertex3f(xCoordPos, yCoordNeg, zCoordNeg);
	glVertex3f(xCoordPos, yCoordPos, zCoordNeg);
	glEnd();

	//right side face
	glBegin(GL_QUADS);
	glVertex3f(xCoordNeg, yCoordPos, zCoordPos);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordPos);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordNeg);
	glVertex3f(xCoordNeg, yCoordPos, zCoordNeg);
	glEnd();

	//front face
	glBegin(GL_QUADS);
	glVertex3f(xCoordPos, yCoordPos, zCoordPos);
	glVertex3f(xCoordPos, yCoordNeg, zCoordPos);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordPos);
	glVertex3f(xCoordNeg, yCoordPos, zCoordPos);
	glEnd();

	//back face
	glBegin(GL_QUADS);
	glVertex3f(xCoordPos, yCoordPos, zCoordNeg);
	glVertex3f(xCoordPos, yCoordNeg, zCoordNeg);
	glVertex3f(xCoordNeg, yCoordNeg, zCoordNeg);
	glVertex3f(xCoordNeg, yCoordPos, zCoordNeg);
	glEnd();

	//glPopMatrix();
};
