/// <summary>
/// @author Cathal Redmond
/// </summary>

#ifndef KEYHANDLER_H 
#define KEYHANDLER_H

#include <map>
#include <SFML/Window/Keyboard.hpp>

/// <summary>
/// @brief Class to manage simultanoes key input in SFML
/// </summary>
class KeyHandler
{
public:
	KeyHandler();
	void updateKey(sf::Keyboard::Key t_key, bool t_isPressed);
	bool isPressed(sf::Keyboard::Key key) const;

private:

	//defines keymap as an std::map of sf::keyboard key to bool
	typedef std::map<sf::Keyboard::Key, bool> KeyMap;

	// A std::map to manage the status of key presses.
	KeyMap m_keyMap;
};

#endif // !KEYHANDLER_H