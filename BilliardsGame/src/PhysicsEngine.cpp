#include "Game.h"

PhysicsEngine::PhysicsEngine(Game& game)
	: mGameRef{game}
	, mSimUpdates{4}
	, mStepTime{ 0 }
	, mMaxSimSteps{15}
	, mFrictionScale{180}
	, mSoundPlayed{false}
	, soundDelayCounter{0}
{
}

void PhysicsEngine::ApplyStrikeVelocityToCueBall(Vec2 unitVec, float scale)
{
	auto& cueBall = mGameRef.GetEntityManager().getCueBall();
	cueBall.setVelocity(unitVec * scale);
}

void PhysicsEngine::FixCueBallResetOnBall()
{
	auto& balls = mGameRef.GetEntityManager().GetBallVector();
	auto& cueball = mGameRef.GetEntityManager().getCueBall();
	for (auto& ball : balls)
	{
		if (ball->getId() == BallId::BallId_cueBall)
		{
			continue;
		}
		if (doBallsOverlap(*ball, cueball))
		{
			BvB_ResolvePosition(*ball, cueball);
		}
	}
}

void PhysicsEngine::Update(float deltaTime)
{
	calculateStepTime(deltaTime);
	resetPreviousPositionForBalls();
	for (size_t i{ 0 }; i < mSimUpdates; i++)
	{
		initializeSimTimeForBalls();
		for (size_t j{ 0 }; j < mMaxSimSteps; j++)
		{
			MoveBalls();
			ApplyFriction();
			// ApplyFrictionCoEff(); // Needs debugging, not quite working
			HandleCollisions();
			UpdateSimTimeForBalls();
		}
	}
	ClampBallVelocity();
	HandleBallInPocket();
}

void PhysicsEngine::calculateStepTime(float deltaTime)
{
	mStepTime = deltaTime / (float)mSimUpdates;
}

void PhysicsEngine::initializeSimTimeForBalls()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		ball->setSimTimeRemaining(mStepTime);
	}
}

void PhysicsEngine::resetPreviousPositionForBalls()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		ball->setPositionPrevious(ball->getPosition());
	}
}

void PhysicsEngine::UpdateSimTimeForBalls()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		float intendedSpeed = ball->getVelocity().magnitude();
		float intendedDistance = intendedSpeed * ball->getSimTimeRemaining();
		Vec2 ballPosCurent = ball->getPosition();
		Vec2 ballPosPrevious = ball->getPositionPrevious();
		Vec2 previousPosToCurrentPos{ ballPosCurent - ballPosPrevious };
		float actualDistance = previousPosToCurrentPos.magnitude();
		float actualTime = actualDistance / intendedSpeed;
		float simTimeRemaining = ball->getSimTimeRemaining();
		ball->setSimTimeRemaining(simTimeRemaining - actualTime);
	}
}

void PhysicsEngine::MoveBalls()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();

	for (auto& ball : balls)
	{
		if (!ball->isVisible())
		{
			ball->setVelocity({ 0,0 });
			continue;
		}
		if (ball->getSimTimeRemaining() > 0.f)
		{
			ball->updatePosition();
		}
	}
}

bool PhysicsEngine::doBallsOverlap(const Ball& b1, const Ball& b2) const
{
	// Uses Vec2 distance function to get distance between b1 and b2
	float distance = b1.getPosition().distance( 
		b2.getPosition() 
	);

	// If distance is less than b1 + b2 radius, they intercept
	return (distance < b1.getRadius() + b2.getRadius());
}

void PhysicsEngine::HandleBallVsPolygons()
{
	auto& polygon = mGameRef.GetEntityManager().getDebugCollisionLine();
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();

	auto& convexShape = mGameRef.GetEntityManager().getDebugConvexShape();

	for (auto& ball : balls)
	{
		if (ball->getSimTimeRemaining() < 0 || !ball->isVisible())
		{
			continue;
		}

		BallVsPolygon(*ball, convexShape);
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

void PhysicsEngine::HandleCollisions()
{
	Handle_BvTableRect();
	Handle_BvB();
	HandleBallVsPolygons();
}

void PhysicsEngine::Handle_BvTableRect()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	auto& table = mGameRef.GetEntityManager().getTable();

	float topEdge = table.getTopBound();
	float bottomEdge = table.getBottomBound();
	float leftEdge = table.getLeftBound();
	float rightEdge = table.getRightBound();
	
	for (auto& ball : balls)
	{
		if (ball->getSimTimeRemaining() < 0 || !ball->isVisible())
		{
			continue;
		}

		float ballVelX = ball->getVelocity().getx();
		float ballVelY = ball->getVelocity().gety(); 
		float ballPosX = ball->getPosition().getx();
		float ballPosY = ball->getPosition().gety();
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

void PhysicsEngine::Handle_BvB()
{
	float totalVelocity = 0;
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

			// Play sounds 
			float randomNumber = Random::getRandomFloat(90, 110);
			float randomPitch = randomNumber / 100;
			float randomVolume = Random::getRandomFloat(80, 100);
			Audio::PlaySound(mSound, Audio::BALL_WITH_BALL_COLLISION, randomVolume, randomPitch);
		}
	}
	// Uncomment to print the total velocity in the system
	// std::cout << "Total Velocity: " << totalVelocity << '\n';
}

void PhysicsEngine::BvB_ResolvePosition(Ball& b1, Ball& b2)
{
	float b1Radius = b1.getRadius();
	float b2Radius = b2.getRadius();

	Vec2 b1Pos = b1.getPosition();
	Vec2 b2Pos = b2.getPosition();

	float b1mass = b1.getMass();
	float b2mass = b2.getMass();

	// What is the distance between the center of the two balls
	float distance = b1Pos.distance(b2Pos);

	// What is the distance they actually overlap, halved so it's the amount of overlap for each ball
	float overlap = 0.5f * (distance - b1Radius - b2Radius - 1.f);

	// Resolve the position of Ball 1
	float xpos_offset = overlap * (b1Pos.getx() - b2Pos.getx()) / distance;
	float ypos_offset = overlap * (b1Pos.gety() - b2Pos.gety()) / distance;
	b1.setPosition({ b1Pos.getx() - xpos_offset , b1Pos.gety() - ypos_offset });

	// Resolve the position of Ball2
	b2.setPosition({ b2Pos.getx() + xpos_offset, b2Pos.gety() + ypos_offset });
}

void PhysicsEngine::BvB_ResolveVelocity(Ball& b1, Ball& b2)
{
	float b1Radius = b1.getRadius();
	float b2Radius = b2.getRadius();

	Vec2 b1Pos = b1.getPosition();
	Vec2 b2Pos = b2.getPosition();

	Vec2 b1Vel = b1.getVelocity();
	Vec2 b2Vel = b2.getVelocity();

	float b1mass = b1.getMass();
	float b2mass = b2.getMass();

	// # Handle the changes in velocity
	Vec2 normal = b1Pos.normalVectorTo(b2Pos);		// Normal vector vel1 | vel2
	Vec2 tangent = normal.getTangent();				// Tangent of normal Vector:

	float dotProdTan1 = b1Vel.dotProduct(tangent);	// Dot product vel1 | tangent
	float dotProdTan2 = b2Vel.dotProduct(tangent);	// Dot product vel2 | tangent

	float dotProdNorm1 = b1Vel.dotProduct(normal);	// Dot product vel1 | normal
	float dotProdNorm2 = b2Vel.dotProduct(normal);	// Dot Product vel2 | normal

	// Conservation of momentum - This might be irrelevant now because poolballs all have the same mass
	float m1 = (dotProdNorm1 * (b1mass - b2mass) + (2.0f * b2mass * dotProdNorm2)) / (b1mass + b2mass);
	float m2 = (dotProdNorm2 * (b2mass - b1mass) + (2.0f * b1mass * dotProdNorm1)) / (b1mass + b2mass);

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

// Dot product
float PhysicsEngine::dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}
// Magnitude
float PhysicsEngine::length(const sf::Vector2f& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}
// Normal vector
sf::Vector2f PhysicsEngine::normalize(const sf::Vector2f& v) {
	float len = length(v);
	return (len != 0) ? sf::Vector2f(v.x / len, v.y / len) : sf::Vector2f(0.f, 0.f);
}

void PhysicsEngine::BallVsPolygon(Ball& b, const sf::ConvexShape& polygon)
{

	bool collision = false;
	sf::Vector2f velocity = { b.getVelocity().getx(), b.getVelocity().gety() };
	sf::Vector2f ballCenter = { b.getPosition().getx(), b.getPosition().gety() };
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

        if (distance <= b.getRadius()) {
            // Collision detected, calculate reflection
			collision = true;
            // Vector collision
            sf::Vector2f normal = normalize(centerToClosest);

			// Resolve Position
			float overlap = distance - b.getRadius() - 1;
			sf::Vector2f displace
			{
			((overlap * (ballCenter.x - closestPoint.x)) / distance),
			((overlap * (ballCenter.y - closestPoint.y)) / distance)
			};

			sf::Vector2f newPos = ballCenter - displace;
			b.setPosition({ newPos.x, newPos.y });
			// Reflect velocity
			velocity = velocity - 2.f * dotProduct(velocity, normal) * normal;
			b.setVelocity({ velocity.x, velocity.y });

		
        }
    }
	if (collision) // This doesn't work very well sadly. :(
	{
		/*float speed = b.getVelocity().magnitude();
		float clamped = std::clamp(speed, 0.f, 500.f);
		clamped = clamped / 5000;
		float randomNumber = Random::getRandomFloat(90, 110);
		float randomPitch = randomNumber / 100;
		float randomVolume = Random::getRandomFloat(80, 100);
		Audio::PlaySound(mSound, Audio::BALL_WITH_TABLE_COLLISION, randomVolume * clamped, randomPitch * 0.75);*/
	}
}

void PhysicsEngine::HandleBallInPocket()
{
	auto& pockets = mGameRef.GetEntityManager().getPockets();
	auto& balls = mGameRef.GetEntityManager().GetBallVector();

	for (auto& ball : balls)
	{
		if (!ball->isVisible())
		{
			continue;
		}

		for (auto& pocket : pockets)
		{
			Vec2 ballPos = ball->getPosition();
			Vec2 pocketPos = { pocket.getPosition().x, pocket.getPosition().y };
			float distance = pocketPos.distance(ballPos);
			float combinedRadius = PoolTable::pocketradius;
			if (distance < combinedRadius)
			{
				Audio::PlaySound(mSound, Audio::POCKET, 50, 1);
				ball->setVisiblity(false);
			}

		}
	}
}

void PhysicsEngine::ApplyFriction()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();

	float scale = mFrictionScale;

	for (auto& ball : balls)
	{
		if (!ball->isVisible())
		{
			continue;
		}
		float time = ball->getSimTimeRemaining();
		if (time > 0 && ball->getVelocity().magnitude() > 0)
		{
			Vec2 currentVelocity = ball->getVelocity();
			Vec2 velocityToSub = currentVelocity;
			velocityToSub = velocityToSub / velocityToSub.magnitude() * scale * time;
			Vec2 newVelocity = currentVelocity - velocityToSub;
			ball->setVelocity(newVelocity);
		}
	}
}

void PhysicsEngine::ClampBallVelocity()
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		if (ball->getVelocity().magnitude() < 2)
		{
			ball->setVelocity({ 0,0 });
		}
	}
}

void PhysicsEngine::ApplyFrictionCoEff()	// Not working yet
{
	std::vector<std::unique_ptr<Ball>>& balls = mGameRef.GetEntityManager().GetBallVector();
	for (auto& ball : balls)
	{
		if (!ball->isVisible())
		{
			continue;
		}

		float time = ball->getSimTimeRemaining();	// delta time equivelant
		float frictionCoEff = 0.0000005f;

		if (time > 0 && ball->getVelocity().magnitude() > 0)
		{
			float speed = ball->getVelocity().magnitude();
			float force = speed * frictionCoEff * time;
			speed -= force * time;
			if (speed < 0)
			{
				speed = 0;
			}
			Vec2 newVel = ball->getVelocity();
			newVel = newVel / newVel.magnitude();
			newVel* speed;
			if (ball->getVelocity().magnitude() > 5)
			{
				ball->setVelocity(newVel);
			}
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



