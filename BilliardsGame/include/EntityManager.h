#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "Ball.h"
#include "Table.h"
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
	Table& getTable();
	
	//FUNCTIONS
	void InitializeAssets();
	void CreateBalls();
	void RackBalls();
	void CreateTable();
	void CreateCollisionPolygons();


	//DEBUG
	void CreateDebugCollisionLine();
	void CreateDebugCollisionBox();
	void CreateDebugConvexShape();
	sf::VertexArray& getDebugCollisionLine();
	sf::ConvexShape& getDebugConvexShape();

private: 
	Game& mGameRef;
	std::vector<std::unique_ptr<Ball>> mBalls; 
	std::unique_ptr<Table> mTable;
	sf::ConvexShape mCollisionPolygon;

	// Debugs
	sf::VertexArray mDebugCollisionLines;


};