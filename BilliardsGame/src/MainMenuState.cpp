#include "Game.h"

MainMenuState::MainMenuState(Game& game)
	: mGameRef{game}
{
	MainMenuGUISetup(game);
}

void MainMenuState::HandleInput(Game& game)
{
	game.GetGUI().MainMenuInput(game);
}

void MainMenuState::Update(Game& game, float deltaTime)
{
}

void MainMenuState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	game.GetGUI().DrawMainMenu(game);
	game.GetWindow().display();
}

void MainMenuState::MainMenuGUISetup(Game& game)
{
	game.GetGUI().MainMenuSetup(game);
}
