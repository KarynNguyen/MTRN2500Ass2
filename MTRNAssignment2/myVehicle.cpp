
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

	//sets colour of prism
	setColor(red, green, blue);
};

//Note: (x,y,z) is the centre of the prism
//draws the 6 faces of the trapezoidal prism 
void myVehicle::draw() {

	// move to the vehicle’s local frame of reference
	glPushMatrix();
	positionInGL();
	// all the local drawing code

	// move back to global frame of reference
	glPopMatrix();
};

