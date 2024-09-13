#pragma once

class Game;

class InputManager
{
public:
	InputManager() = delete; 

	InputManager(Game& game);

	Vec2 getMousePos();

	Vec2 getCueBallPos();

	Vec2 GetVecMouseToCueBall();

	Vec2 GetPositionForCueOnBall();

	bool IsMouseOverCueBall();

	bool IsMouseButtonDown();

	void debugCueOutline();

	float getAngleCueballToMouse();

	float distanceFromCueToBall();	// Returns the distance from the tip of the cue to the edge of the ball

private:
	Game& mGameRef; 
	bool mMouseHeld;
	bool mCueBallSelected;
};

