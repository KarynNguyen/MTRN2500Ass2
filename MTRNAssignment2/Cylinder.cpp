
#include "Cylinder.hpp"
#include "Vehicle.hpp"
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

Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z) : Shape(x, y, z){

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
//draws wheels with spokes
void Cylinder::drawWheel() {

	glPushMatrix();
	setColorInGL();
	positionInGL();

	GLUquadricObj * diskWhTop = gluNewQuadric();			//cap of cylinder
	GLUquadricObj * diskWhBase = gluNewQuadric();			//base of cylinder
	GLUquadricObj * cylinderWh = gluNewQuadric();			//body of cylinder

	double theta = 45 * 3.141593f / 180;					//converts degress to radians
	double xCoord = r * cos(theta);
	double yCoord = r * sin(theta);

	//moved axis so that cylinder is level with y = 0 and is the middle of the x and z axis
	glTranslated(0, 0, -h / 2.0);

	//cap of cylinder
	gluDisk(diskWhTop, 0, r, 25, 1);

	//body of cylinder
	gluCylinder(cylinderWh, r, r, h, 20, 20);

		//horizontal spoke
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(r, 0, 0);
		glVertex3f(-r, 0, 0);
		glEnd();

		//vertical spoke
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(0, r, 0);
		glVertex3f(0, -r, 0);
		glEnd();

		//diagonal spoke 1
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(xCoord, yCoord, 0);
		glVertex3f(-xCoord, -yCoord, 0);
		glEnd();

		//diagonal spoke 2
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(-xCoord, yCoord, 0);
		glVertex3f(xCoord, -yCoord, 0);
		glEnd();

	//base of cylinder
	setColorInGL();
	glTranslated(0, 0, h);
	gluDisk(diskWhBase, 0, r, 25, 1);

		//horizontal spoke
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(r, 0, 0);
		glVertex3f(-r, 0, 0);
		glEnd();

		//vertical spoke
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(0, r, 0);
		glVertex3f(0, -r, 0);
		glEnd();

		//diagonal spoke 1
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(xCoord, -yCoord, 0);
		glVertex3f(-xCoord, yCoord, 0);
		glEnd();

		//diagonal spoke 2
		glLineWidth(3);
		glColor3f(0, 0, 0);				//black spokes
		glBegin(GL_LINES);
		glVertex3f(xCoord, yCoord, 0);
		glVertex3f(-xCoord, -yCoord, 0);
		glEnd();

		glLineWidth(1);

	glPopMatrix();

	//rotate wheels
	/*
	update(speed, dt);

	rotation = (speed*dt)/r;

	glRotated(rotation, 0, 1, 0 ); //causes overflow now...
	*/
}



