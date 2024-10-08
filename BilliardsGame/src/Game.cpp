#include "Game.h"
#include "TestState.h"
#include <iomanip>


Game::Game()
    : mWindow(sf::VideoMode(1600, 900), "Billiard Club", sf::Style::Close)
    , mDeltaTime{ 0.0f }
    , mEntityManager{*this}
    , mPhysicsEngine{*this}
    , mTextureManager{*this}
    , mRenderManager{*this}
    , mInputManager{*this}
    , mGUI{*this}
    , mShotsTaken{0}
    , mGameWon{false}
    , mGameLost{false}
{
    mWindow.setFramerateLimit(120);
    mIcon.loadFromFile("assets/graphics/icon.png");
    mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());
    mStateStack.PushState(std::make_unique<MainMenuState>(*this));
    Audio::Init();
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

InputManager& Game::GetInputManager()
{
    return mInputManager;
}

GUI& Game::GetGUI()
{
    return mGUI;
}

void Game::PlaySound(AudioType sound, float volume, float pitch)
{
    mSoundManager.playSound(sound, volume, pitch);
}

void Game::ToggleMute(bool mute)
{
    mSoundManager.toggleMute(mute);
}

bool Game::IsMuted()
{
    return mSoundManager.isMuted();
}

void Game::IncrementShotsTaken()
{
    mShotsTaken++;
}

int Game::GetShotsTaken()
{
    return mShotsTaken;
}

void Game::ResetShotsTaken()
{
    mShotsTaken = 0;
}

void Game::CheckWinConditionOnBallSunk()
{
    int BallsLeft = 0;
    auto& balls = GetEntityManager().GetBallVector();
    for (auto& ball : balls)
    {
        if (ball->isVisible())
        {
            BallsLeft++;
        }
    }
    if (BallsLeft == 1 && balls[BallId_cueBall]->isVisible())
    {
        GameWon();
    }
    else if (BallsLeft == 0)
    {
        GameLost();
    }
    else if (BallsLeft > 1 && !balls[BallId::BallId_eight]->isVisible())
    {
        GameLost();
    }
}

void Game::GameWon()
{
    mGameLost = false;
    mGameWon = true;
}

void Game::GameLost()
{
    mGameLost = true;
    mGameWon = false;
}

void Game::ResetGame()
{
    mEntityManager.RackBalls();
    ResetShotsTaken();
    mGameLost = false;
    mGameWon = false;
}

bool Game::IsGameOver()
{
    return mGameLost || mGameWon;
}

bool Game::IsGameWon()
{
    return mGameWon;
}

bool Game::isGameLost()
{
    return mGameLost;
}

void Game::Tick()
{
    mDeltaTime = mClock.restart().asSeconds();
}
