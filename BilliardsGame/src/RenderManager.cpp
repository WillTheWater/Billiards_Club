#include "Game.h"

RenderManager::RenderManager(Game& game)
	:mGameRef{game}
{
}

void RenderManager::RenderTable()
{
	auto& window = mGameRef.GetWindow();
	auto& entityManager = mGameRef.GetEntityManager();
	auto& textureManager = mGameRef.GetTextureManager();
	auto& tableRect = entityManager.getTable().getRect();

	tableRect.setFillColor(sf::Color::Green);
	window.draw(tableRect);
}

void RenderManager::RenderBalls()
{
	auto& window = mGameRef.GetWindow();
	auto& entityManager = mGameRef.GetEntityManager();
	auto& textureManager = mGameRef.GetTextureManager();
	auto& tableRect = entityManager.getTable().getRect();
	
	auto& balls = entityManager.GetBallVector();

	for (auto& ball : balls)	// Loop through the vector of balls
	{
		if (ball->isVisible())
		{
			ball->getCircle().setFillColor(sf::Color::Red);
			window.draw(ball->getCircle());
		}
	}

}
