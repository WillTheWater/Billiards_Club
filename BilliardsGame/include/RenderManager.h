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
	void DebugRenderPockets();
	void DebugBallVectors();
	void DrawDebugCollisionPoly();
	void DrawDebugConvexShape();
	void DrawGameWon();
	void DrawGameLost();
	void DrawShotsTaken();
	

	void DrawDebugLineMouseToCueBall();

private:
	Game& mGameRef;
	sf::RenderStates mRenderMode;
};

