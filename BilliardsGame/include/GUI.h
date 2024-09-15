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
	void PlayInput(sf::Event event);

private:
	Game&						mGameRef;
	sf::Sprite					mBackground;
	sf::Sprite					mFloor;
	std::unique_ptr<Button>		mStartButton;
	std::unique_ptr<Button>		mExitButton;
	std::unique_ptr<Button>		mAudioButton;
	bool						mAudioOn;
};

