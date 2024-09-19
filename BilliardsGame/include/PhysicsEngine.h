#pragma once
#include <algorithm>
#include "Ball.h"
#include "Random.h" // For debug randomization of balls

class Game;

class PhysicsEngine
{
public:
	// Constructors
	PhysicsEngine() = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;
	PhysicsEngine(Game& game);

	// Public Functions
	void Update(float deltaTime);
	void HandleCollisions();
	bool AreBallsAtRest();
	void ApplyStrikeVelocityToCueBall(Vec2 unitVec, float scale);
	void FixCueBallResetOnBall();

	// Debug Functions
	void debugRandomizeBalls();

private:
	// Member Variables
	Game& mGameRef;
	int mSimUpdates;
	float mStepTime;
	int mMaxSimSteps;
	float mFrictionScale; 

	// Private Functions
	void calculateStepTime(float deltaTime);
	void initializeSimTimeForBalls();
	void resetPreviousPositionForBalls();
	void UpdateSimTimeForBalls();
	void MoveBalls();
	void Handle_BvTableRect();
	void Handle_BvB();
	void BvB_ResolvePosition(Ball& b1, Ball& b2);
	void BvB_ResolveVelocity(Ball& b1, Ball& b2);
	bool doBallsOverlap(const Ball& b1, const Ball& b2) const;
	void HandleBallVsPolygons();
	void BallVsPolygon(Ball& b, const sf::ConvexShape& polygon);
	void HandleBallInPocket();
	void ApplyFriction();
	void ClampBallVelocity();

	void ApplyFrictionCoEff();

	float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	float length(const sf::Vector2f& v);
	sf::Vector2f normalize(const sf::Vector2f& v);
	int soundDelayCounter; 
	bool mSoundPlayed;


};

