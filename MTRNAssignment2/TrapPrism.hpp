
#include "Shape.hpp"

//Absract Traprezoidal prism class derived from Shape

class TrapPrism : public Shape
{
public:
	TrapPrism(double a_length, double b_length, double height, double depth, double a_offset, float red, float green, float blue);			//constructor

	//dimensions of triangular prism
	double a_len;
	double b_len;
	double y_height;
	double z_depth;
	double a_off;

	//function to draw the triangular prism
	void draw();

};
