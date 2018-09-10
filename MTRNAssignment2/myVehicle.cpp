
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
	glPushMatrix();

	glPopMatrix();

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
	double radius_b = 0.5;
	double radius_f = 0.5;
	double depth = 0.5;

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
	TrapPrism trapTop(trap_a, trap_b, trap_h, trap_depth, trap_off, 1, 0, 0, 0, rect_w, 0, 0);		//blue top
	trapTop.draw();
	glPopMatrix();
	
	//draw left front wheels (closed solid cylinder)
	glPushMatrix();
	Cylinder flWheel(radius_f, depth, 1, 1, 1, 1.2 , 0, -rect_d/2.0, 0);		//white front wheels
	flWheel.drawWheel();
	glPopMatrix();

	//draw right front wheel (closed solid cylinder)
	glPushMatrix();
	Cylinder frWheel(radius_f, depth, 1, 1, 1, 1.2, 0, rect_d/2.0, 0);		//white front wheels
	frWheel.drawWheel();
	glPopMatrix();
	
	
	//draw right back wheel (closed solid cylinder)
	glPushMatrix();
	Cylinder brWheel(radius_b, depth, 1, 1, 1, -1.2, 0, rect_d/2.0, 0);		//white back wheels
	brWheel.drawWheel();
	glPopMatrix();

	//draw left back wheel (closed solid cylinder)
	glPushMatrix();
	Cylinder blWheel(radius_b, depth, 1, 1, 1, -1.2, 0, -rect_d/2.0, 0);		//white back wheels
	blWheel.drawWheel();
	glPopMatrix();
	
	//draw lights on top (triangluar prism)
	glPushMatrix();
	TriangularPrism triTop(side, base, angle, tri_depth, 0, 0, 1, 0, rect_w + trap_h, 0, 0);		//blue lights on top
	triTop.draw();
	glPopMatrix();

	// move back to global frame of reference
	glPopMatrix();
}




