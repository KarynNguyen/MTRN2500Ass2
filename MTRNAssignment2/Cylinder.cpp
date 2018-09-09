
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

Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z) {

	//set dimensions
	r = radius;
	h = height;
	
	//sets colour of cylinder
	setColor(red, green, blue);
}

Cylinder::Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation) {

	//set dimensions
	r = radius;
	h = height;

	//sets colour of cylinder
	setColor(red, green, blue);
}


//draw function
void Cylinder::draw() {
	
	GLUquadricObj * disk1 = gluNewQuadric();			//cap of cylinder
	GLUquadricObj * disk2 = gluNewQuadric();			//base of cylinder
	GLUquadricObj * cylinder = gluNewQuadric();			//body of cylinder

	glPushMatrix();
	setColorInGL();
	positionInGL();

	//moved axis so that cylinder is level with y = 0 and is the middle of the x and z axis
	glTranslated(0, r, -h/2.0);

	//cap of cylinder
	gluDisk(disk1, 0, r, 25, 1);
	
	//body of cylinder
	gluCylinder(cylinder, r, r, h, 20, 20);
	
	//base of cylinder
	glTranslated(0, 0, h);
	gluDisk(disk2, 0, r, 25, 1);

	glPopMatrix();
}

void Cylinder::drawWheel() {

	GLUquadricObj * disk1 = gluNewQuadric();			//cap of cylinder
	GLUquadricObj * disk2 = gluNewQuadric();			//base of cylinder
	GLUquadricObj * cylinder = gluNewQuadric();			//body of cylinder

	glPushMatrix();
	setColorInGL();
	positionInGL();

	//moved axis so that cylinder is level with y = 0 and is the middle of the x and z axis
	glTranslated(0, r, -h / 2.0);

	//cap of cylinder
	gluDisk(disk1, 0, r, 25, 1);

	//body of cylinder
	gluCylinder(cylinder, r, r, h, 20, 20);

		//horizontal spoke
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, 0, 0);
		glVertex3f(-r, 0, 0);
		glEnd();

		//vertical spoke
		glLineWidth(1);
		glColor3f(0, 0, 0);//black spokes
		glBegin(GL_LINES);
		glVertex3f(0, r, 0);
		glVertex3f(0, -r, 0);
		glEnd();

		//diagonal spoke 1
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, -r, 0);
		glVertex3f(-r, r, 0);
		glEnd();

		//diagonal spoke 2
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, r, 0);
		glVertex3f(-r, -r, 0);
		glEnd();


	//base of cylinder
	glTranslated(0, 0, h);
	gluDisk(disk2, 0, r, 25, 1);

		//horizontal spoke
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, 0, 0);
		glVertex3f(-r, 0, 0);
		glEnd();

		//vertical spoke
		glLineWidth(1);
		glColor3f(0, 0, 0);//black spokes
		glBegin(GL_LINES);
		glVertex3f(0, r, 0);
		glVertex3f(0, -r, 0);
		glEnd();

		//diagonal spoke 1
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, -r, 0);
		glVertex3f(-r, r, 0);
		glEnd();

		//diagonal spoke 2
		glLineWidth(1);
		glColor3f(0, 0, 0); //black spokes
		glBegin(GL_LINES);
		glVertex3f(r, r, 0);
		glVertex3f(-r, -r, 0);
		glEnd();

	glPopMatrix();
}

