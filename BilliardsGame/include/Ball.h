#pragma once

#include "Vec2.h"
#include "EntityGlobals.h"
#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>

class Ball
{
public:
	Ball() = delete;
	Ball(BallId id, double radius, Vec2 pos, Vec2 vel, Vec2 accel);
	
	const Vec2 getPosition() const;
	const Vec2 getVelocity() const;
	const Vec2 getAcceleration() const;
	const double getMass() const; 
	const bool isVisible() const;
	const double getRadius() const;
	sf::CircleShape& getCircle();

	void setPosition(const Vec2& position);
	void setVelocity(const Vec2& velocity);
	void setAcceleration(const Vec2& acceleration);
	void setMass(const double mass);
	void setVisiblity(bool visibility);
	void setRadius(const double radius) ;
	void setVelMagnitude(const double magnitude);

	void updatePosition(double deltaTime);
	void clampVelocity();
	bool isBallAtRest(Ball* ball);

	void debugRender();
	

private:
	Vec2 m_position;
	Vec2 m_velocity;
	Vec2 m_acceleration;
	double m_mass;
	double m_radius;
	bool m_visible;
	sf::CircleShape m_circle;
	BallId m_id;
};