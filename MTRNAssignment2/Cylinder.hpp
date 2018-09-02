
#include "Shape.hpp"

//Absract Cylinder class derived from Shape

class Cylinder : public Shape
{
public:
	Cylinder(double radius, double height, float red, float green, float blue);

	double r;
	double h;

	//function to draw the cylinder
	void draw();
};
