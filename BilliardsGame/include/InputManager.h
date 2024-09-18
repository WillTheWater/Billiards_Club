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

	void updateCueStick();	// Sets the cue stick for rendering during input polling;

	void giveCueBallStrikeVelocity();

	void initialiazeCueStickAnim(int steps);	// Initialize the cuestick animation with the number of steps to play

	bool IsMouseOverCueBall();

	bool IsMouseButtonDown();

	void debugCueOutline();

	float getAngleCueballToMouse();

	float distanceFromCueToBall();	// Returns the distance from the tip of the cue to the edge of the ball

	bool isMouseInShootingRange();

private:
	Game& mGameRef; 
	float mMaxDistanceForCueStick; // The maximum distance the mouse can be from the cuestick for it to be displayed
	bool mMouseHeld;
	bool mCueBallSelected;
};

