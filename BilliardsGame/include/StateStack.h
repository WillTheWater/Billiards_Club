#pragma once
#include <vector>
#include <memory>
#include "State.h"

class StateStack
{
public:
	void						PushState(std::shared_ptr<State> state);
	void						PopState();
	void						ClearStates();
	std::shared_ptr<State>		GetCurrentState();
	void						Update(Game& game, float deltaTime);
	void						Draw(Game& game);

private:
	std::vector<std::shared_ptr<State>> mStates;
};
