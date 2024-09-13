#include "Ball.h"

Ball::Ball(BallId id, float radius, Vec2 pos = (0, 0), Vec2 vel = (0, 0), Vec2 accel = (0, 0))
	:m_id{id}
	,m_position{pos}
	,m_positionPrevious{ pos }
	,m_velocity{vel}
	,m_acceleration{accel}
	,m_mass{(float)std::fabs(radius * radius * 3.14)}
	,m_visible{true}
	,m_radius{radius}
	,m_circle{radius}
	,m_SimTimeRemaining{0}
	,m_outline{false}
{
	m_circle.setOrigin(radius, radius);
	m_circle.setPosition(pos.getx(), pos.gety());
}

const Vec2 Ball::getPosition() const {
	return m_position;
}
const Vec2 Ball::getPositionPrevious() const
{
	return m_positionPrevious;
}
const Vec2 Ball::getVelocity() const {
	return m_velocity;
}
const Vec2 Ball::getAcceleration() const {
	return m_acceleration;
}
const float Ball::getMass() const {
	return m_mass;
}

const float Ball::getRadius() const{
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

float Ball::getSimTimeRemaining() const
{
	return m_SimTimeRemaining;
}

sf::Sprite& Ball::getTagSprite()
{
	return m_tag;
}

const bool Ball::isVisible() const {
	return m_visible;
}

void Ball::setPosition(const Vec2& position) {
	m_position = position;
	m_circle.setPosition(position.getx(), position.gety());
}
void Ball::setPositionPrevious(const Vec2& position)
{
	m_positionPrevious = position;
}
void Ball::setVelocity(const Vec2& velocity) {
	m_velocity = velocity;
}
void Ball::setAcceleration(const Vec2& acceleration) {
	m_acceleration = acceleration;
}
void Ball::setMass(const float mass) {
	m_mass = mass;
}

void Ball::setVelMagnitude(const float magnitude)
{
	m_velocity.setMagnitude(magnitude);
}

void Ball::setSimTimeRemaining(float time)
{
	m_SimTimeRemaining = time;
}

void Ball::toggleOutline(bool toggle)
{
	m_outline = toggle;
	if (m_outline)
	{
		m_circle.setOutlineThickness(5);
	}
	else
	{
		m_circle.setOutlineThickness(0);
	}
}

void Ball::setRadius(const float radius) {
	m_circle.setRadius(m_radius);
}

void Ball::setVisiblity(bool visibility) {
	m_visible = visibility;
}

void Ball::updatePosition() {
	m_positionPrevious = m_position;
	m_position += m_velocity * m_SimTimeRemaining;
	m_velocity += m_acceleration * m_SimTimeRemaining;
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
