
#include "Shape.hpp"

//Absract Cylinder class derived from Shape

class Cylinder : public Shape
{
public:
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z);
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation);
	Cylinder(double radius, double height, float red, float green, float blue, double x, double y, double z, double rotation, bool steering);

	
	//void update(double speed_, double dt);
	double r;
	double h;

	bool curSteering;
	bool curRotating;
	double rotating;
	/*double speed;
	double dt;
	double rotation;*/

	//function to draw the cylinder
	void draw();
	void drawWheel();

	double rotation1;
	double getTime2();


	double getSpeed(double speed);
};
