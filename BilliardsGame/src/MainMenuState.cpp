#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState()
	: mInput{0}
{
}

void MainMenuState::HandleInput(Game& game)
{
	std::cin >> mInput;
	switch (mInput)
	{
	case 1:
		game.GetStateStack().PushState(std::make_shared<PlayState>());
		break;
	case 2:
		game.GetStateStack().ClearStates();
		break;
	default:
		std::cout << "			Invalid input\n";
		break;
	}
}

void MainMenuState::Update(Game& game, float deltaTime)
{
}

void MainMenuState::Draw(Game& game)
{
	std::cout << "\033[34m"
		<< " __| |____________________________________________| |__\n"
		<< "(__   ____________________________________________   __)\n"
		<< "   | |                      *                     | |\n"
		<< "   | |                   *  *  *                  | |\n"
		<< "   | |       ||       * BILLIARDS *      ||       | |\n"
		<< "   | |============================================| |\n"
		<< "   | |                                            | |\n"
		<< "   | |                                            | |\n"
		<< "   | |                * Start: 1                  | |\n"
		<< "   | |                *  Quit: 2                  | |\n"
		<< "   | |                                            | |\n"
		<< "   | |                                            | |\n"
		<< " __| |____________________________________________| |__\n"
		<< "(__   ____________________________________________   __)\n"
		<< "   | |                                            | |\n"
		<< "\033[0m"
		<< "			Input: ";
}
