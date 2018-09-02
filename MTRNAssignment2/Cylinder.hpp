
#include "Shape.hpp"

//Absract RectangularPrism class derived from Shape

class Cylinder : public Shape
{

	Cylinder(double radius, double height, float red, float green, float blue);

	double radius;
	double height;

	//function to draw the cylinder
	void draw();
};
