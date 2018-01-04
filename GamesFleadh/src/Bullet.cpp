/// <summary>
/// @author Cathal Redmond
/// </summary>
#include "Bullet.h"





void Bullet::initialise(sf::Texture const & t_texture, sf::Vector2f t_position, float t_rotation, sf::Vector2f t_direction)
{
	m_bulletSprite.setTexture(t_texture);
	m_bulletSprite.setTextureRect(m_bulletRect);
	m_bulletSprite.setOrigin(m_bulletRect.width / 2.0f, m_bulletRect.height / 2.0f);
	m_bulletSprite.setPosition(t_position);
	m_bulletSprite.setRotation(t_rotation);

	m_direction = (t_direction / (sqrt((t_direction.x * t_direction.x) + (t_direction.y * t_direction.y))));

	m_speed = s_MAX_SPEED;
}

bool Bullet::update(sf::Time t_deltaTime)
{
	if (!inUse())
	{
		// no point in updating if bullet is not in use anymore
		return false;
	}
	

	sf::Vector2f position = m_bulletSprite.getPosition();
	sf::Vector2f newPosition = position + (m_direction * m_speed * (t_deltaTime.asMilliseconds()/1000.0f));

	m_bulletSprite.setPosition(newPosition);

	if (!isOnScreen(newPosition))
	{
		m_speed = 0;
	}
	return m_speed == s_MAX_SPEED;
}

bool Bullet::inUse() const
{
	return m_speed == s_MAX_SPEED;
}



bool Bullet::isOnScreen(sf::Vector2f t_position) const
{
	return t_position.x - m_bulletRect.width / 2.0f > 0.0f
		&& t_position.x + m_bulletRect.width / 2.0f < ScreenSize::s_width
		&& t_position.y - m_bulletRect.height / 2.0f > 0.0f
		&& t_position.y + m_bulletRect.height / 2.0f < ScreenSize::s_height;
}

float Bullet::degreesToRadians(float angleInDegrees)
{
	return 0.0f;
}
