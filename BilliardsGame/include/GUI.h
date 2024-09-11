#pragma once
#include "Button.h"

class Game;

class GUI
{
public:
	GUI() = delete;
	GUI(Game& game);
	~GUI() = default;

	void MainMenuSetup(Game& game);
	void DrawMainMenu(Game& game);
	void MainMenuInput(Game& game);
	
	void PlaySetup(Game& game);
	void DrawPlay(Game& game);
	void PlayInput(Game& game);

private:
	Game&						mGameRef;
	sf::Sprite					mBackground;
	sf::Sprite					mFloor;
	// Needs refactored out
	sf::ConvexShape				polygon;
	sf::CircleShape				hole1;
	sf::CircleShape				hole2;
	sf::CircleShape				hole3;
	sf::CircleShape				hole4;
	sf::CircleShape				hole5;
	sf::CircleShape				hole6;

	std::unique_ptr<Button>		mStartButton;
	std::unique_ptr<Button>		mExitButton;
	std::unique_ptr<Button>		mAudioButton;
	bool						mAudioOn;
};

