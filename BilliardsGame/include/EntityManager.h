#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "Ball.h"
#include "Table.h"
#include "CueStick.h"
#include "EntityGlobals.h"

class Game;

class EntityManager
{
public:
	EntityManager() = delete;
	EntityManager(Game& game);
	~EntityManager() = default;
	EntityManager& operator=(const EntityManager&) = delete;

	// GETTERS
	std::vector<std::unique_ptr<Ball>>& GetBallVector();
	Ball& getCueBall();
	Table& getTable();
	CueStick& getCueStick();
	
	//FUNCTIONS
	void InitializeAssets();
	void CreateBalls();
	void RackBalls();
	void CreateCueStick();
	void CreateTable();
	void CreateCollisionPolygons();
	void CreatePockets();


	//DEBUG
	void CreateDebugCollisionLine();
	void CreateDebugCollisionBox();
	void CreateDebugConvexShape();
	sf::VertexArray& getDebugCollisionLine();
	sf::ConvexShape& getDebugConvexShape();

private: 
	Game& mGameRef;
	std::vector<std::unique_ptr<Ball>> mBalls; 
	std::vector<sf::CircleShape> mPockets;
	std::unique_ptr<Table> mTable;
	std::unique_ptr<CueStick> mCueStick;
	sf::ConvexShape mCollisionPolygon;

	// Debugs
	sf::VertexArray mDebugCollisionLines;


};