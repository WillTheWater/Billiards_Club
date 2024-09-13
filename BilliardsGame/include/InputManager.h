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


private:
	Game& mGameRef; 
	bool mMouseHeld;
	bool mCueBallSelected;
};

