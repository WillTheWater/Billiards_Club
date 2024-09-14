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
	void RenderCue();
	void DebugRenderCue();
	void DebugBallVectors();
	void DrawDebugCollisionPoly();
	void DrawDebugConvexShape();

	void DrawDebugLineMouseToCueBall();

private:
	Game& mGameRef;
	sf::RenderStates mRenderMode;
};

