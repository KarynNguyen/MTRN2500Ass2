
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
	Cylinder * frontLWheel = new Cylinder(0.5, 1.0, 1, 1, 1, 1.2, 0, 1.25, 1, 1);
	Cylinder * frontRWheel = new Cylinder(0.5, 1.0, 1, 1, 1, 1.2, 0,-1.25, 1, 1);
	Cylinder * backRWheel = new Cylinder(0.5, 1.0, 1, 1, 1, -1.2, 0,-1.25, 1, 0);
	Cylinder * backLWheel = new Cylinder(0.5, 1.0, 1, 1, 1, -1.2, 0, 1.25, 1, 0);

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
	for (int i = 0; i < vm.shapes.size(); i++) 
	{
		switch (vm.shapes[i].type)
		{
			case RECTANGULAR_PRISM:
			{
				RectangularPrism * rect = new RectangularPrism(vm.shapes[i].params.rect.xlen, vm.shapes[i].params.rect.ylen, vm.shapes[i].params.rect.zlen, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation);
				addShape(rect);
			} 
			break;
			case TRIANGULAR_PRISM:
			{
				TriangularPrism * tri = new TriangularPrism(vm.shapes[i].params.tri.alen, vm.shapes[i].params.tri.blen, vm.shapes[i].params.tri.angle, vm.shapes[i].params.tri.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation);
				addShape(tri);
			}
			break;
			case TRAPEZOIDAL_PRISM:
			{
				TrapPrism * trap = new TrapPrism(vm.shapes[i].params.trap.alen, vm.shapes[i].params.trap.blen, vm.shapes[i].params.trap.height, vm.shapes[i].params.trap.depth, vm.shapes[i].params.trap.aoff, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation);
				addShape(trap);
			}
			break;
			case CYLINDER:
			{
				if (!(vm.shapes[i].params.cyl.isRolling)) {
					Cylinder * cyl = new Cylinder(vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
					addShape(cyl);
				}
				else {
					Cylinder * cylWheel = new Cylinder(vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation);
					addShape(cylWheel);
				}
				if (!(vm.shapes[i].params.cyl.isSteering)) {
					Cylinder * cyl = new Cylinder(vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2]);
					addShape(cyl);
				}
				else {
					Cylinder * cyl = new Cylinder(vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation, vm.shapes[i].params.cyl.isSteering);
					addShape(cyl);
				}
			}
			break;

		default:
			break;
		}

	}
	

};

double myVehicle::getTime2()
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

//Note: (x,y,z) is the centre of the prism
//draws the 6 faces of the trapezoidal prism 
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
			if (cyl->curRotating == true)
			{
				//cyl->getSpeed(speed);

				if (cyl->curSteering == true) {

					cyl->setRotation(steering);
				
				}

			cyl->drawWheel();
			}
		}
		else {
			(*it)->draw();
		}
		glPopMatrix();
	}
	
	/*
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
	glRotated(-getSteering(), 0, 1, 0);			//do steering of wheels as car is turning
	Cylinder flWheel(radius_f, depth, 1, 1, 1, 1.2 , 0, -rect_d/2.0, 0);		//white front wheels
	flWheel.drawWheel();
	glPopMatrix();

	//draw right front wheel (closed solid cylinder)
	glPushMatrix();
	glRotated(-getSteering(), 0, 1, 0);			//do steering of wheels as car is turning
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
	glPopMatrix();	*/
};
