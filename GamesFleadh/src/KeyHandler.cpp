/// <summary>
/// @author Cathal Redmond
/// </summary>
#include "KeyHandler.h"

/// <summary>
/// @brief default constructor for the class
/// </summary>
KeyHandler::KeyHandler()
{
}

/// <summary>
/// @brief updates key pressed status
/// assigns value of true of false to the key
/// </summary>
/// <param name="key">SFML Key</param>
/// <param name="isPressed">true if key is pressed</param>
void KeyHandler::updateKey(sf::Keyboard::Key key, bool isPressed)
{
	m_keyMap[key] = isPressed;
}


/// <summary>
/// @brief checks if specified key has been pressed
/// </summary>
/// <param name="key">SFML Key</param>
/// <returns>Returns true if key has been pressed else false</returns>
bool KeyHandler::isPressed(sf::Keyboard::Key key) const
{
	KeyMap::const_iterator it = m_keyMap.find(key);

	if (it != m_keyMap.end())
	{
		return it->second;
	}
	return false;
}
