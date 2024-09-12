#include "TestState.h"

TestState::TestState(Game& game)
	:mGame(game)
{

}

void TestState::HandleInput(Game& game)
{
	sf::Event event;
	while (game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			game.GetPhysicsEngine().debugRandomizeBalls();
			
		}
	}
}

void TestState::Update(Game& game, float deltaTime)
{
	game.GetWindow().clear(sf::Color::Black);
	game.GetPhysicsEngine().Update(deltaTime);
}

void TestState::Draw(Game& game)
{
	game.GetRenderManager().RenderTable();
	game.GetRenderManager().RenderBalls();
	game.GetRenderManager().DebugBallVectors();
	//game.GetRenderManager().DrawDebugCollisionPoly();
	game.GetRenderManager().DrawDebugConvexShape();
	game.GetWindow().display();
}
