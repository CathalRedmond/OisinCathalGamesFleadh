#include "Bullet.h"



Bullet::Bullet(KeyHandler const & t_keyhandler)
	:
	m_intialPosition{ ScreenSize::s_width / 2.0f, ScreenSize::s_height / 2.0f }
	,m_keyHandler{t_keyhandler}
	,m_velocity{0.0f,0.0f}
{
}


Bullet::~Bullet()
{
}

void Bullet::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

void Bullet::update()
{
	handleKeyInput();
	m_currentPosition += m_velocity;
	m_sprite.setPosition(m_currentPosition);
}

void Bullet::setTexture(sf::Texture const & t_texture)
{
	m_texture = t_texture;
	setUpSprite();
}

void Bullet::setVelocity(sf::Vector2f & t_velocity)
{
	m_velocity = t_velocity;
	m_velocity /= 10.0f;
}

void Bullet::setIntialPosition(sf::Vector2f & t_position)
{
	m_intialPosition = t_position;
	m_currentPosition = m_intialPosition;
}

void Bullet::setUpSprite()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_intialPosition);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
}

void Bullet::handleKeyInput()
{
	if (m_keyHandler.isPressed(sf::Keyboard::Left))
	{
		m_velocity = sf::Vector2f(-5.0f,0.0f);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Right))
	{
		m_velocity = sf::Vector2f(5.0f, 0.0f);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Up))
	{
		m_velocity = sf::Vector2f(0.0f, -5.0f);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Down))
	{
		m_velocity = sf::Vector2f(0.0f, 5.0f);
	}
}