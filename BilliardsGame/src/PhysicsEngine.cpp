#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(EntityManager& entityManager)
	: mEntityManager(entityManager)
{
}

void PhysicsEngine::Update(float deltaTime)
{
	// Put all of the logic here
}



void PhysicsEngine::MoveBalls(float deltaTime)
{
	std::vector<std::unique_ptr<Ball>>& balls = mEntityManager.GetBallVector();

	for (auto& ball : balls)
	{
		ball->updatePosition(deltaTime);
	}
}

void PhysicsEngine::Collisions(float deltaTime)
{

}

void PhysicsEngine::BallVsTable(float deltaTime)
{
	std::vector<std::unique_ptr<Ball>>& balls = mEntityManager.GetBallVector();
	auto& tableRect = mEntityManager.getTable().getRect();
	
	for (auto& ball : balls)
	{
		double ballVelX = ball->getVelocity().getx();
		double ballVelY = ball->getVelocity().gety(); 

		if (ball->getPosition().gety() - ball->getRadius() > tableRect.getGlobalBounds().top)
		{
			ball->setVelocity(Vec2{ballVelX, ballVelY * -1});
		}
		if (ball->getPosition().gety() + ball->getRadius() > tableRect.getGlobalBounds().height)
		{
			ball->setVelocity(Vec2{ ballVelX, ballVelY * -1 });
		}
		if (ball->getPosition().getx() - ball->getRadius() > tableRect.getGlobalBounds().left)
		{
			ball->setVelocity(Vec2{ ballVelX * -1, ballVelY });
		}
		if (ball->getPosition().getx() + ball->getRadius() > tableRect.getGlobalBounds().width)
		{
			ball->setVelocity(Vec2{ ballVelX * -1, ballVelY });
		}
	}
}

void PhysicsEngine::BallVsBall(float deltaTime)
{
}

bool PhysicsEngine::AreBallsAtRest()
{
	bool atRest = true;
	std::vector<std::unique_ptr<Ball>>& balls = mEntityManager.GetBallVector();
	for (auto& ball : balls)
	{
		if (ball->getVelocity().getx() != 0)
		{
			atRest = false;
		}
		if (ball->getVelocity().gety() != 0)
		{
			atRest = false;
		}
	}
	
	return atRest;
}


