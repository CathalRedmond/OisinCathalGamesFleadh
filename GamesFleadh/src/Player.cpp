/// <summary>
/// @author Cathal Redmond
/// </summary>


#include "Player.h"



Player::Player(KeyHandler const & t_keyhandler, Xbox360Controller const & t_controller)
	:
    m_keyHandler{ t_keyhandler }
   ,m_controller{t_controller}
   ,m_direction{ sf::Vector2f(0.0f, 75.0f) }
	// change this value to switch between using keyboard and controller
	,m_usingController{false}
{
	time = sf::milliseconds(10.0);
}

Player::~Player()
{
}

/// <summary>
/// @brief renders the player sprite and calls the bullet pool render function which renders all the player bullet on the screen
/// </summary>
/// <param name="t_window"></param>
void Player::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_playerSprite);
	m_pool.render(t_window);
}

/// <summary>
/// @brief update function for the player class
/// updates values for the player
/// </summary>
void Player::update()
{
	// if bool is true doesn't allow for input from the keyboard to move or shoot
	// if bool false doesn't allow for input from the controller to move or shoot
	if(m_usingController)
	{
		handleControllerInput();
	}
	else
	{
		handleKeyInput();
	}

	m_position += m_velocity;
	boundaryCheck();

	m_playerSprite.setPosition(m_position);
	m_playerSprite.setRotation(m_rotationAngle);

	// if bullet has been fired ,timer goes down until it is 0 (or less) then bullet can be fired again 
	if (m_fireRequested && m_shootTimer > 0.0)
	{
		m_shootTimer -= time.asMilliseconds();
	}
	else
	{
		// reset values
		m_fireRequested = false;
		m_shootTimer = s_TIME_BETWEEN_SHOTS;
	}
	// updates the bullet pool which updates all the players bullets on the screen
	m_pool.update(time);
}

/// <summary>
/// @ brief loads texture used for the player - the spritesheet - in from the gameplayscreen class
/// </summary>
/// <param name="t_texture"></param>
void Player::setTexture(sf::Texture const & t_texture)
{
	m_texture = t_texture ;
	setUpSprite();
}



/// <summary>
/// @brief function used to fire bullets for the player
/// </summary>
void Player::requestFire()
{
	m_fireRequested = true;
	// only works if time is equal, allows for delay between the bullet shots
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		float multipleAmount;	// used to multiply by direction to get bullet to orignate where player is pointing
		if (m_direction.x == 0.0f || m_direction.y == 0.0f)
		{
			multipleAmount = 75.0f;	// for left,right,up and down directions
		}
		else
		{
			multipleAmount = 53.0f;	// used for diagonall directions
		}
		sf::Vector2f tipOfGun(m_playerSprite.getPosition() + (m_direction * multipleAmount));
		// creates a bullet for the player by using the bullet pool
		m_pool.create(m_texture, tipOfGun, m_rotationAngle, m_direction);
	}
}

/// <summary>
/// @brief sets up and intialieses values for the sprite used for the player
/// </summary>
void Player::setUpSprite()
{
	m_playerSprite.setTexture(m_texture);
	m_playerSprite.setTextureRect(m_playerRect);
	m_playerSprite.setPosition(m_position);
	m_playerSprite.setOrigin(m_playerRect.width / 2.0f, m_playerRect.height / 2.0f);
}


/// <summary>
/// @brief function that handles the input from the keyboard for the player
/// When the WASD Keys are pressed it sets the player's current velocity and direction
/// When The F key is pressed it fires a bullet - key used can be changed, right now moving diagonally and shooting is a bit difficult to do 
/// </summary>
void Player::handleKeyInput()
{
	if (m_keyHandler.isPressed(sf::Keyboard::A) && m_keyHandler.isPressed(sf::Keyboard::W))
	{
		m_velocity = sf::Vector2f(-5.3f, -5.3f);
		m_direction = sf::Vector2f(-1.0f, -1.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::A) && m_keyHandler.isPressed(sf::Keyboard::S))
	{
		m_velocity = sf::Vector2f(-5.3f, 5.3f);
		m_direction = sf::Vector2f(-1.0f, 1.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::D) && m_keyHandler.isPressed(sf::Keyboard::W))
	{
		m_velocity = sf::Vector2f(5.3f, -5.3f);
		m_direction = sf::Vector2f(1.0f, -1.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::D) && m_keyHandler.isPressed(sf::Keyboard::S))
	{
		m_velocity = sf::Vector2f(5.3f, 5.3f);
		m_direction = sf::Vector2f(1.0f, 1.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::D))
	{
		m_velocity = sf::Vector2f(7.5f,0.0f);
		m_direction = sf::Vector2f(1.0f, 0.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::S))
	{
		m_velocity = sf::Vector2f(0.0f, 7.5f);
		m_direction = sf::Vector2f(0.0f, 1.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::A))
	{
		m_velocity = sf::Vector2f(-7.5f, 0.0f);
		m_direction = sf::Vector2f(-1.0f, 0.0f);
	}
	else if (m_keyHandler.isPressed(sf::Keyboard::W))
	{
		m_velocity = sf::Vector2f(0.0f, -7.5f);
		m_direction = sf::Vector2f(0.0f, -1.0f);
	}
	else
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
		m_direction = m_direction;
	}

	if (m_keyHandler.isPressed(sf::Keyboard::F))
	{
		requestFire();
	}
	calculateAngle();
}


/// <summary>
/// @brief takes the direction vector and calculates the current angle of rotation the player should have
/// </summary>
void Player::calculateAngle()
{
		// prevents division by zero - error checking
		// also sets rotation angle to the one of the two values it could be when the 
		// x componenet is 0
		if (m_direction.x == 0)
		{
			if (m_direction.y > 0)
			{
				m_rotationAngle = 90;  // pointing right
			}
			else
			{
				m_rotationAngle = 270; // pointing left
			}
		}
		else
		{
			// bool for if the angle is a minus value or not in the x component
			bool negativeAngle = false;
			if (m_direction.x < 0)
			{
				negativeAngle = true;
			}

			// tan(angle) == opposite / adjacent
			// rotationAngle = atan(y - component / x - component)
			m_rotationAngle = atan((m_direction.y / m_direction.x));
			
			// converting angle value to degrees
			m_rotationAngle = radiansToDegress(m_rotationAngle);


			// if angle is negative, 180 is added to change it to the corresponding positive angle
			// i.e -45 degrees is the same as 315 degrees (360 - 45  = 315)
			if (negativeAngle)
			{
				m_rotationAngle += 180;
			}
		}
}

/// <summary>
/// @brief handles input for the player with regard to the controller 
/// </summary>
void Player::handleControllerInput()
{
	if (m_controller.m_currentState.RTrigger > 50.0f)
	{
		requestFire();
	}
	determineDirection();
	determineVelocity();
}



/// <summary>
/// @brief takes in a value for an angle in radian and returns the same angle in degrees
/// </summary>
/// <param name="t_degreesAngle">angle in radian form</param>
/// <returns>angle in degrees form</returns>
float Player::radiansToDegress(float t_radianAngle)
{
	return (t_radianAngle * (180.0f/ acos(-1.0f)));
}


/// <summary>
/// @brief checks if player is outside of the screen or not
/// if the player is outside the screen the function places the player at the the very edge of the screen
/// </summary>
void Player::boundaryCheck()
{
	if (m_position.x + m_playerRect.width / 2.0f > ScreenSize::s_width)
	{
		m_position.x = ScreenSize::s_width - m_playerRect.width / 2.0f;
	}
	if (m_position.x - m_playerRect.width / 2.0f < 0.0f)
	{
		m_position.x = 0.0f + m_playerRect.width / 2.0f;
	}
	if (m_position.y + m_playerRect.height / 2.0f > ScreenSize::s_height)
	{
		m_position.y = ScreenSize::s_height - m_playerRect.height / 2.0f;
	}
	if (m_position.y - m_playerRect.height / 2.0f < 0.0f)
	{
		m_position.y = 0.0f + m_playerRect.height / 2.0f;
	}
}


/// <summary>
/// @brief calculates current player direction from the position of the right thumbstick
/// </summary>
void Player::determineDirection()
{
	if (m_controller.m_currentState.RightThumbStickLeft && m_controller.m_currentState.RightThumbStickUp)
	{
		 m_direction = sf::Vector2f(-1.0f, 1.0f);
		
	}
	else if (m_controller.m_currentState.RightThumbStickLeft && m_controller.m_currentState.RightThumbStickDown)
	{
		m_direction = sf::Vector2f(-1.0f, -1.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickRight && m_controller.m_currentState.RightThumbStickUp)
	{
		m_direction = sf::Vector2f(1.0f, 1.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickRight && m_controller.m_currentState.RightThumbStickDown)
	{
		m_direction = sf::Vector2f(1.0f, -1.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickLeft)
	{
		m_direction = sf::Vector2f(-1.0f, 0.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickRight)
	{
		m_direction = sf::Vector2f(1.0f, 0.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickUp)
	{
		m_direction = sf::Vector2f(0.0f, 1.0f);
	}
	else if (m_controller.m_currentState.RightThumbStickDown)
	{
		m_direction = sf::Vector2f(0.0f, -1.0f);
	}
	else
	{
		m_direction = m_direction;
	}
	calculateAngle();
}


/// <summary>
/// @brief calculates current player velocity from the position of the left thumbstick
/// </summary>
void Player::determineVelocity()
{
	if (m_controller.m_currentState.LeftThumbStickLeft && m_controller.m_currentState.LeftThumbStickUp)
	{
		m_velocity = sf::Vector2f(-5.3f, 5.3f);
	}
	else if (m_controller.m_currentState.LeftThumbStickLeft && m_controller.m_currentState.LeftThumbStickDown)
	{
		m_velocity = sf::Vector2f(-5.3f, -5.3f);
	}
	else if (m_controller.m_currentState.LeftThumbStickRight && m_controller.m_currentState.LeftThumbStickUp)
	{
		m_velocity = sf::Vector2f(5.3f, 5.3f);
	}
	else if (m_controller.m_currentState.LeftThumbStickRight && m_controller.m_currentState.LeftThumbStickDown)
	{
		m_velocity = sf::Vector2f(5.3f, -5.3f);
	}
	else if (m_controller.m_currentState.LeftThumbStickLeft)
	{
		m_velocity = sf::Vector2f(-7.5f, 0.0f);
	}
	else if (m_controller.m_currentState.LeftThumbStickRight)
	{
		m_velocity = sf::Vector2f(7.5f, 0.0f);
	}
	else if (m_controller.m_currentState.LeftThumbStickUp)
	{
		m_velocity = sf::Vector2f(0.0f, 7.5f);
	}
	else if (m_controller.m_currentState.LeftThumbStickDown)
	{
		m_velocity = sf::Vector2f(0.0f, -7.5f);
	}
	else
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}


}