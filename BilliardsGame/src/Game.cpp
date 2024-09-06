#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

Game::Game()
    : mDeltaTime{ 0.0f }
{
    mStateStack.PushState(std::make_shared<MainMenuState>());
}

void Game::Run()
{
    while (mStateStack.GetCurrentState() != nullptr)
    {
        if (auto currentState = mStateStack.GetCurrentState())
        {
            mStateStack.Draw(*this); // Should be on bottom once graphics are used
            currentState->HandleInput(*this);
            mStateStack.Update(*this, mDeltaTime);
        }
        system("cls");
    }
}

StateStack& Game::GetStateStack()
{
    return mStateStack;
}
