#pragma once
#include "Game.h"


class Game; //Forward decleration to prevent circule dependancies

class RenderManager
{
public:
	RenderManager() = delete;
	RenderManager(Game& game);

	void RenderTable();
	void RenderBalls();

private:
	Game& mGameRef;
};

