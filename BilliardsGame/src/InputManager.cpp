#include "Game.h"

InputManager::InputManager(Game& game)
	:mGameRef{game}
	,mCueBallSelected{false}
	,mMouseHeld{false}
	,mMaxDistanceForCueStick{300}
{
}

Vec2 InputManager::getMousePos()
{
	auto& window = mGameRef.GetWindow();
	return Vec2{ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y};
}

Vec2 InputManager::getCueBallPos()
{
	auto& cueball = mGameRef.GetEntityManager().getCueBall();
	return cueball.getPosition();
}

Vec2 InputManager::GetVecMouseToCueBall() 
{
	return getCueBallPos() - getMousePos();
}

Vec2 InputManager::GetPositionForCueOnBall()
{
	Vec2 ballPos {getCueBallPos() };
	Vec2 ballToCue{ GetVecMouseToCueBall() };

	// Get the unit vector of ballToCue
	Vec2 ballToCueUnit = ballToCue / ballToCue.magnitude();

	// Make ballToCue the length of the ball radius
	Vec2 offsetToBallEdge = ballToCueUnit * PoolBall::radius;

	// Apply the offset to ballposition so that it's on the edge
	Vec2 cueOnBall = ballPos - offsetToBallEdge;

	//If you make the cue have this position, the tip will be on the very edge of the cue ball. 
	return cueOnBall;
}

void InputManager::updateCueStick()
{
	auto& cuestick = mGameRef.GetEntityManager().getCueStick();
	auto& powerBar = cuestick.getPowerBar();
	if (IsMouseOverCueBall())
	{
		cuestick.setPosition(GetPositionForCueOnBall());
		powerBar.setScale(0, powerBar.getScale().y);
	}
	else
	{
		cuestick.setPosition(getMousePos());
		powerBar.setScale(distanceFromCueToBall(), powerBar.getScale().y);
		sf::Uint8 colorScale = std::clamp(distanceFromCueToBall(), 0.f, 255.f);
		sf::Uint8 otherColor = (255 - colorScale);
		sf::Color powerBarColor{ colorScale, otherColor, otherColor };
		powerBar.setFillColor(powerBarColor);
	}

	if (distanceFromCueToBall() < mMaxDistanceForCueStick)
	{
		cuestick.toggleVisiblity(true);
	}
	else
	{
		cuestick.toggleVisiblity(false);
	}

	cuestick.setRotationDegrees(getAngleCueballToMouse());
}

void InputManager::giveCueBallStrikeVelocity()
{
	auto& cuestick = mGameRef.GetEntityManager().getCueStick();
	Vec2 strikeVelocity = cuestick.getStrikeVelocity();
	auto& physicsEngine = mGameRef.GetPhysicsEngine();
	physicsEngine.ApplyStrikeVelocityToCueBall(strikeVelocity, 500);
}

void InputManager::initialiazeCueStickAnim(int steps)
{
	auto& cuestick = mGameRef.GetEntityManager().getCueStick();
	cuestick.setPosition(getMousePos());
	cuestick.setRotationDegrees(getAngleCueballToMouse());
	cuestick.setAnimVectors(getMousePos(), GetPositionForCueOnBall(), steps);
}

bool InputManager::IsMouseOverCueBall()
{
	Vec2 mousePos = getMousePos();
	Vec2 cueBallPos = getCueBallPos();
	if (mousePos.distance(cueBallPos) < (float)PoolBall::radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IsMouseButtonDown()
{
	return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void InputManager::debugCueOutline()
{
	auto& cueball = mGameRef.GetEntityManager().getCueBall();
	if (IsMouseOverCueBall())
	{
		cueball.toggleOutline(true);
	}
	else
	{
		cueball.toggleOutline(false);
	}
}

float InputManager::getAngleCueballToMouse()
{
	Vec2 mousePos = getMousePos();
	Vec2 ballPos = getCueBallPos();
	Vec2 mouseToBall = ballPos - mousePos;
	float angle = mouseToBall.angleInDegrees();
	// Apply this angle to the cueball and it will point from mouse to the cue ball
	return angle;
}

float InputManager::distanceFromCueToBall()
{
	Vec2 mousePos = getMousePos();
	Vec2 ballPos = getCueBallPos();
	Vec2 ballToCue = GetVecMouseToCueBall();
	float distance = ballToCue.magnitude() - PoolBall::radius;
	return distance; 
}

bool InputManager::isMouseInShootingRange()
{
	if (distanceFromCueToBall() < mMaxDistanceForCueStick)
	{
		return true;
	}

	return false;
}


