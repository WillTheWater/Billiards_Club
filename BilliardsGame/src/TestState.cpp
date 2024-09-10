#include "TestState.h"

TestState::TestState()
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
	game.GetPhysicsEngine().Update(deltaTime);
}

void TestState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	game.GetRenderManager().RenderTable();
	game.GetRenderManager().RenderBalls();
	game.GetWindow().display();
}
