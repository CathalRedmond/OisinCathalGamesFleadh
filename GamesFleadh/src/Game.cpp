/// <summary>
/// @author Cathal Redmond
/// </summary>
#include "Game.h"



Game::Game()
	:
	m_window{sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height,32), "GAMES FLEADH"}
{
	m_window.setVerticalSyncEnabled(true);
	m_gameplayScreen = new GameplayScreen{ m_keyhandler };
}


Game::~Game()
{
	if (m_gameplayScreen != nullptr)
	{
		delete(m_gameplayScreen);
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		processGameEvents(event);
		switch (m_currentScreen)
		{
		case CurrentScreen::gameplay:
			m_gameplayScreen->processEvents(event);
			break;
		default:
			break;
		}
	}
}

void Game::processGameEvents(sf::Event &event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		m_keyhandler.updateKey(event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		m_keyhandler.updateKey(event.key.code, false);
		break;
	default:
		break;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentScreen)
	{
	case CurrentScreen::gameplay:
		m_gameplayScreen->update();
		break;
	default:
		break;
	}
}

void Game::render()
{
	m_window.clear();
	switch (m_currentScreen)
	{
	case CurrentScreen::gameplay:
		m_gameplayScreen->render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}


