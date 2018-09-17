//XBoxController.cpp
//By: Karyn Nguyen (z5160445)

#include <iostream>
#include <Windows.h>
#include <math.h>
#include "XBoxController.h"
#include "XInputWrapper.h"

#define MAX_VALUE 32767			//Maximum x-coordinate/y-coordinate possible for left and right thumbsticks
#define DEFAULT 0				//Initial deadzone radius value of zero

//constructor
GamePad::XBoxController::XBoxController(XInputWrapper* xinput, DWORD id)
{
	this->xinput = xinput;			
	this->deadzone = DEFAULT;				//set deadzone to initial value of zero
	ControllerId = id;
}

DWORD GamePad::XBoxController::GetControllerId()
{
	return ControllerId;
}

bool GamePad::XBoxController::IsConnected()
{
	return ((xinput->XInputGetState(ControllerId, &State) == ERROR_SUCCESS));	//Retrieve and return state of controller
}

bool GamePad::XBoxController::PressedA() 
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller 
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_A)		//bitmask (0x1000) to check whether button A is being pressed 
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedB()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_B)		//bitmask (0x2000) to check whether button B is being pressed 
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedX()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_X)		//bitmask (0x4000) to check whether button X is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedY()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_Y)		//bitmask (0x8000) to check whether button Y is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedLeftShoulder()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)		//bitmask (0x0100) to check whether left shoulder is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedRightShoulder()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)		//bitmask (0x0200) to check whether rigth shoulder is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedLeftDpad()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)		//bitmask to (0x0004) check whether left pad is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedRightDpad()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)		//bitmask (0x0008) to check whether right is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedUpDpad()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)		//bitmask (0x0001) to check whether up is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedDownDpad()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)		//bitmask (0x0002) to check whether down is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedStart()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_START)		//bitmask (0x0010) to check whether start button is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedBack()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)		//bitmask (0x0020) to check whether back button is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedLeftThumb()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)		//bitmask (0x0040) to check whether left thumb is being pressed
		return true;
	else
		return false;
}

bool GamePad::XBoxController::PressedRightThumb()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	if (State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)		//bitmask (0x0080) to check whether right thumb is being pressed
		return true;
	else
		return false;
}

BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller

	return State.Gamepad.bLeftTrigger;					//returns a value between 0 and 255
}

BYTE GamePad::XBoxController::RightTriggerLocation()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	//State.Gamepad.bRightTrigger = '5';
	return State.Gamepad.bRightTrigger;					//returns a value between 0 and 255
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	GamePad::Coordinate LeftStick(State.Gamepad.sThumbLX, State.Gamepad.sThumbLY);		//creates coordinate class which contains coordinates (x,y) of left thumb

	short x;
	short y;
	float ratio;
	float XCoord = LeftStick.GetX();
	float YCoord = LeftStick.GetY();

	float magnitude = sqrt(XCoord * XCoord + YCoord * YCoord);				//calculate magnitude of vector using Pythagoras

	if (magnitude > this->deadzone)
	{
		if (magnitude > MAX_VALUE)			//cap the magnitude if it is greater than the maximum value
		{
			magnitude = MAX_VALUE;
		}
		//calculate scaling factor
		ratio = (((magnitude - this->deadzone) / (MAX_VALUE - this->deadzone)) * MAX_VALUE) / (magnitude);		//			 input magnitude - deadzone radius
		float modXCoord = ratio * XCoord;																		//		    ------------------------------------ * maximum radius 
		float modYCoord = ratio * YCoord;																		//			 maximum radius - deadzone radius
		x = static_cast<SHORT>(modXCoord);																		//ratio = -------------------------------------------------------
		y = static_cast<SHORT>(modYCoord);																		//							 input magnitude
	}
	else				//if coordinates are in deadzone, set them to zero 
	{
		x = 0;
		y = 0;
	}

	LeftStick.SetX(x);			//sets new modified coordinates
	LeftStick.SetY(y);

	return LeftStick;		//returns the coordinate class of left thumb
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	GamePad::Coordinate RightStick(State.Gamepad.sThumbRX, State.Gamepad.sThumbRY);		//creates coordinate class which contains coordinates (x,y) of left thumb

	short x;
	short y;
	float ratio;
	float XCoord = RightStick.GetX();
	float YCoord = RightStick.GetY();

	float magnitude = sqrt(XCoord * XCoord + YCoord * YCoord);				//calculate magnitude of vector using Pythagoras

	if (magnitude > this->deadzone)
	{
		if (magnitude > MAX_VALUE)			//cap the magnitude if it is greater than the maximum value
		{
			magnitude = MAX_VALUE;
		}
		//calculate scaling factor
		ratio = (((magnitude - this->deadzone) / (MAX_VALUE - this->deadzone)) * MAX_VALUE) / (magnitude);		//			 input magnitude - deadzone radius
		float modXCoord = ratio * XCoord;																		//		    ------------------------------------ * maximum radius 
		float modYCoord = ratio * YCoord;																		//			 maximum radius - deadzone radius
		x = static_cast<SHORT>(modXCoord);																		//ratio = -------------------------------------------------------
		y = static_cast<SHORT>(modYCoord);																		//							 input magnitude
	}
	else				//if coordinates are in deadzone, set them to zero 
	{
		x = 0;
		y = 0;
	}

	RightStick.SetX(x);			//sets new modified coordinates
	RightStick.SetY(y);

	return RightStick;		//returns the coordinate class of left thumb
}

void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	xinput->XInputGetState(ControllerId, &State);		//retrieve current state of controller
	Vibration.wLeftMotorSpeed = left;		//set left motor to value passed in
	Vibration.wRightMotorSpeed = right;		//set right motor to vaue passed in 
	xinput->XInputSetState(ControllerId, &Vibration);		//sets state of controller after change in vibration struct 
}

void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	this->deadzone = radius;		
}
