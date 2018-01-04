/// <summary>
/// @ author Cathal Redmond
/// </summary>
#include "Controller.h"

Xbox360Controller::Xbox360Controller()
{
	// intializes back to false to prevent window closing due to an unintialized back bool
	m_currentState.Back = false;
	connect();
}

Xbox360Controller::~Xbox360Controller()
{
}

void Xbox360Controller::update()
{

	// only works if controller is connected
	if (isConnected() && connect())
	{
		// sets previous state to current state at the start of each update
		m_previousState = m_currentState;

		// checks if button is pressed on controller and sets corresponding bool to true
		// if not pressed bool is false
		// continues down to the right thumb stick click

		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 0))
		{
			m_currentState.A = true;

		}
		else
		{
			m_currentState.A = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 1))
		{
			m_currentState.B = true;
		}
		else
		{
			m_currentState.B = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 2))
		{
			m_currentState.X = true;

		}
		else
		{
			m_currentState.X = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 3))
		{
			m_currentState.Y = true;

		}
		else
		{
			m_currentState.Y = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 4))
		{
			m_currentState.LB = true;

		}
		else
		{
			m_currentState.LB = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 5))
		{
			m_currentState.RB = true;

		}
		else
		{
			m_currentState.RB = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 6))
		{
			m_currentState.Back = true;

		}
		else
		{
			m_currentState.Back = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 7))
		{
			m_currentState.Start = true;

		}
		else
		{
			m_currentState.Start = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 8))
		{
			m_currentState.LeftThumbStickClick = true;

		}
		else
		{
			m_currentState.LeftThumbStickClick = false;
		}
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 9))
		{
			m_currentState.RightThumbStickClick = true;

		}
		else
		{
			m_currentState.RightThumbStickClick = false;
		}

		// checks if z axis of controller is greater than 0 (positive number)
		// then that means left trigger is activate and takes the current z axis value
		if ((sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z)) > 0)
		{
			m_currentState.LTrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
			// right trigger value set to 0
			m_currentState.RTrigger = 0.0f;
		}
		// check if z axis of controller is less than 0 (negative number)
		// then that means right trigger is activate and takes the current z axis value multiplied 
		// by minus 1 to get a positive value
		else if ((sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z)) < 0)
		{
			m_currentState.RTrigger = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z)) * -1;
			// left trigger value set to 0
			m_currentState.LTrigger = 0.0f;

		}

		// checks if values are greater than threshold or minus threshold to determine 
		// which directions on the dpad are activated

		// if x-axis greater than threshold than dpad pointing right and sets bool to true
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovX) > dpadThreshold)
		{
			m_currentState.DpadRight = true;
		}
		else
		{
			m_currentState.DpadRight = false;
		}

		// if x-axis less than minus threshold than dpad pointing left and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovX) < -dpadThreshold)
		{
			m_currentState.DpadLeft = true;
		}
		else
		{
			m_currentState.DpadLeft = false;
		}

		// if y-axis greater than threshold than dpad pointing up and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) > dpadThreshold)
		{
			m_currentState.DpadUp = true;
		}
		else
		{
			m_currentState.DpadUp = false;
		}

		// if y-axis less than minus threshold than dpad pointing down and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::PovY) < -dpadThreshold)
		{
			m_currentState.DpadDown = true;
		}
		else
		{
			m_currentState.DpadDown = false;
		}


		// checks if values are greater than threshold or minus threshold to determine 
		// which directions on the dpad are activated

		// if x-axis greater than threshold than dpad pointing right and sets bool to true
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X) > dpadThreshold)
		{
			m_currentState.LeftThumbStickRight = true;
		}
		else
		{
			m_currentState.LeftThumbStickRight = false;
		}

		// if x-axis less than minus threshold than dpad pointing left and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X) < -dpadThreshold)
		{
			m_currentState.LeftThumbStickLeft = true;
		}
		else
		{
			m_currentState.LeftThumbStickLeft = false;
		}

		// if y-axis greater than threshold than dpad pointing up and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y) > dpadThreshold)
		{
			m_currentState.LeftThumbStickUp = true;
		}
		else
		{
			m_currentState.LeftThumbStickUp = false;
		}

		// if y-axis less than minus threshold than dpad pointing down and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y) < -dpadThreshold)
		{
			m_currentState.LeftThumbStickDown = true;
		}
		else
		{
			m_currentState.LeftThumbStickDown = false;
		}


		// checks if values are greater than threshold or minus threshold to determine 
		// which directions on the dpad are activated

		// if x-axis greater than threshold than dpad pointing right and sets bool to true
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U) > dpadThreshold)
		{
			m_currentState.RightThumbStickRight = true;
		}
		else
		{
			m_currentState.RightThumbStickRight = false;
		}

		// if x-axis less than minus threshold than dpad pointing left and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U) < -dpadThreshold)
		{
			m_currentState.RightThumbStickLeft = true;
		}
		else
		{
			m_currentState.RightThumbStickLeft = false;
		}

		// if y-axis greater than threshold than dpad pointing up and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R) > dpadThreshold)
		{
			m_currentState.RightThumbStickUp = true;
		}
		else
		{
			m_currentState.RightThumbStickUp = false;
		}

		// if y-axis less than minus threshold than dpad pointing down and sets bool to true

		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R) < -dpadThreshold)
		{
			m_currentState.RightThumbStickDown = true;
		}
		else
		{
			m_currentState.RightThumbStickDown = false;
		}

		// sets values of the left and right thumbsticks vectors to corresponding axis position
		m_currentState.LeftThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X);
		m_currentState.LeftThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y);
		m_currentState.RightThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U);
		m_currentState.RightThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R);




	}
}

// function that checks if controller is connected
bool Xbox360Controller::isConnected()
{
	bool connected = false;
	// for loop that checks if controller is connected
	for (int index = 0; index < sf::Joystick::Count; index++)
	{
		if (sf::Joystick::isConnected(index))
		{
			connected = true;
		}
	}
	return connected;
}

// function that checks if controller is connected and sets controller index
bool Xbox360Controller::connect()
{
	bool connected = false;;
	// for loop thats checks if controller is connected and sets the index of the controller
	for (int index = 0; index < sf::Joystick::Count; index++)
	{
		if (sf::Joystick::isConnected(index))
		{
			sf_Joystick_index = index;		// sets index
			connected = true;
		}
	}
	return connected;
}
