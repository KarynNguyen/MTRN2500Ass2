
#include "Vehicle.hpp"
#include "Messages.hpp"
#include "RectangularPrism.hpp"
#include "TriangularPrism.hpp"
#include "TrapPrism.hpp"
#include "Cylinder.hpp"

//Absract myVehicle class derived from Vehicle
class myVehicle : public Vehicle
{
public:
	myVehicle();					//constructor with no arguments passed in
	myVehicle(VehicleModel vm);		//constructor with VehicleModel passed in (used to draw other vehicles)

	//function to draw the custom vehicle
	void draw();
	//void update(double speed_, double dt);
	//double dt;
	//double speed;


};

