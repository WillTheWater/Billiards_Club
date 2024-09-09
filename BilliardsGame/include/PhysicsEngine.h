#pragma once

#include "EntityManager.h"

class PhysicsEngine
{
public:
	PhysicsEngine() = delete;

	PhysicsEngine(EntityManager& entityManager);

	void Update(float deltaTime);

	void MoveBalls(float deltaTime);

	void Collisions(float deltaTime);

	void BallVsTable(float deltaTime);

	void BallVsBall(float deltaTime);

	bool AreBallsAtRest();



private:
	EntityManager& mEntityManager;
};

