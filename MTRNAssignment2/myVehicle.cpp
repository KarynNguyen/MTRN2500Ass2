
#include "myVehicle.hpp"
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

myVehicle::myVehicle() {

};

//Note: (x,y,z) is the centre of the prism
//draws the 6 faces of the trapezoidal prism 
void myVehicle::draw() {
	//dimensions of rectangle base
	double rect_l = 4.0;
	double rect_w = 1.75;
	double rect_d = 2.5;

	//dimensions of trapezoidal top
	double trap_a = 2.0;
	double trap_b = 1.0;
	double trap_h = 1.0;
	double trap_off = 0.5;
	double trap_depth = 2.5;

	//dimensions of cylindrical wheels
	double radius = 0.5;
	double depth = 2.5;

	//dimensions of triangular prism on top of head
	double side = 0.5;
	double base = 0.5;
	double angle = 60;
	double tri_depth = 2.5;

	// move to the vehicle’s local frame of reference
	glPushMatrix();
	positionInGL();
	// all the local drawing code

	//draw rectangular prism body of vehicle
	glPushMatrix();
	RectangularPrism rectBody(rect_l, rect_w, rect_d, 1, 0, 0, 0, 0 ,0, 0);		//red body
	rectBody.draw();
	glPopMatrix();
	
	//draw trapezoidal prism on top of body
	glPushMatrix();
	glTranslated(0, rect_w, 0);
	TrapPrism trapTop(trap_a, trap_b, trap_h, trap_depth, trap_off, 1, 0, 0, 0, 0, 0, 0);		//blue top
	trapTop.draw();
	glPopMatrix();

	//draw front wheels (closed solid cylinder)
	glPushMatrix();
	glTranslated(1.0, -0.5, 0);
	Cylinder fWheel(radius, depth, 1, 1, 1, 0 ,0 ,0, 0);		//white front wheels
	fWheel.draw();
	glPopMatrix();

	//draw back wheels (closed solid cylinder)
	glPushMatrix();
	glTranslated(-1.0, -0.5, 0);
	Cylinder bWheel(radius, depth, 1, 1, 1, 0, 0, 0, 0);		//white back wheels
	bWheel.draw();
	glPopMatrix();

	//draw lights on top (triangluar prism)
	glPushMatrix();
	glTranslated(0, rect_w + trap_h, 0);
	TriangularPrism triSpoilerBase(side, base, angle, tri_depth, 0, 0, 1, 0, 0, 0, 0);		//blue lights on top
	triSpoilerBase.draw();
	glPopMatrix();

	// move back to global frame of reference
	glPopMatrix();
};

