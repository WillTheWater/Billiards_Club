#pragma once
#include <iostream>
#include "StateStack.h"

class Game
{
public:
	Game();

	void						Run();
	StateStack&					GetStateStack();

private:
	float						mDeltaTime;
	StateStack					mStateStack;
};