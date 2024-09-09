#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include "Ball.h"
#include "Table.h"
#include "EntityGlobals.h"


class EntityManager
{
public:
	EntityManager();
	~EntityManager() = default;

	EntityManager& operator=(const EntityManager&) = delete;

	void InitializeAssets();

	void CreateBalls();

	void CreateTable();

	std::vector<std::unique_ptr<Ball>>& GetBallVector();

	Table& getTable();




private: 
	std::vector<std::unique_ptr<Ball>> mBalls; 
	std::unique_ptr<Table> mTable;
};