#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "EntityGlobals.h"
#include "StateStack.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "PhysicsEngine.h"
#include "EntityManager.h"
#include "RenderManager.h"
#include "Button.h"
#include "InputManager.h"
#include "GUI.h"

class Game
{
public:
	Game();

	void						Run();
	StateStack&					GetStateStack();
	sf::RenderWindow&			GetWindow();
	sf::Vector2u				GetWindowSize();
	float						GetDeltaTime() const;
	TextureManager&				GetTextureManager();
	EntityManager&				GetEntityManager();
	PhysicsEngine&				GetPhysicsEngine();
	RenderManager&				GetRenderManager();
	InputManager&				GetInputManager();
	GUI&						GetGUI();
	void						IncrementShotsTaken();
	int							GetShotsTaken();
	void						ResetShotsTaken();
	void						CheckWinConditionOnBallSunk();
	void						GameWon();
	void						GameLost();
	void						ResetGame();
	bool						IsGameOver();
	bool						IsGameWon();
	bool						isGameLost();



private:
	sf::RenderWindow			mWindow;
	float						mDeltaTime;
	sf::Image					mIcon;
	sf::Clock					mClock;
	void						Tick();
	TextureManager				mTextureManager;
	EntityManager				mEntityManager;
	PhysicsEngine				mPhysicsEngine;
	RenderManager				mRenderManager;
	InputManager				mInputManager;
	StateStack					mStateStack;
	GUI							mGUI;
	int							mShotsTaken;
	bool						mGameWon;
	bool						mGameLost;
};