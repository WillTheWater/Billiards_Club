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

	tableRect.setFillColor(sf::Color(0,0,0,0));
	tableRect.setOutlineThickness(5);
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

void RenderManager::DebugBallVectors()
{
	auto& window = mGameRef.GetWindow();
	auto& entityManager = mGameRef.GetEntityManager();
	auto& balls = entityManager.GetBallVector();

	for (auto& ball : balls)	// Loop through the vector of balls
	{
		if (ball->isVisible())
		{
			double velx = ball->getVelocity().getx();
			double vely = ball->getVelocity().gety();
			double vel_linex = 0.3 * velx;
			double vel_liney = 0.3 * vely;

			double xPos = ball->getPosition().getx();
			double yPos = ball->getPosition().gety();


			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = sf::Vector2f(xPos,yPos);
			lines[0].color = sf::Color::Cyan;
			lines[1].position = sf::Vector2f(xPos + vel_linex, yPos + vel_liney);
			lines[1].color = sf::Color::Cyan;
			window.draw(lines);
		}
	}
}

void RenderManager::DrawDebugCollisionPoly()
{
	auto& window = mGameRef.GetWindow();
	auto& entityManager = mGameRef.GetEntityManager();
	auto& poly = entityManager.getDebugCollisionLine();
	for (size_t i{ 0 }; i < poly.getVertexCount(); i++)
	{
		poly[i].color = sf::Color::Magenta;
	}
	window.draw(poly);
}

void RenderManager::DrawDebugConvexShape()
{
	auto& window = mGameRef.GetWindow();
	auto& entityManager = mGameRef.GetEntityManager();
	auto& poly = entityManager.getDebugConvexShape();
	window.draw(poly);
}
