
#include "Shape.hpp"

//Absract Cylinder class derived from Shape

class Cylinder : public Shape
{
public:
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z);
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation);

	
	void update(double speed_, double dt);
	double r;
	double h;
	double speed;
	double dt;
	double rotation;

	//function to draw the cylinder
	void draw();
	void drawWheel();
};
