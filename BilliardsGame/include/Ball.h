#pragma once

#include "Vec2.h"
#include "EntityGlobals.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball() = delete;
	Ball(BallId id, float radius, Vec2 pos, Vec2 vel, Vec2 accel);
	
	const Vec2 getPosition() const;
	const Vec2 getPositionPrevious() const;
	const Vec2 getVelocity() const;
	const Vec2 getAcceleration() const;
	const float getMass() const; 
	const bool isVisible() const;
	const float getRadius() const;
	sf::CircleShape& getCircle();
	const BallId getId() const;
	float getSimTimeRemaining() const;
	sf::Sprite& getTagSprite(); 

	void setPosition(const Vec2& position);
	void setPositionPrevious(const Vec2& position);
	void setVelocity(const Vec2& velocity);
	void setAcceleration(const Vec2& acceleration);
	void setMass(const float mass);
	void setVisiblity(bool visibility);
	void setRadius(const float radius) ;
	void setVelMagnitude(const float magnitude);
	void setSimTimeRemaining(float time);

	void updatePosition();
	void clampVelocity();
	bool isBallAtRest(Ball* ball);

	void debugRender();
	

private:
	Vec2 m_position;
	Vec2 m_positionPrevious;
	Vec2 m_velocity;
	Vec2 m_acceleration;
	float m_mass;
	float m_radius;
	bool m_visible;
	sf::CircleShape m_circle;
	sf::Sprite		m_tag;
	BallId m_id;
	float m_SimTimeRemaining;
};