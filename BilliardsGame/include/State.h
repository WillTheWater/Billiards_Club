#pragma once

class Game; // Forward declaration to avoid circular dependencies

class State
{
public:
	virtual						~State() = default;

	virtual void				HandleInput(Game& game) = 0;
	virtual void				Update(Game& game, float deltaTime) = 0;
	virtual void				Draw(Game& game) = 0;
};