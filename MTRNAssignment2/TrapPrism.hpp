
#include "Shape.hpp"

//Absract Traprezoidal prism class derived from Shape

class TrapPrism : public Shape
{
public:
	TrapPrism(double a_length, double b_length, double height, double depth, double a_offset, float red, float green, float blue);			//constructor w/o centre position or rotation
	TrapPrism(double a_length, double b_length, double height, double depth, double a_offset, float red, float green, float blue, double x, double y, double z);			//constructor w/o rotation
	TrapPrism(double a_length, double b_length, double height, double depth, double a_offset, float red, float green, float blue, double x, double y, double z, double rotation);			//constructor with rotation

	//dimensions of triangular prism
	double a_len;
	double b_len;
	double y_height;
	double z_depth;
	double a_off;

	//function to draw the triangular prism
	void draw();

};
