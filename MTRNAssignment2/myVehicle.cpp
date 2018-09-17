
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

//constructor for custom car 
myVehicle::myVehicle() {
	
	//create pointers to custom behicle shapes to be added to shapes vector
	RectangularPrism * body = new RectangularPrism(4, 1.75, 2.5, 1, 0, 0, 0, 0.5, 0, 0);
	TrapPrism * top = new TrapPrism(2.0, 1.0, 1.0, 2.5, 0.5, 1.0, 0, 0, 0, 2.25, 0, 0); 
	TriangularPrism * topLight = new TriangularPrism(0.5, 0.5, 60, 2.5, 0, 0, 1.0, 0, 3.25, 0, 0);
	Cylinder * frontLWheel = new Cylinder(0.5, 1.0, 1, 1, 1, 1.2, 0, 1.25, 0, 1);
	Cylinder * frontRWheel = new Cylinder(0.5, 1.0, 1, 1, 1, 1.2, 0,-1.25, 0, 1);
	Cylinder * backRWheel = new Cylinder(0.5, 1.0, 1, 1, 1, -1.2, 0,-1.25, 0, 0);
	Cylinder * backLWheel = new Cylinder(0.5, 1.0, 1, 1, 1, -1.2, 0, 1.25, 0, 0);

	//add shapes to shape vector to be drawn
	addShape(body);
	addShape(top);
	addShape(topLight);
	addShape(frontLWheel);
	addShape(frontRWheel);
	addShape(backLWheel);
	addShape(backRWheel);
	
};

//constructor for other vehicles
myVehicle::myVehicle(VehicleModel vm) {

	std::vector<ShapeInit>::iterator it;

	for (it = vm.shapes.begin(); it != vm.shapes.end(); it++) 
	{
		switch (it->type)
		{
			case RECTANGULAR_PRISM:
			{
				RectangularPrism * rect = new RectangularPrism(it->params.rect.xlen, it->params.rect.ylen, it->params.rect.zlen, it->xyz[0], it->xyz[1], it->xyz[2], it->rgb[0], it->rgb[1], it->rgb[2], it->rotation);
				addShape(rect);
			} 
			break;
			case TRIANGULAR_PRISM:
			{
				TriangularPrism * tri = new TriangularPrism(it->params.tri.alen, it->params.tri.blen, it->params.tri.angle, it->params.tri.depth, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
				addShape(tri);
			}
			break;
			case TRAPEZOIDAL_PRISM:
			{
				TrapPrism * trap = new TrapPrism(it->params.trap.alen, it->params.trap.blen, it->params.trap.height, it->params.trap.depth, it->params.trap.aoff, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
				addShape(trap);
			}
			break;
			case CYLINDER:
			{
				if (!(it->params.cyl.isRolling)) {
					Cylinder * cyl = new Cylinder(it->params.cyl.radius, it->params.cyl.depth, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation);
					addShape(cyl);
				}
				else {
					Cylinder * cylWheel = new Cylinder(it->params.cyl.radius, it->params.cyl.depth, it->rgb[0], it->rgb[1], it->rgb[2], it->xyz[0], it->xyz[1], it->xyz[2], it->rotation, it->params.cyl.isSteering);
					addShape(cylWheel);
				}
			}
			break;

		default:
			break;
		}
	}
};

//draws the vehicle
void myVehicle::draw() {

	std::vector<Shape * >::iterator it;

	for (it = shapes.begin(); it != shapes.end(); ++it)
	{
		glPushMatrix();

		positionInGL();
		//check if shape pointer is holding a cylinder, then check if its a wheel set rotation to steering value and implement rotation speed
		Cylinder * cyl = dynamic_cast<Cylinder *>(*it);
		if (cyl != nullptr)
		{
			if (cyl->curRotating == true) {				//cylinder is a wheel and hence rotates
				if (cyl->curSteering == true)				//determines whether or not it is a front wheel ad sets steering
				{
					cyl->setRotation(steering);
				}
				cyl->drawWheel();
				//cyl->setSpeed(speed);
			}
		}
		else {
			(*it)->draw();
		}
		glPopMatrix();
	}
};




