#include "Game.h"

PhysicsEngine::PhysicsEngine(Game& game)
	: mGameRef{game}
{
}

void PhysicsEngine::Update(float deltaTime)
{
	MoveBalls(deltaTime);
	HandleCollisions(deltaTime);
}

void PhysicsEngine::MoveBalls(float deltaTime)
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();

	for (auto& ball : balls)
	{
		ball->updatePosition(deltaTime);
	}
}

bool PhysicsEngine::doBallsOverlap(const Ball& b1, const Ball& b2) const
{
	// Uses Vec2 distance function to get distance between b1 and b2
	double distance = b1.getPosition().distance( 
		b2.getPosition() 
	);

	// If distance is less than b1 + b2 radius, they intercept
	return (distance < b1.getRadius() + b2.getRadius());
}

void PhysicsEngine::HandleBallVsPolygons()
{
	auto& polygon = mGameRef.GetEntityManager().getDebugCollisionLine();
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();

	// Lines added for stolen code
	auto& convexShape = mGameRef.GetEntityManager().getDebugConvexShape();

	for (auto& b : balls)
	{
		//BallVsPolygon(*b, polygon);
		BallVsPolygonStolen(*b, convexShape);
	}
}

void PhysicsEngine::debugRandomizeBalls()
{
	auto& balls = mGameRef.GetEntityManager().GetBallVector();
	auto& rect = mGameRef.GetEntityManager().getTable();
	float upperBound = rect.getTopBound();
	float lowerBound = rect.getBottomBound();
	float leftBound = rect.getLeftBound();
	float rightBound = rect.getRightBound();

	for (auto& ball : balls)
	{
		float radius = ball->getRadius();
		Vec2 ranVel = Random::getRandomVec2(-500, 500, -500, 500);
		
		Vec2 ranPos = Random::getRandomVec2(
			(int)leftBound,
			(int)rightBound,
			(int)upperBound,
			(int)lowerBound
		);
		ball->setVelocity(ranVel);
		ball->setPosition(ranPos);
	}
}

void PhysicsEngine::HandleCollisions(float deltaTime)
{
	Handle_BvTableRect(deltaTime);
	Handle_BvB(deltaTime);
	HandleBallVsPolygons();
}

void PhysicsEngine::Handle_BvTableRect(float deltaTime)
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	auto& table = mGameRef.GetEntityManager().getTable();

	double topEdge = table.getTopBound();
	double bottomEdge = table.getBottomBound();
	double leftEdge = table.getLeftBound();
	double rightEdge = table.getRightBound();
	
	for (auto& ball : balls)
	{
		double ballVelX = ball->getVelocity().getx();
		double ballVelY = ball->getVelocity().gety(); 
		double ballPosX = ball->getPosition().getx();
		double ballPosY = ball->getPosition().gety();
		float radius = ball->getRadius();

		if (ballPosY - radius < topEdge)
		{
			ball->setPosition({ ballPosX, topEdge + radius });
			ball->setVelocity(Vec2{ballVelX, ballVelY * -1});
		}
		if (ballPosY + radius > bottomEdge)
		{
			ball->setPosition({ ballPosX, bottomEdge - radius });
			ball->setVelocity(Vec2{ ballVelX, ballVelY * -1 });
		}
		if (ballPosX - radius < leftEdge)
		{
			ball->setPosition({ leftEdge + radius, ballPosY});
			ball->setVelocity(Vec2{ ballVelX * -1, ballVelY });
		}
		if (ballPosX + radius > rightEdge)
		{
			ball->setPosition({ rightEdge - radius, ballPosY });
			ball->setVelocity(Vec2{ ballVelX * -1, ballVelY });
		}
		
	}
}

void PhysicsEngine::Handle_BvB(float deltaTime)
{
	double totalVelocity = 0;
	auto& balls = mGameRef.GetEntityManager().GetBallVector();

	for (size_t i{ 0 }; i < balls.size(); i++)
	{
		if (balls[i]->isVisible() == false) { continue;	}				// If Ball 1 is not visible, skip this iteration
		else { totalVelocity += balls[i]->getVelocity().magnitude();}	// To debug for energy conservation print this value at end

		for (size_t j{ i +1  }; j < balls.size(); j++)
		{
			if (balls[j]->isVisible() == false) { continue;}			// If Ball 2 is not visible, skip this iteration
			if (i == j) { continue; }									// Most likely redundant safeguard
			if (!doBallsOverlap(*balls[i], *balls[j])) { continue; }	// If balls don't overlap, no need to do anything

			BvB_ResolvePosition(*balls[i], *balls[j]);					// Resolve the positional overlap
			BvB_ResolveVelocity(*balls[i], *balls[j]);					// Calculate the new velocities
		}
	}
	// Uncomment to print the total velocity in the system
	std::cout << "Total Velocity: " << totalVelocity << '\n';
}

void PhysicsEngine::BvB_ResolvePosition(Ball& b1, Ball& b2)
{
	double b1Radius = b1.getRadius();
	double b2Radius = b2.getRadius();

	Vec2 b1Pos = b1.getPosition();
	Vec2 b2Pos = b2.getPosition();

	double b1mass = b1.getMass();
	double b2mass = b2.getMass();

	// What is the distance between the center of the two balls
	double distance = b1Pos.distance(b2Pos);

	// What is the distance they actually overlap, halved so it's the amount of overlap for each ball
	double overlap = 0.5 * (distance - b1Radius - b2Radius);

	// Resolve the position of Ball 1
	double xpos_offset = overlap * (b1Pos.getx() - b2Pos.getx()) / distance;
	double ypos_offset = overlap * (b1Pos.gety() - b2Pos.gety()) / distance;
	b1.setPosition({ b1Pos.getx() - xpos_offset , b1Pos.gety() - ypos_offset });

	// Resolve the position of Ball2
	b2.setPosition({ b2Pos.getx() + xpos_offset, b2Pos.gety() + ypos_offset });
}


void PhysicsEngine::BvB_ResolveVelocity(Ball& b1, Ball& b2)
{
	double b1Radius = b1.getRadius();
	double b2Radius = b2.getRadius();

	Vec2 b1Pos = b1.getPosition();
	Vec2 b2Pos = b2.getPosition();

	Vec2 b1Vel = b1.getVelocity();
	Vec2 b2Vel = b2.getVelocity();

	double b1mass = b1.getMass();
	double b2mass = b2.getMass();

	// # Handle the changes in velocity
	Vec2 normal = b1Pos.normalVectorTo(b2Pos);		// Normal vector vel1 | vel2
	Vec2 tangent = normal.getTangent();				// Tangent of normal Vector:

	double dotProdTan1 = b1Vel.dotProduct(tangent);	// Dot product vel1 | tangent
	double dotProdTan2 = b2Vel.dotProduct(tangent);	// Dot product vel2 | tangent

	double dotProdNorm1 = b1Vel.dotProduct(normal);	// Dot product vel1 | normal
	double dotProdNorm2 = b2Vel.dotProduct(normal);	// Dot Product vel2 | normal

	// Conservation of momentum - This might be irrelevant now because poolballs all have the same mass
	double m1 = (dotProdNorm1 * (b1mass - b2mass) + (2.0 * b2mass * dotProdNorm2)) / (b1mass + b2mass);
	double m2 = (dotProdNorm2 * (b2mass - b1mass) + (2.0 * b1mass * dotProdNorm1)) / (b1mass + b2mass);

	// New Velocities
	Vec2 b1NewVel{
		{(tangent.getx() * dotProdTan1) + (normal.getx() * m1)},	// New X velocity of ball 1
		{(tangent.gety() * dotProdTan1) + (normal.gety() * m1)}		// New Y Velocity of ball 1
	};
	Vec2 b2NewVel{
		{(tangent.getx() * dotProdTan2) + (normal.getx() * m2) },	// New X velocity of ball 2
		{(tangent.gety() * dotProdTan2) + (normal.gety() * m2) }	// New Y Velocity of ball 2
	};

	b1.setVelocity(b1NewVel);
	b2.setVelocity(b2NewVel);
}


void PhysicsEngine::BallVsPolygon(Ball& b, const sf::VertexArray& polygon)
{

	// Debug stuff
	auto& window = mGameRef.GetWindow();

	for (size_t i{ 0 }; i < polygon.getVertexCount(); i++)
	{
		Vec2 ballPos = b.getPosition();	// Ball Position
		Vec2 ballVel = b.getVelocity();

		Vec2 point1 = { polygon[i].position.x, polygon[i].position.y };
		Vec2 point2 = { 
			polygon[((i + 1) % polygon.getVertexCount())].position.x,
			polygon[((i + 1) % polygon.getVertexCount())].position.y 
		};

		// Vector from point1 to point2 (The line)
		Vec2 edge = point2 - point1;

		// Vector from point1 to the ball
		Vec2 centerToP1 = ballPos - point1;

		// Projection of ball onto edge
		float edgeLength = edge.magnitude();
		float projection = ((centerToP1.dotProduct(edge) / (edgeLength * edgeLength)));
		projection = std::clamp(projection, 0.f, 1.f);

		// Closest point on the edge to the ball's center
		Vec2 closestPoint = (point1 + (edge * projection));

		// Vector from ball to closest point
		Vec2 centerToClosest = ballPos - closestPoint;

		//DEBUG DRAW
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(closestPoint.getx(), closestPoint.gety());
		lines[0].color = sf::Color::Cyan;
		lines[1].position = sf::Vector2f(centerToClosest.getx() + closestPoint.getx(), centerToClosest.gety() + closestPoint.gety());
		lines[1].color = sf::Color::Cyan;
		window.draw(lines);

		// Distance to ball edge
		double distance = centerToClosest.magnitude();

		if (distance <= b.getRadius())
		{
			Vec2 normal = centerToClosest.withMagnitude(1);

			// Push the ball back
			Vec2 newPos = ballPos + (normal * (distance - b.getRadius()));
			b.setPosition(newPos);

			// Update velocity
			Vec2 velocity = ballVel - (normal * 2.0 * (ballVel.dotProduct(normal)));
			b.setVelocity(velocity);
		}
		
	}
}

// Dot product
float PhysicsEngine::dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}
// magnitude
float PhysicsEngine::length(const sf::Vector2f& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}
// normal vector
sf::Vector2f PhysicsEngine::normalize(const sf::Vector2f& v) {
	float len = length(v);
	return (len != 0) ? sf::Vector2f(v.x / len, v.y / len) : sf::Vector2f(0.f, 0.f);
}

void PhysicsEngine::BallVsPolygonStolen(Ball& b, const sf::ConvexShape& polygon)
{
	sf::Vector2f velocity = { (float)b.getVelocity().getx(), (float)b.getVelocity().gety() };
	sf::Vector2f ballCenter = { (float)b.getPosition().getx(), (float)b.getPosition().gety() };
    // Iterate through polygon
    for (size_t i = 0; i < polygon.getPointCount(); ++i) {
        // Get current and next vertex
        sf::Vector2f point1 = polygon.getPoint(i);
        sf::Vector2f point2 = polygon.getPoint((i + 1) % polygon.getPointCount());

        // Vector from point1 to point2 (polygon edge)
        sf::Vector2f edge = point2 - point1;


        // Vector from point1 to the ball's center
        sf::Vector2f centerToP1 = ballCenter - point1;
        // Projection of ball onto edge
        float edgeLength = length(edge);
        float projection = dotProduct(centerToP1, edge) / (edgeLength * edgeLength);
        projection = std::clamp(projection, 0.f, 1.f);  

        // Closest point on the edge to the ball's center
        sf::Vector2f closestPoint = point1 + projection * edge;

        // Vector from ball to closest point
        sf::Vector2f centerToClosest = ballCenter - closestPoint;
        
        // Distance ball to edge
        float distance = length(centerToClosest);

        if (distance <= b.getRadius() + 0.001) {
            // Collision detected, calculate reflection

            // Vector collision
            sf::Vector2f normal = normalize(centerToClosest);

			//sf::Vector2f newPos = ballCenter + (normal * (distance - (float)b.getRadius()));
			//b.setPosition({ newPos.x, newPos.y });

            // Reflect velocity
            velocity = velocity - 2.f * dotProduct(velocity, normal) * normal;
			b.setVelocity({ velocity.x, velocity.y });
        }
    }

}

bool PhysicsEngine::AreBallsAtRest()
{
	bool atRest = true;
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		if (ball->getVelocity().getx() != 0)
		{
			atRest = false;
		}
		if (ball->getVelocity().gety() != 0)
		{
			atRest = false;
		}
	}
	return atRest;
}


