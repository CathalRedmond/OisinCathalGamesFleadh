/// <summary>
/// @author Cathal Redmond
/// </summary>
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"
#include "ScreenSize.h"
#include "KeyHandler.h"
#include "BulletPool.h"
#include "Controller.h"


/// <summary>
/// @brief class for the player in the game
/// Allows player to move and rotate and fire bullets
/// WASD Keys to move with keyboard an F key to fire bullet
/// Left thumbstick to move with controller and rightthumbstick for the direction player is facing, right trigger to fire a bullet
/// </summary>
class Player
{
public:
	Player(KeyHandler const & t_keyhandler, Xbox360Controller const & t_controller);
	~Player();
	void render(sf::RenderWindow & t_window);
	void update();
	void setTexture(sf::Texture const & t_texture);


private:
	void setUpSprite();

	void determineVelocity();
	void determineDirection();

	void requestFire();

	void handleKeyInput();
	void handleControllerInput();

	void calculateAngle();

	float radiansToDegress(float t_degreesAngle);

	void boundaryCheck();

	// keyhandler used in the game
	KeyHandler const & m_keyHandler;
	// controller used in the game - assumes xbox 360 controller is used
	Xbox360Controller const & m_controller;

	
	// rect used for player sprite on the sprite sheet
	sf::IntRect m_playerRect{0,0,100,100};

	// player texture - texture of the spritesheet
	sf::Texture m_texture;

	// sprite for the player
	sf::Sprite m_playerSprite;

	// position of the player
	sf::Vector2f m_position;

	// velocity of the player
	sf::Vector2f m_velocity;

	// direction player is going
	sf::Vector2f m_direction;


	// what angle the player is currently rotated at - in degrees
	float m_rotationAngle;

	// bool for if player is using the controller for the game or the keyboard
	bool m_usingController;

	// time used for firing bullets and for the bulletpool
	sf::Time time;

	// bullet pool for the player
	BulletPool m_pool;

	// bool for if the fire bullet function has been called
	bool m_fireRequested{ false };

	// cuurent time since bullet has been shot - should be intialsed to the same as the value below
	double m_shootTimer{ 400 };


	// value for the total time between bullet shots
	// increase the value - increase time between shots - slower, less shots
	// decrease the value - decrease time between shots - faster, more shots
	static int const s_TIME_BETWEEN_SHOTS{ 400 };

};

#endif // !PLAYER_H
