#pragma once
#include "State.h"
#include "Button.h"

class MainMenuState : public State
{
public:
	MainMenuState();
	virtual						~MainMenuState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;

private:
	void						GUISetup(Game& game);
	void						BackgroundSetup(Game& game);
	sf::Sprite					mBackground;
	Button						mStartButton;
	Button						mExitButton;
};

