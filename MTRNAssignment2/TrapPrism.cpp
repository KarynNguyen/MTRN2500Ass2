
#include "TrapPrism.hpp"
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#endif

TrapPrism::TrapPrism(double a_length, double b_length, double height, double depth, double a_offset, float red, float green, float blue) {

	//sets dimensions of prism
	a_len = a_length;
	b_len = b_length;
	y_height = height;
	z_depth = depth;
	a_off = a_offset;
	
	//sets colour of prism
	setColor(red, green, blue);
};

//Note: (x,y,z) is the centre of the prism
//draws the 6 faces of the trapezoidal prism 
void TrapPrism::draw() {
	//move to TrapPrism's local frame of reference
	glPushMatrix();
	setColorInGL();
	positionInGL();
	glTranslated(a_len / 2.0, 0, z_depth / 2.0);

	//bottom face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z_depth);
	glVertex3f(-a_len, 0, -z_depth);
	glVertex3f(-a_len, 0, 0);
	glEnd();

	//top face(rectangle)
	glBegin(GL_QUADS);
	glVertex3f(-a_off, y_height, 0);
	glVertex3f(-a_off, y_height, -z_depth);
	glVertex3f(-(a_off + b_len), y_height, -z_depth);
	glVertex3f(-(a_off + b_len), y_height, 0);
	glEnd();
	
	//left side face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z_depth);
	glVertex3f(-a_off, y_height, -z_depth);
	glVertex3f(-a_off, y_height, 0);
	glEnd();
	
	//right side face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f(-(a_off + b_len), y_height, 0);
	glVertex3f(-(a_off + b_len), y_height, -z_depth);
	glVertex3f(-a_len, 0, -z_depth);
	glVertex3f(-a_len, 0, 0);
	glEnd();
	
	//back face (trapezium)
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(-a_len, 0, 0);
	glVertex3f(-(a_off + b_len), y_height, 0);
	glVertex3f(-a_off, y_height, 0);
	glEnd();
	
	//front face (trapezium)
	glBegin(GL_QUADS);
	glVertex3f(0, 0, -z_depth);
	glVertex3f(-a_len, 0, -z_depth);
	glVertex3f(-(a_off + b_len), y_height, -z_depth);
	glVertex3f(-a_off, y_height, -z_depth);
	glEnd();
	
	glPopMatrix();
};

