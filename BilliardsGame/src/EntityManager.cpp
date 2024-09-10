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
	CreateDebugCollisionLine();
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

void EntityManager::CreateDebugCollisionLine()
{
	float v1x = Random::getRandomFloat(mTable->getLeftBound(), mTable->getRightBound());
	float v1y = Random::getRandomFloat(mTable->getTopBound(), mTable->getBottomBound());
	float v2x = Random::getRandomFloat(mTable->getLeftBound(), mTable->getRightBound());
	float v2y = Random::getRandomFloat(mTable->getTopBound(), mTable->getBottomBound());

	sf::Vector2f vertex1 (v1x, v1y);
	sf::Vector2f vertex2 (v2x, v2y);
	sf::VertexArray vArr (sf::Lines, 2);
	vArr[0] = vertex1;
	vArr[1] = vertex2;

	mPolygon = vArr;
}

sf::VertexArray& EntityManager::getDebugCollisionLine()
{
	return mPolygon;
}

std::vector<std::unique_ptr<Ball>>& EntityManager::GetBallVector()
{
	return mBalls;
}

Table& EntityManager::getTable()
{
	return *mTable;
}
