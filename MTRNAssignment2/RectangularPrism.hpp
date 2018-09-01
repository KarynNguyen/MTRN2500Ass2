
#include "Shape.hpp"

//Absract RectangularPrism class derived from Shape

class RectangularPrism : public Shape
{
public:
	RectangularPrism(double length, double width, double depth, float red, float green, float blue);			//constructor

																												//dimensions of rectangular prism
	double x_len;
	double y_len;
	double z_len;

	//function to draw the rectangular prism
	void draw();

};
