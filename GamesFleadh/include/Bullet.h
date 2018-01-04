/// <summary>
/// @author Cathal Redmond
/// </summary>
#ifndef BULLET_H
#define BULLET_H

#include "SFML\Graphics.hpp"
#include "ScreenSize.h"


/// <summary>
/// @brief class for the bullets used in the game for the player
/// </summary>
class Bullet
{

	friend class BulletPool;


public:
	Bullet() = default;
	void initialise(sf::Texture const & t_texture, sf::Vector2f t_position, float t_rotation, sf::Vector2f t_direction);
	bool update(sf::Time t_deltaTime);
	bool inUse() const;
private:

	bool Bullet::isOnScreen(sf::Vector2f t_position) const;

	// Max speed of the bullet
	static constexpr float s_MAX_SPEED{ 1000.0 };

	// movement speed
	float m_speed{ s_MAX_SPEED };

	// the bullet sprite
	sf::Sprite m_bulletSprite;

	// texture of the bullet sprite
	sf::IntRect m_bulletRect{110,0,50,50};

	float degreesToRadians(float angleInDegrees);

	sf::Vector2f m_direction;
};


#endif // !BULLET_H
