#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "Game.h"
#include "KeyHandler.h"
#include "Player.h"
#include "Bullet.h"
#include "Controller.h"


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
	KeyHandler m_keyhandler;
	void loadTextures();

	Player m_player;
	Bullet m_bullet;

	sf::Texture m_playerTexture;
	sf::Texture m_bulletTexture;

	Xbox360Controller m_xbox360Controller;


};

#endif // !GAMEPLAYSCREEN_H
