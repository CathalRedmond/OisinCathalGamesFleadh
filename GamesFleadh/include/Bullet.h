#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "ScreenSize.h"
#include "KeyHandler.h"
#include "Player.h"

class Bullet
{
public:
	Bullet(KeyHandler const & t_keyhandler);
	~Bullet();
	void render(sf::RenderWindow & t_window);
	void update();
	void setTexture(sf::Texture const & t_texture);
	void setVelocity(sf::Vector2f & t_velocity);
	void setIntialPosition(sf::Vector2f & t_position);
private:
	void setUpSprite();
	void handleKeyInput();


	KeyHandler const & m_keyHandler;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_intialPosition;
	sf::Vector2f m_velocity;
	sf::Vector2f m_currentPosition;
};


#endif // !BULLET_H
