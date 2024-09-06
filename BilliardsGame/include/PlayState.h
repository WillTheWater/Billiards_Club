#pragma once
#include "State.h"

class PlayState : public State
{
public:
	PlayState();
	virtual						~PlayState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;

private:
	int							mInput;
};

