
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
				Cylinder * cyl = new Cylinder(vm.shapes[i].params.cyl.radius, vm.shapes[i].params.cyl.depth, vm.shapes[i].rgb[0], vm.shapes[i].rgb[1], vm.shapes[i].rgb[2], vm.shapes[i].xyz[0], vm.shapes[i].xyz[1], vm.shapes[i].xyz[2], vm.shapes[i].rotation, vm.shapes[i].params.cyl.isSteering);
				addShape(cyl);
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
};
