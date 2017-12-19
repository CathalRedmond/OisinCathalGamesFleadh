#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "gameplayScreen.h"
#include "Enums.h"
#include "ScreenSize.h"
#include "KeyHandler.h"
#include <iostream>

class GameplayScreen;

/// <summary>
/// @brief game class used for the game
/// </summary>
class Game
{
public:
	Game();
	~Game();
	void run();

	// used to tell what screen the game is currently on
	CurrentScreen m_currentScreen{ CurrentScreen::gameplay };

private:
	void processEvents();
	void processGameEvents(sf::Event &event);
	void update(sf::Time t_deltaTime);
	void render();

	
	// gameplay screen used in the game
	GameplayScreen *m_gameplayScreen;

	// render window used for the game
	sf::RenderWindow m_window;

	KeyHandler m_keyhandler;
	


};

#endif // !GAME_H
