#pragma once
#include "State.h"
#include "Game.h"

class Game;

class TestState : public State
{
public:
	TestState();
	virtual						~TestState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;

private:
};

