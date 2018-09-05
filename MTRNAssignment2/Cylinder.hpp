
#include "Shape.hpp"

//Absract Cylinder class derived from Shape

class Cylinder : public Shape
{
public:
	Cylinder(double radius, double height, float red, float green, float blue);		//constructor w/o centre position or rotation
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z);		//constructor w/o rotation
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation);		//constructor with rotation

	double r;
	double h;

	//function to draw the cylinder
	void draw();
};
