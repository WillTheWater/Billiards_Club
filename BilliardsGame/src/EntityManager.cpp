#include "Game.h"


EntityManager::EntityManager(Game& game)
	:mGameRef{game}
{
	InitializeAssets();
}

void EntityManager::InitializeAssets()
{
	CreateTable();
	CreateBalls();
}

void EntityManager::CreateBalls()
{
	for (size_t i{ 0 }; i < BallId_MAX_BALL_ID; i++)
	{
		mBalls.push_back(
			std::make_unique<Ball>(static_cast<BallId>(i), PoolBall::radius, NULL, NULL, NULL)
			);

		mBalls[i]->setPosition(Vec2{ 
			(double)PoolTable::width /2, 
			(double)PoolTable::height /2 
			});

		
	}
	assert(mBalls.size() == BallId::BallId_MAX_BALL_ID && "EntityManager::CreateBalls, vector size != BallId_MAX_BALL_ID");
}

void EntityManager::CreateTable()
{
	mTable = std::make_unique<Table>(PoolTable::width, PoolTable::height);
	mTable->setOrigin(PoolTable::width / 2, PoolTable::height / 2);
	mTable->setPosition(mGameRef.GetWindowSize().x / 2, mGameRef.GetWindowSize().y / 2);
}

std::vector<std::unique_ptr<Ball>>& EntityManager::GetBallVector()
{
	return mBalls;
}

Table& EntityManager::getTable()
{
	return *mTable;
}
