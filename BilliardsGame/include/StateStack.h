#pragma once
#include <vector>
#include <memory>
#include "State.h"

class StateStack
{
public:
	void						PushState(std::unique_ptr<State> state);
	void						PopState();
	void						ClearStates();
	State*						GetCurrentState();
	void						HandleInput(Game& game);
	void						Update(Game& game, float deltaTime);
	void						Draw(Game& game);

private:
	std::vector<std::unique_ptr<State>> mStates;
};