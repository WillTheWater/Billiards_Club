#include "EntityManager.h"


EntityManager::EntityManager()
{
}

void EntityManager::InitializeAssets()
{
	CreateBalls();
	CreateTable();
}

void EntityManager::CreateBalls()
{
	for (size_t i{ 0 }; i < BallId_MAX_BALL_ID; i++)
	{
		mBalls.push_back(
			std::make_unique<Ball>(static_cast<BallId>(i), PoolBall::radius, NULL, NULL, NULL)
			);
	}
	assert(mBalls.size() == BallId::BallId_MAX_BALL_ID && "EntityManager::CreateBalls, vector size != BallId_MAX_BALL_ID");
}

void EntityManager::CreateTable()
{
	mTable = std::make_unique<Table>(PoolTable::width, PoolTable::height);
}

std::vector<std::unique_ptr<Ball>>& EntityManager::GetBallVector()
{
	return mBalls;
}

Table& EntityManager::getTable()
{
	return *mTable;
}
