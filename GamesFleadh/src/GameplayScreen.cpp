/// <summary>
/// @author Cathal Redmond
/// </summary>
#include "GameplayScreen.h"

GameplayScreen::GameplayScreen(KeyHandler & t_keyhandler)
	:
	m_keyhandler{ t_keyhandler }
	,m_player{m_keyhandler, m_controller}
{
	loadTextures();
	m_player.setTexture(m_spriteSheetTexture);
}

/// <summary>
/// @brief update function 
/// calls the update function for the controller and the player and calls the handlekeyInput function 
/// </summary>
void GameplayScreen::update()
{
	m_player.update();
	m_controller.update();
	handleKeyInput();
}

/// <summary>
/// @brief render function for the gameplay screen  
/// </summary>
/// <param name="t_window"></param>
void GameplayScreen::render(sf::RenderWindow & t_window)
{
	m_player.render(t_window);
}

/// <summary>
/// @brief procees keyinput anbd updates the keyhandler
/// </summary>
/// <param name="t_event"></param>
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

}


/// <summary>
/// @brief loads spritesheet texture into the game
/// </summary>
void GameplayScreen::loadTextures()
{
	if (!m_spriteSheetTexture.loadFromFile("./resources/images/spriteSheet.png"))
	{
		std::cout << "Error Loading Player Texture" << std::endl;
	}
	
}