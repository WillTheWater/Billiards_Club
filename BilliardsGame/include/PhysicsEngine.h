#pragma once
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
	void HandleCollisions(float deltaTime);
	bool AreBallsAtRest();

	// Debug Functions
	void debugRandomizeBalls();

private:
	// Member Variables
	Game& mGameRef;

	// Private Functions
	void MoveBalls(float deltaTime);
	void Handle_BvTableRect(float deltaTime);
	void Handle_BvB(float deltaTime);
	void BvB_ResolvePosition(Ball& b1, Ball& b2);
	void BvB_ResolveVelocity(Ball& b1, Ball& b2);
	bool doBallsOverlap(const Ball& b1, const Ball& b2) const;
	void HandleBallVsPolygons();
	void BallVsPolygon(Ball& b, const sf::VertexArray& polygon);
	
	void BallVsPolygonStolen(Ball& b, const sf::ConvexShape& polygon);

	float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	float length(const sf::Vector2f& v);
	sf::Vector2f normalize(const sf::Vector2f& v);

	

};

