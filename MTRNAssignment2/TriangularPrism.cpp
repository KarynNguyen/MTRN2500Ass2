
#include "TriangularPrism.hpp"
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

//constructor w/o centre position or rotation
TriangularPrism::TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue) : Shape () {

	const float DEG2RAD = 3.141593f / 180;		//constant to convert from degress to radians

												//sets dimensions of prism
	base = side1;
	side = side2;
	angleInRad = angle * DEG2RAD;
	z_len = length;
	y_height = side * sin(angleInRad);			//caculating height of triangle using trigonometry

												//sets colour of prism
	setColor(red, green, blue);
};

//constructor w/o rotation
TriangularPrism::TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue, double x, double y, double z) : Shape(x, y, z) {

	const float DEG2RAD = 3.141593f / 180;		//constant to convert from degress to radians

												//sets dimensions of prism
	base = side1;
	side = side2;
	angleInRad = angle * DEG2RAD;
	z_len = length;
	y_height = side * sin(angleInRad);			//caculating height of triangle using trigonometry

	//sets colour of prism
	setColor(red, green, blue);
	positionInGL();
};

//constructor with rotation
TriangularPrism::TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue, double x, double y, double z, double rotation) : Shape(x, y, z, rotation) {
	
	const float DEG2RAD = 3.141593f / 180;		//constant to convert from degress to radians
	
	//sets dimensions of prism
	base = side1;
	side = side2;
	angleInRad = angle * DEG2RAD;
	z_len = length;
	y_height = side * sin(angleInRad);			//caculating heigght of triangle using trigonometry

	//sets colour of prism
	setColor(red, green, blue);
	positionInGL();
};

//Note: (x,y,z) is the centre of the prism
//draws the 5 faces of the triangular prism 
void TriangularPrism::draw() {

	double xCoord = side * cos(angleInRad);		//calculating x coordinate of vertex of triangle using trigonometry
	//move to TriangularPrism's local frame of reference
	glPushMatrix();
	setColorInGL();
	positionInGL();
	
	//bottom face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f(base / 2.0, 0, -z_len / 2.0);
	glVertex3f(base / 2.0, 0, z_len / 2.0);
	glVertex3f(-base / 2.0, 0, z_len / 2.0);
	glVertex3f(-base / 2.0, 0, -z_len / 2.0);
	glEnd();
	
	//left side face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f(base / 2.0, 0, -z_len / 2.0);
	glVertex3f(base / 2.0, 0, z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, -z_len / 2.0);
	glEnd();
	
	//right side face (rectangle)
	glBegin(GL_QUADS);
	glVertex3f( -base / 2.0, 0, -z_len / 2.0);
	glVertex3f(-base / 2.0, 0, z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, -z_len / 2.0);
	glEnd();
	
	//back face (triangle)
	glBegin(GL_TRIANGLES);
	glVertex3f(base / 2.0, 0, -z_len / 2.0);
	glVertex3f(-base / 2.0, 0, -z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, -z_len / 2.0);
	glEnd();
	
	//front face (triangle)
	glBegin(GL_TRIANGLES);
	glVertex3f(base / 2.0, 0, z_len / 2.0);
	glVertex3f(-base / 2.0, 0, z_len / 2.0);
	glVertex3f(-(base / 2.0) + xCoord, y_height, z_len / 2.0);
	glEnd();
	
	glPopMatrix();
};

