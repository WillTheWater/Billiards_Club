#pragma once

class Game;

class RenderManager
{
public:
	RenderManager() = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	RenderManager(Game& game);

	void RenderTable();
	void RenderBalls();
	void DebugBallVectors();

private:
	Game& mGameRef;
};

