
#include "Cylinder.hpp"
#include "Vehicle.hpp"
#include <cmath>
#include <iostream>
#include "Windows.h"

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

Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z) : Shape(x, y, z) {
	//set dimensions
	r = radius;
	h = height;
	
	//sets colour of cylinder
	setColor(red, green, blue);
}

//wheel cylinder constructor
Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation) : Shape(x, y, z, rotation) {

	//set dimensions
	r = radius;
	h = height;
	rotating = rotation; 

	//sets colour of cylinder
	setColor(red, green, blue);
}

Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation, bool steering) : Shape(x, y, z, rotation) {

	//set dimensions
	r = radius;
	h = height;
	rotating = rotation;
	curSteering = steering; 
	curRotating = true;

	//sets colour of cylinder
	setColor(red, green, blue);
}

//draw function
void Cylinder::draw() {

	glPushMatrix();
	setColorInGL();
	positionInGL();

	GLUquadricObj * diskCylTop = gluNewQuadric();			//cap of cylinder
	GLUquadricObj * diskCylBase = gluNewQuadric();			//base of cylinder
	GLUquadricObj * cylinder = gluNewQuadric();			//body of cylinder
	
	//moved axis so that cylinder is level with y = 0 and is the middle of the x and z axis
	glTranslated(0, r, -h/2.0);
	
	//cap of cylinder
	gluDisk(diskCylTop, 0, r, 25, 1);
	
	//body of cylinder
	gluCylinder(cylinder, r, r, h, 20, 20);
	
	//base of cylinder
	glTranslated(0, 0, h);
	gluDisk(diskCylBase, 0, r, 25, 1);

	glPopMatrix();
}

double Cylinder::getSpeed(double speed) {
	return speed;
}

double Cylinder::getTime2()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}



//draws wheels with spokes
void Cylinder::drawWheel(double speed) {

	const float DEG2RAD = 3.141593f / 180;
	const float RAD2DEG = 180 / 3.141593f;
	
	glPushMatrix();

	//draws wheels
	glPushMatrix();
	setColorInGL();
	positionInGL();

	GLUquadricObj * diskWhTop = gluNewQuadric();			//cap of cylinder
	GLUquadricObj * diskWhBase = gluNewQuadric();			//base of cylinder
	GLUquadricObj * cylinderWh = gluNewQuadric();			//body of cylinder

	double theta = 45 * DEG2RAD;					//converts degress to radians
	double xCoord = r * cos(theta);
	double yCoord = r * sin(theta);

	//moved axis so that cylinder is level with y = 0 and is the middle of the x and z axis
	glTranslated(0, r, -h / 2.0);

	//cap of cylinder
	gluDisk(diskWhTop, 0, r, 25, 1);

	//body of cylinder
	gluCylinder(cylinderWh, r, r, h, 20, 20);

	//base of cylinder
	setColorInGL();
	glTranslated(0, 0, h);
	gluDisk(diskWhBase, 0, r, 25, 1);

	glPopMatrix();
	
	//does rotation of wheels
	double oldTime = 0.0;

	double currTime = glutGet(GLUT_ELAPSED_TIME);			//gets the time since glut init was called (in milliseconds)
	currTime = currTime / 1000;								//changes from milliseconds to seconds
	double dt = currTime - oldTime;							//calculated change in time	
	oldTime = currTime;										//sets the current time as the new time

	rotation1 = ((speed*dt) / r) * RAD2DEG;					//converts angle of rotation to radians
	glRotated(rotation1, 0, 0, -1);							//rotates wheel according to angular velocity calculated


	//draws spokes 
	glPushMatrix();

	/*glTranslated(0, r, -h / 2.0);

	//cap of cylinder
	gluDisk(diskWhTop, 0, r, 25, 1);

	//body of cylinder
	gluCylinder(cylinderWh, r, r, h, 20, 20);

	//base of cylinder
	setColorInGL();
	glTranslated(0, 0, h);
	gluDisk(diskWhBase, 0, r, 25, 1);
	glTranslated();*/

	//horizontal spoke
	glLineWidth(5);
	glColor3f(0.4, 0.3, 0.2);				//black spokes
	glBegin(GL_LINES);
	glVertex3f(r, 0, 0);
	glVertex3f(-r, 0, 0);
	glEnd();

	//horizontal spoke
	glLineWidth(5);
	glColor3f(0.4, 0.3, 0.2);				//black spokes
	glBegin(GL_LINES);
	glVertex3f(r, 0, 0);
	glVertex3f(-r, 0, 0);
	glEnd();

	glLineWidth(1);

	glPopMatrix();

	glPopMatrix();
}

