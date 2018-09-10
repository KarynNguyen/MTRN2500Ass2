
#include "Vehicle.hpp"
#include "RectangularPrism.hpp"
#include "TriangularPrism.hpp"
#include "TrapPrism.hpp"
#include "Cylinder.hpp"

//Absract myVehicle class derived from Vehicle
class myVehicle : public Vehicle
{
public:
	myVehicle();			//constructor

	//function to draw the custom vehicle
	void draw();
	void update(double speed_, double dt);
	double dt;
	double speed;


};

