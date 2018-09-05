
#include "Shape.hpp"

//Absract TriangularPrism class derived from Shape

class TriangularPrism : public Shape
{
public:
	TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue);					//constructor w/o centre position or rotation
	TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue, double x, double y, double z);			//constructor w/o rotation
	TriangularPrism(double side1, double side2, double angle, double length, float red, float green, float blue, double x, double y, double z, double rotation);			//constructor with rotation
	
	//dimensions of triangular prism
	double base;
	double side;
	double angleInRad;
	double z_len;
	double y_height;

	//function to draw the triangular prism
	void draw();

};
