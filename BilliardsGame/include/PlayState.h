#pragma once
#include "State.h"
#include "GUI.h"

class Game;

class PlayState : public State
{
public:
	PlayState(Game& game);

	virtual						~PlayState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;
	void						PlayGUISetup(Game& game);

private:
	Game&						mGameRef;
};