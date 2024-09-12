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
	CreateCollisionPolygons();
	RackBalls();
}

void EntityManager::CreateBalls()
{
	auto& textureManager = mGameRef.GetTextureManager();

	for (size_t i{ 0 }; i < BallId::BallId_MAX_BALL_ID; i++)
	{
		mBalls.push_back(
			std::make_unique<Ball>(static_cast<BallId>(i), PoolBall::radius, NULL, NULL, NULL)
			);

		mBalls[i]->setPosition(Vec2{ 
			(float)PoolTable::width /2, 
			(float)PoolTable::height /2 
			});

		mBalls[i]->getCircle().setTexture(&textureManager.getBallTexture(static_cast<BallId>(i)));
		if (i != BallId::BallId_cueBall)
		{
			auto& tagTexture = textureManager.getBallTag(static_cast<BallId>(i));
			mBalls[i]->getTagSprite().setTexture(tagTexture);
			mBalls[i]->getTagSprite().setOrigin(tagTexture.getSize().x /2, tagTexture.getSize().y / 2);
			mBalls[i]->getTagSprite().setScale(PoolBall::tagScale, PoolBall::tagScale);
		}
		
	}
	assert(mBalls.size() == BallId::BallId_MAX_BALL_ID && "EntityManager::CreateBalls, vector size != BallId_MAX_BALL_ID");
}

void EntityManager::RackBalls()
{
	float tableTop = mTable->getLeftBound();
	float tableBottom = mTable->getBottomBound();
	float tableLeft = mTable->getLeftBound();
	float tableRight = mTable->getRightBound();
	float radius = PoolBall::radius;

	const Vec2 TriangleOffsetDown{ ((radius + radius) * (float)std::cos(0.523599)), ((radius + radius) * (float)std::sin(0.523599)) };
	const Vec2 TriangleOffsetUp{((radius + radius) * (float)std::cos(-0.523599)), ((radius + radius) * (float)std::sin(-0.523599)) };

	// Cueball
	int ball0 = BallId_cueBall;
	// Row 1
	int ball1 = BallId_one;
	// Row 2
	int ball2 = BallId_nine;
	int ball3 = BallId_two;
	// Row 3
	int ball4 = BallId_ten;
	int ball5 = BallId_eight;
	int ball6 = BallId_three;
	// Row 4
	int ball7 = BallId_eleven;
	int ball8 = BallId_seven;
	int ball9 = BallId_fourteen;
	int ball10 = BallId_four;
	// Row 5
	int ball11 = BallId_five;
	int ball12 = BallId_thirteen;
	int ball13 = BallId_fifteen;
	int ball14 = BallId_six;
	int ball15 = BallId_twelve;

	// Cueball
	mBalls[ball0]->setPosition({ tableLeft + 330, tableBottom / 2 });

	// First row of rack
	mBalls[ball1]->setPosition({ tableLeft + 870, tableBottom / 2 });

	// Second row of rack
	mBalls[ball2]-> setPosition({  mBalls[ball1]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball1]->getPosition().gety() + TriangleOffsetUp.gety()});
	mBalls[ball3]-> setPosition({  mBalls[ball1]->getPosition().getx() + TriangleOffsetDown.getx(),		mBalls[ball1]->getPosition().gety() + TriangleOffsetDown.gety() });

	// Third row of rack
	mBalls[ball4]->setPosition({   mBalls[ball2]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball2]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball5]->setPosition({   mBalls[ball3]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball3]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball6]->setPosition({   mBalls[ball3]->getPosition().getx() + TriangleOffsetDown.getx(),		mBalls[ball3]->getPosition().gety() + TriangleOffsetDown.gety() });

	// Fourth row of rack
	mBalls[ball7]->setPosition({   mBalls[ball4]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball4]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball8]->setPosition({   mBalls[ball5]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball5]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball9]->setPosition({   mBalls[ball6]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball6]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball10]->setPosition({  mBalls[ball6]->getPosition().getx() + TriangleOffsetDown.getx(),		mBalls[ball6]->getPosition().gety() + TriangleOffsetDown.gety() });

	// Fifth row of rack
	mBalls[ball11]->setPosition({  mBalls[ball7]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball7]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball12]->setPosition({  mBalls[ball8]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball8]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball13]->setPosition({  mBalls[ball9]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball9]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball14]->setPosition({  mBalls[ball10]->getPosition().getx() + TriangleOffsetUp.getx(),		mBalls[ball10]->getPosition().gety() + TriangleOffsetUp.gety() });
	mBalls[ball15]->setPosition({  mBalls[ball10]->getPosition().getx() + TriangleOffsetDown.getx(),	mBalls[ball10]->getPosition().gety() + TriangleOffsetDown.gety() });

}

void EntityManager::CreateTable()
{
	mTable = std::make_unique<Table>(PoolTable::width, PoolTable::height);
	mTable->setOrigin(PoolTable::width / 2, PoolTable::height / 2);
	mTable->setPosition(mGameRef.GetWindowSize().x / 2, mGameRef.GetWindowSize().y / 2);
}



void EntityManager::CreateCollisionPolygons()
{
	sf::ConvexShape polygon;

	polygon.setPointCount(40);
	polygon.setPoint(0, sf::Vector2f(200, 150));
	polygon.setPoint(1, sf::Vector2f(285, 150));
	polygon.setPoint(2, sf::Vector2f(285, 200));
	polygon.setPoint(3, sf::Vector2f(315, 220));
	polygon.setPoint(4, sf::Vector2f(760, 220));
	polygon.setPoint(5, sf::Vector2f(765, 200));
	polygon.setPoint(6, sf::Vector2f(765, 150));
	polygon.setPoint(7, sf::Vector2f(835, 150));
	polygon.setPoint(8, sf::Vector2f(835, 200));
	polygon.setPoint(9, sf::Vector2f(840, 220));
	polygon.setPoint(10, sf::Vector2f(1285, 220));
	polygon.setPoint(11, sf::Vector2f(1315, 200));
	polygon.setPoint(12, sf::Vector2f(1315, 150));
	polygon.setPoint(13, sf::Vector2f(1400, 150));
	polygon.setPoint(14, sf::Vector2f(1400, 235));
	polygon.setPoint(15, sf::Vector2f(1350, 235));
	polygon.setPoint(16, sf::Vector2f(1330, 265));
	polygon.setPoint(17, sf::Vector2f(1330, 635));
	polygon.setPoint(18, sf::Vector2f(1350, 665));
	polygon.setPoint(19, sf::Vector2f(1400, 665));
	polygon.setPoint(20, sf::Vector2f(1400, 750));
	polygon.setPoint(21, sf::Vector2f(1315, 750));
	polygon.setPoint(22, sf::Vector2f(1315, 700));
	polygon.setPoint(23, sf::Vector2f(1285, 680));
	polygon.setPoint(24, sf::Vector2f(840, 680));
	polygon.setPoint(25, sf::Vector2f(835, 700));
	polygon.setPoint(26, sf::Vector2f(835, 750));
	polygon.setPoint(27, sf::Vector2f(765, 750));
	polygon.setPoint(28, sf::Vector2f(765, 700));
	polygon.setPoint(29, sf::Vector2f(760, 680));
	polygon.setPoint(30, sf::Vector2f(315, 680));
	polygon.setPoint(31, sf::Vector2f(285, 700));
	polygon.setPoint(32, sf::Vector2f(285, 750));
	polygon.setPoint(33, sf::Vector2f(200, 750));
	polygon.setPoint(34, sf::Vector2f(200, 665));
	polygon.setPoint(35, sf::Vector2f(250, 665));
	polygon.setPoint(36, sf::Vector2f(270, 635));
	polygon.setPoint(37, sf::Vector2f(270, 265));
	polygon.setPoint(38, sf::Vector2f(250, 235));
	polygon.setPoint(39, sf::Vector2f(200, 235));

	mCollisionPolygon = polygon;
}

std::vector<std::unique_ptr<Ball>>& EntityManager::GetBallVector()
{
	return mBalls;
}

Table& EntityManager::getTable()
{
	return *mTable;
}

// DEBUG:

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

	mDebugCollisionLines = vArr;
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

	mDebugCollisionLines = vArr;
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

	mCollisionPolygon = polygon;
}

sf::VertexArray& EntityManager::getDebugCollisionLine()
{
	return mDebugCollisionLines;
}

sf::ConvexShape& EntityManager::getDebugConvexShape()
{
	return mCollisionPolygon;
}

