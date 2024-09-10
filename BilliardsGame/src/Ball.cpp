#include "Ball.h"

Ball::Ball(BallId id, double radius, Vec2 pos = (0, 0), Vec2 vel = (0, 0), Vec2 accel = (0, 0))
	:m_id{id}
	,m_position{pos}
	,m_velocity{vel}
	,m_acceleration{accel}
	,m_mass{std::fabs(radius * radius * 3.14)}
	,m_visible{true}
	,m_radius{radius}
	,m_circle{(float)radius}
{
	m_circle.setOrigin(radius, radius);
	m_circle.setPosition(pos.getx(), pos.gety());
}

const Vec2 Ball::getPosition() const {
	return m_position;
}
const Vec2 Ball::getVelocity() const {
	return m_velocity;
}
const Vec2 Ball::getAcceleration() const {
	return m_acceleration;
}
const double Ball::getMass() const {
	return m_mass;
}

const double Ball::getRadius() const{
	return m_circle.getRadius();
}

sf::CircleShape& Ball::getCircle()
{
	return m_circle;
}

const BallId Ball::getId() const
{
	return m_id;
}

const bool Ball::isVisible() const {
	return m_visible;
}

void Ball::setPosition(const Vec2& position) {
	m_position = position;
	m_circle.setPosition(position.getx(), position.gety());
}
void Ball::setVelocity(const Vec2& velocity) {
	m_velocity = velocity;
}
void Ball::setAcceleration(const Vec2& acceleration) {
	m_acceleration = acceleration;
}
void Ball::setMass(const double mass) {
	m_mass = mass;
}

void Ball::setVelMagnitude(const double magnitude)
{
	m_velocity.setMagnitude(magnitude);
}

void Ball::setRadius(const double radius) {
	m_circle.setRadius(m_radius);
}

void Ball::setVisiblity(bool visibility) {
	m_visible = visibility;
}

void Ball::updatePosition(double deltaTime) {
	m_position += m_velocity * deltaTime;
	m_velocity += m_acceleration * deltaTime;
	m_circle.setPosition({ (float)m_position.getx(), (float)m_position.gety() });
}

void Ball::clampVelocity()
{
	if (m_velocity.magnitude() < 1)
	{
		m_velocity = { 0, 0 };
	}
}

bool Ball::isBallAtRest(Ball* ball)
{
	return (ball->getVelocity().getx() == 0 && ball->getVelocity().gety() == 0);
}

void Ball::debugRender()
{

}
