#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TestState.h"
#include <iomanip>


Game::Game()
    : mWindow(sf::VideoMode(1600, 900), "Billiards", sf::Style::Close)
    , mDeltaTime{ 0.0f }
    , mEntityManager{*this}
    , mPhysicsEngine{*this}
    , mTextureManager{*this}
    , mRenderManager{*this}
{
    mWindow.setFramerateLimit(120);
    mIcon.loadFromFile("assets/graphics/icon.png");
    mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());
    mStateStack.PushState(std::make_unique<TestState>());   // Change this back to 'MenuState' 
}

void Game::Run()
{
    while (mWindow.isOpen() && mStateStack.GetCurrentState() != nullptr)
    {
        Tick();
        mStateStack.GetCurrentState()->HandleInput(*this);
        mStateStack.GetCurrentState()->Update(*this, mDeltaTime);
        mStateStack.GetCurrentState()->Draw(*this);
    }
}

StateStack& Game::GetStateStack()
{
    return mStateStack;
}

sf::RenderWindow& Game::GetWindow()
{
    return mWindow;
}

sf::Vector2u Game::GetWindowSize()
{
    return mWindow.getSize();
}

float Game::GetDeltaTime() const
{
    return mDeltaTime;
}

TextureManager& Game::GetTextureManager()
{
    return mTextureManager;
}

EntityManager& Game::GetEntityManager()
{
    return mEntityManager;
}

PhysicsEngine& Game::GetPhysicsEngine()
{
    return mPhysicsEngine;
}

RenderManager& Game::GetRenderManager()
{
    return mRenderManager;
}

void Game::Tick()
{
    mDeltaTime = mClock.restart().asSeconds();
}
