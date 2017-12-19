#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"
#include "ScreenSize.h"
#include "KeyHandler.h"

class Player
{
public:
	Player(KeyHandler const & t_keyhandler);
	~Player();
	void render(sf::RenderWindow & t_window);
	void update();
	void setTexture(sf::Texture const & t_texture);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f & t_velocity);
private:
	void setUpSprite();
	void handleKeyInput();

	KeyHandler const & m_keyHandler;


	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};

#endif // !PLAYER_H
