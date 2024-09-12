#include "Vec2.h"

// ### CONSTRUCTORS ###

Vec2::Vec2(float x, float y)
	: m_x{x}
	, m_y{y}
{
}

Vec2::~Vec2()
{
}

// ### OPERATORS ###

Vec2 Vec2::operator + (Vec2 other)
{
	float x = (this->m_x + other.m_x); 
	float y = (this->m_y + other.m_y);
	return Vec2(x, y);
}

Vec2 Vec2::operator - (Vec2 other)
{
	float x = (this->m_x - other.m_x);
	float y = (this->m_y - other.m_y);
	return Vec2(x, y);
}

Vec2& Vec2::operator = (Vec2 other)
{
	this->m_x = other.m_x;
	this->m_y = other.m_y;
	return *this;
}

Vec2& Vec2::operator += (Vec2 other)
{
	return *this = *this + other;
}

Vec2& Vec2::operator -= (Vec2 other)
{
	return *this = *this - other;
}

Vec2 Vec2::operator / (float num)
{
	float x = (this->m_x / num);
	float y =  (this->m_y / num);
	return Vec2(x, y);
}

Vec2 Vec2::operator * (float num)
{
	float x = (this->m_x * num);
	float y = (this->m_y * num);
	return Vec2(x, y);
}

Vec2 Vec2::operator + (float num)
{
	float magnitude = this->magnitude();
	float angle = this->angleInDegrees();
	magnitude += num;
	float x = (this->m_x = magnitude * std::cos(angle));
	float y = (this->m_y = magnitude * std::sin(angle));
	return Vec2(x, y);
}

Vec2 Vec2::operator - (float num)
{
	float magnitude = this->magnitude();
	float angle = this->angleInDegrees();
	magnitude -= num;
	float x = (this->m_x = magnitude * std::cos(angle));
	float y = (this->m_y = magnitude * std::sin(angle));
	return Vec2(x, y);
}

std::ostream& operator << (std::ostream& out, Vec2& vec)
{
	out << "Vec2: (" << vec.m_x << ", " << vec.m_y << ") ";
	return out;
}

// ### GETTERS ###

const float Vec2::getx() const { return this->m_x; }

const float Vec2::gety() const { return this->m_y; }

// ### SETTERS ###

void Vec2::setx(float x) { this->m_x = x; }

void Vec2::sety(float y) { this->m_y = y; }

void Vec2::setMagnitude(const float magnitude)
{
	float angle = this->angleInDegrees();
	this->m_x = magnitude * std::cos(angle);
	this->m_y = magnitude * std::sin(angle);
}

// ### FUNCTIONS ###

Vec2 Vec2::withMagnitude(const float magnitude)
{
	float angle = this->angleInDegrees();
	float x = magnitude * std::cos(angle);
	float y = magnitude * std::sin(angle);
	return Vec2(x, y);
}

const float Vec2::distance(Vec2 other) const
{
	return std::sqrt(
		(std::pow((other.m_x - this->m_x), 2)) + 
		(std::pow((other.m_y - this->m_y), 2)) 
	);
}

Vec2 Vec2::getNormalized() const
{
	float length = this->magnitude();
	if (length == 0)
	{
		return (0, 0);
	}
	else
	{
		return ((this->m_x / length), (this->m_y / length));
	}
}

Vec2 Vec2::normalVectorTo(Vec2 other) const
{
	float distance = this->distance(other);
	float normalx = (other.m_x - this->m_x) / (distance);
	float normaly = (other.m_y - this->m_y) / (distance);
	return Vec2(normalx, normaly);
}

Vec2 Vec2::getTangent() const
{
	float tangentx = this->m_y * -1;
	float tangenty = this->m_x;
	return Vec2(tangentx, tangenty);
}

const float Vec2::magnitude() const
{
	return std::sqrt((this->m_x * this->m_x) + (this->m_y * this->m_y));
}

const float Vec2::dotProduct(Vec2 other) const
{
	return ((this->m_x * other.m_x) + (this->m_y * other.m_y));
}

float Vec2::angleInDegrees()
{
	return std::atan2(this->m_y, this->m_x) * (180 / PI);
}

float Vec2::angleInRads()
{
	return std::atan2(this->m_y, this->m_x);
}