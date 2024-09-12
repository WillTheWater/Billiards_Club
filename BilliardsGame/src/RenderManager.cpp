#include "Game.h"

RenderManager::RenderManager(Game& game)
	:mGameRef{game}
{
	mRenderMode.blendMode = sf::BlendAlpha;
	// This doesn't work
	//mRenderMode.blendMode.alphaSrcFactor = sf::BlendMode::Factor(0.2);
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

	sf::CircleShape overlayCircle;
	overlayCircle.setOrigin(PoolBall::radius, PoolBall::radius);
	overlayCircle.setRadius(PoolBall::radius);
	overlayCircle.setTexture(&textureManager.getBallOverlay());

	for (auto& ball : balls) // Loop through the vector of balls
	{
		if (ball->isVisible())
		{
			overlayCircle.setPosition(ball->getCircle().getPosition());
			window.draw(ball->getCircle());
			window.draw(overlayCircle, mRenderMode);
			BallId id = ball->getId();
			
			if (id != BallId_cueBall)
			{
				auto& tagSprite = ball->getTagSprite();
				tagSprite.setPosition(ball->getCircle().getPosition());
				window.draw(tagSprite);
				
			}
			
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
			float velx = ball->getVelocity().getx();
			float vely = ball->getVelocity().gety();
			float vel_linex = velx;
			float vel_liney = vely;

			float xPos = ball->getPosition().getx();
			float yPos = ball->getPosition().gety();


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
	auto& polygon = entityManager.getDebugConvexShape();
	polygon.setFillColor(sf::Color(0, 0, 0, 0));
	polygon.setOutlineColor(sf::Color::White);
	polygon.setOutlineThickness(1);
	window.draw(polygon);
}
