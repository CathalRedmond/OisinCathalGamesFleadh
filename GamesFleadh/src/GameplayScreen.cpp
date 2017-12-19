#include "GameplayScreen.h"

GameplayScreen::GameplayScreen(KeyHandler & t_keyhandler)
	:
	m_keyhandler{ t_keyhandler }
	,m_bullet{m_keyhandler}
	,m_player{m_keyhandler}
{
	loadTextures();
	m_player.setTexture(m_playerTexture);
	m_bullet.setTexture(m_bulletTexture);
	
}

void GameplayScreen::update()
{
	m_player.update();
	m_bullet.update();
	m_xbox360Controller.update();
	if (m_xbox360Controller.m_currentState.RB == true)
	{
		m_bullet.setVelocity((m_xbox360Controller.m_currentState.RightThumbStick) * 0.9f);
	}
	m_player.setVelocity(m_xbox360Controller.m_currentState.LeftThumbStick * 0.9f);
}

void GameplayScreen::render(sf::RenderWindow & t_window)
{
	m_bullet.render(t_window);
	m_player.render(t_window);
	handleKeyInput();
}

void GameplayScreen::processEvents(sf::Event & t_event)
{
	switch (t_event.type)
	{
	case sf::Event::KeyPressed:
		m_keyhandler.updateKey(t_event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		m_keyhandler.updateKey(t_event.key.code, false);
		break;
	default:
		break;
	}
}

GameplayScreen::~GameplayScreen()
{
}

void GameplayScreen::handleKeyInput()
{
	if (m_xbox360Controller.m_currentState.RB == true)
	{
		m_bullet.setIntialPosition(m_player.getPosition());
	}
}

void GameplayScreen::loadTextures()
{
	if (!m_playerTexture.loadFromFile("./resources/images/player.png"))
	{
		std::cout << "Error Loading Player Texture" << std::endl;
	}
	if (!m_bulletTexture.loadFromFile("./resources/images/bullet.png"))
	{
		std::cout << "Error Loading Bullet Texture" << std::endl;
	}
}