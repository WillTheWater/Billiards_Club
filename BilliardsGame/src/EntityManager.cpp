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
	CreateDebugConvexShape();
}

void EntityManager::CreateBalls()
{

	// DEBUG DELETE LATER

	mBalls.push_back(
		std::make_unique<Ball>(static_cast<BallId>(0), PoolBall::radius, NULL, NULL, NULL)
	);

	// !DEBUG

	for (size_t i{ 0 }; i < BallId_MAX_BALL_ID; i++)
	{
		mBalls.push_back(
			std::make_unique<Ball>(static_cast<BallId>(i), PoolBall::radius, NULL, NULL, NULL)
			);

		mBalls[i]->setPosition(Vec2{ 
			(float)PoolTable::width /2, 
			(float)PoolTable::height /2 
			});

		
	}
	//assert(mBalls.size() == BallId::BallId_MAX_BALL_ID && "EntityManager::CreateBalls, vector size != BallId_MAX_BALL_ID");
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

	sf::Vector2f vertex0 (v1x, v1y);
	sf::Vector2f vertex1 (v2x, v2y);
	sf::Vector2f vertex2 = vertex0;

	sf::VertexArray vArr (sf::LineStrip, 2);
	vArr[0] = vertex0;
	vArr[1] = vertex1;
	//vArr[2] = vertex2;

	mPolygon = vArr;
}

void EntityManager::CreateDebugCollisionBox()
{

	/*sf::ConvexShape polygon;
	polygon.setPointCount(3);
	polygon.setPoint(0, sf::Vector2f(0, 0));
	polygon.setPoint(1, sf::Vector2f(0, 10));
	polygon.setPoint(2, sf::Vector2f(25, 5));
	polygon.setOutlineColor(sf::Color::Red);
	polygon.setOutlineThickness(5);
	polygon.setPosition(10, 20);*/

	// Top
	sf::Vertex vertex0{ sf::Vector2f(600, 600) };
	sf::Vertex vertex1{ sf::Vector2f(650, 600) };
	sf::Vertex vertex2{ sf::Vector2f(700, 600) };
	sf::Vertex vertex3{ sf::Vector2f(750, 600) };
	sf::Vertex vertex4{ sf::Vector2f(800, 600) };

	// Right
	sf::Vertex vertex5{ sf::Vector2f(800, 650) };
	sf::Vertex vertex6{ sf::Vector2f(800, 700) };
	sf::Vertex vertex7{ sf::Vector2f(800, 750) };
	sf::Vertex vertex8{ sf::Vector2f(800, 800) };

	// Bottom 
	sf::Vertex vertex9{ sf::Vector2f(750, 800) };
	sf::Vertex vertex10{ sf::Vector2f(700, 800) };
	sf::Vertex vertex11{ sf::Vector2f(650, 800) };
	sf::Vertex vertex12{ sf::Vector2f(600, 800) };

	// Left
	sf::Vertex vertex13{ sf::Vector2f(600, 750) };
	sf::Vertex vertex14{ sf::Vector2f(600, 700) };
	sf::Vertex vertex15{ sf::Vector2f(600, 650) };
	sf::Vertex vertex16{ sf::Vector2f(600, 600) };

	sf::Vertex vertex17{ vertex0 };


	sf::VertexArray vArr(sf::LineStrip, 17);
	vArr[0] = vertex0;
	vArr[1] = vertex1;
	vArr[2] = vertex2;
	vArr[3] = vertex3;
	vArr[4] = vertex4;
	vArr[5] = vertex5;
	vArr[6] = vertex6;
	vArr[7] = vertex7;
	vArr[8] = vertex8;
	vArr[9] = vertex9;
	vArr[10] = vertex10;
	vArr[11] = vertex11;
	vArr[12] = vertex12;
	vArr[13] = vertex13;
	vArr[14] = vertex14;
	vArr[15] = vertex15;
	vArr[16] = vertex16;

	mPolygon = vArr;
}

void EntityManager::CreateDebugConvexShape()
{
	/*sf::ConvexShape polygon;
	polygon.setPointCount(3);
	polygon.setPoint(0, sf::Vector2f(400, 400));
	polygon.setPoint(1, sf::Vector2f(400, 800));
	polygon.setPoint(2, sf::Vector2f(800, 600));
	polygon.setOutlineColor(sf::Color::Red);
	polygon.setOutlineThickness(2);*/


	sf::ConvexShape polygon;
	polygon.setPointCount(10);
	float polygonRadius = 200.f;
	sf::Vector2f polygonCenter(400.f, 300.f);
	for (int i = 0; i < 10; ++i) {
		float angle = i * (2 * 3.14159f / 10.f);
		float x = 200 + polygonRadius * std::cos(angle);
		float y = 200 + polygonRadius * std::sin(angle);
		polygon.setPoint(i, sf::Vector2f(polygonCenter.x + x, polygonCenter.y + y));
	}
	//polygon.move({ 200,200 });

	mConvexShape = polygon;
}

sf::VertexArray& EntityManager::getDebugCollisionLine()
{
	return mPolygon;
}

sf::ConvexShape& EntityManager::getDebugConvexShape()
{
	return mConvexShape;
}

std::vector<std::unique_ptr<Ball>>& EntityManager::GetBallVector()
{
	return mBalls;
}

Table& EntityManager::getTable()
{
	return *mTable;
}
