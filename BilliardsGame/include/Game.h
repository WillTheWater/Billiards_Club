#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "StateStack.h"
#include "TextureManager.h"

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

private:
	sf::RenderWindow			mWindow;
	float						mDeltaTime;
	sf::Image					mIcon;
	sf::Clock					mClock;
	void						Tick();
	TextureManager				mTextureManager;
	StateStack					mStateStack;
};