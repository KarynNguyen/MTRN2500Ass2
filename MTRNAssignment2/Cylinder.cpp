
#include "Cylinder.hpp"
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

Cylinder::Cylinder(double radius, double height, float red, float green, float blue) {

	//set dimensions
	radius = radius;
	height = height;
	
	//sets colour of cylinder
	setColor(red, green, blue);
}

Cylinder::draw() {
	
	static GLUquadric * quad = gluNewQuadric();
	gluQuadricNormals(quad, GLU_SMOOTH);

	gluCylinder(quad, radius, radius, height, 10, 10);
}