
#include "Shape.hpp"

//Absract Cylinder class derived from Shape

class Cylinder : public Shape
{
public:
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z);
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation);

	double r;
	double h;

	//function to draw the cylinder
	void draw();
	void drawWheel();
};
