#include "Game.h"

PlayState::PlayState(Game& game)
	: mGameRef(game)
{
	PlayGUISetup(game);
}

void PlayState::HandleInput(Game& game)
{
	game.GetGUI().PlayInput(game);
}

void PlayState::Update(Game& game, float deltaTime)
{
}

void PlayState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	game.GetGUI().DrawPlay(game);
	game.GetWindow().display();
}

void PlayState::PlayGUISetup(Game& game)
{
	game.GetGUI().PlaySetup(game);
}
