#include "Player.h"

Player::Player(KeyHandler const & t_keyhandler)
	:
    m_position{ScreenSize::s_width / 2.0f, ScreenSize::s_height / 2.0f}
	, m_keyHandler{ t_keyhandler }
{
}

Player::~Player()
{
}

void Player::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

void Player::update()
{
	handleKeyInput();

	m_position += m_velocity;
	m_sprite.setPosition(m_position);
}

void Player::setTexture(sf::Texture const & t_texture)
{
	m_texture = t_texture ;
	setUpSprite();
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

void Player::setVelocity(sf::Vector2f & t_velocity)
{
	m_velocity = t_velocity;
	m_velocity /= 10.0f;
}

void Player::setUpSprite()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
}

void Player::handleKeyInput()
{
	
	if (m_keyHandler.isPressed(sf::Keyboard::D))
	{
		m_position.x += 5;
		m_sprite.setRotation(0);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::S))
	{
		m_position.y += 5;
		m_sprite.setRotation(90);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::A))
	{
		m_position.x -= 5;
		m_sprite.setRotation(180);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::W))
	{
		m_position.y -= 5;
		m_sprite.setRotation(270);
	}
	m_sprite.setPosition(m_position);
}
