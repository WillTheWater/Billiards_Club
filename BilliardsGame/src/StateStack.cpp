#include "StateStack.h"

void StateStack::PushState(std::unique_ptr<State> state)
{
	mStates.push_back(std::move(state));
}

void StateStack::PopState()
{
	if (!mStates.empty()) { mStates.pop_back(); }
}

void StateStack::ClearStates()
{
	mStates.clear();
}

State* StateStack::GetCurrentState()
{
	if (!mStates.empty()) { return mStates.back().get(); }
	return nullptr;
}

void StateStack::HandleInput(Game& game)
{
	if (!mStates.empty()) { mStates.back()->HandleInput(game); }
}

void StateStack::Update(Game& game, float deltaTime)
{
	if (!mStates.empty()) { mStates.back()->Update(game, deltaTime); }
}

void StateStack::Draw(Game& game)
{
	if (!mStates.empty()) { mStates.back()->Draw(game); }
}
