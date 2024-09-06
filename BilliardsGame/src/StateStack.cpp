#include "StateStack.h"

void StateStack::PushState(std::shared_ptr<State> state)
{
	mStates.push_back(state);
}

void StateStack::PopState()
{
	if (!mStates.empty()) { mStates.pop_back(); }
}

void StateStack::ClearStates()
{
	mStates.clear();
}

std::shared_ptr<State> StateStack::GetCurrentState()
{
	if (!mStates.empty()) { return mStates.back(); }
	return nullptr;
}

void StateStack::Update(Game& game, float deltaTime)
{
	if (!mStates.empty()) { mStates.back()->Update(game, deltaTime); }
}

void StateStack::Draw(Game& game)
{
	if (!mStates.empty()) { mStates.back()->Draw(game); }
}
