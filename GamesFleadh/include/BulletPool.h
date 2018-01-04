/// <summary>
/// @author Cathal Redmond
/// </summary>

/// <summary>
/// Basically this header and corresponding cpp is a copy of the projectile pool ross gives in the latest assigmenet for the tank project
/// Edited slightly to fit this project
/// </summary>




#ifndef BULLETPOOL_H
#define BULLETPOOL_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Bullet.h"

class Bullet;

class BulletPool
{
public:

	/// <summary>
	/// @brief No-op default constructor
	/// </summary>
	BulletPool() = default;

	/// <summary>
	/// @brief Creates a bullet.
	/// Creates a bullet from the pool of available bullets.
	///  If no bullets are available, the next in (pool) sequence after
	///  the last used bullet is chosen.
	/// </summary>
	/// <param name="texture">A reference to the sprite sheet texture</param>	
	/// <param name="x">The x position of the bullet</param>
	/// <param name="x">The y position of the bullet</param>
	/// <param name="rotation">The rotation angle of the bullet in degrees</param>
	void create(sf::Texture const & texture, sf::Vector2f t_position, float rotation, sf::Vector2f t_direction);

	/// <summary>
	/// @brief Updates all bullets in the pool.
	/// Sets an index to the next available bullet. Also sets a 
	///  status flag to indicate pool full (all bullets in use).
	/// </summary>
	/// <param name="dt">The delta time</param>	
	/// <param name="rotation">A reference to the container of wall sprites</param>
	void update(sf::Time t_deltaTime);

	/// <summary>
	/// @brief Draws all active bullets.
	/// </summary>
	/// <param name="window">The SFML render window</param>	
	void render(sf::RenderWindow & t_window);


private:
	static const int s_POOL_SIZE = 100;

	// A container for the bullets.
	std::array<Bullet, s_POOL_SIZE> m_bullets;

	// The index of the next available bullet.
	int m_nextAvailable{ 0 };

	// A flag indicating whether there are any bullets available (initially they are).
	bool m_poolFull{ false };
};

#endif // !BULLETPOOL_H
