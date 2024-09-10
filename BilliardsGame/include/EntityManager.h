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

	void InitializeAssets();

	void CreateBalls();

	void CreateTable();

	void CreateDebugCollisionLine();

	sf::VertexArray& getDebugCollisionLine();

	std::vector<std::unique_ptr<Ball>>& GetBallVector();

	Table& getTable();

private: 
	Game& mGameRef;
	std::vector<std::unique_ptr<Ball>> mBalls; 
	std::unique_ptr<Table> mTable;
	sf::VertexArray mPolygon;	// For debug
};