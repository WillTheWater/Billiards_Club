#pragma once
#include "State.h"

class MainMenuState : public State
{
public:
	MainMenuState();
	virtual						~MainMenuState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;

private:
	int							mInput;
};

