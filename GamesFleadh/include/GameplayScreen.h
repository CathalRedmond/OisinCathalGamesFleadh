/// <summary>
/// @author Cathal Redmond
/// </summary>
#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "Game.h"
#include "KeyHandler.h"
#include "Player.h"
#include "Bullet.h"
#include "Controller.h"


/// <summary>
/// @brief class for the gameplay screen used in the game
/// </summary>
class GameplayScreen
{
public:
	GameplayScreen(KeyHandler & t_keyhandler);
	void update();
	void render(sf::RenderWindow & t_window);
	void processEvents(sf::Event & t_event);
	~GameplayScreen();
private:
	void handleKeyInput();
	void loadTextures();

	// keyhandler used in the game
	KeyHandler m_keyhandler;

	// instance of player class
	Player m_player;



	// texture used for the player
	sf::Texture m_spriteSheetTexture;

	// instance of the controller class used in the game
	Xbox360Controller m_controller;


};

#endif // !GAMEPLAYSCREEN_H
