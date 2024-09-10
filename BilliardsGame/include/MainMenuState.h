#pragma once
#include "State.h"
#include "GUI.h"

class Game;

class MainMenuState : public State
{
public:
	MainMenuState(Game& game);

	virtual						~MainMenuState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;
	void						MainMenuGUISetup(Game& game);

private:
	Game&						mGameRef;
};