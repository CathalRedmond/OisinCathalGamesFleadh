/// <summary>
/// @author Cathal Redmond
/// </summary>
#include "BulletPool.h"



void BulletPool::create(sf::Texture const & texture, sf::Vector2f t_position, float rotation, sf::Vector2f t_direction)
{
	// If no bullets available, simply re-use the next in sequence.
	if (m_poolFull)
	{
		m_nextAvailable = (m_nextAvailable + 1) % s_POOL_SIZE;
	}

	m_bullets.at(m_nextAvailable).initialise(texture, t_position, rotation, t_direction);
}

void BulletPool::update(sf::Time t_deltaTime)
{
	// The number of active bullets.
	int activeCount = 0;
	// Assume the pool is not full initially.
	m_poolFull = false;
	for (int i = 0; i < s_POOL_SIZE; i++)
	{
		if (!m_bullets.at(i).update(t_deltaTime))
		{
			// If this bullet has expired, make it the next available.
			m_nextAvailable = i;
		}
		else
		{
			// So we know how many bullets are active.
			activeCount++;
		}
	}
	// If no bullets available, set a flag.
	if (s_POOL_SIZE == activeCount)
	{
		m_poolFull = true;
	}
}

void BulletPool::render(sf::RenderWindow & window)
{
	for (int i = 0; i < s_POOL_SIZE; i++)
	{
		// If bullet is active...
		if (m_bullets.at(i).inUse())
		{
			window.draw(m_bullets.at(i).m_bulletSprite);
		}
	}
}
