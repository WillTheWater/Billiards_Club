#include "Vec2.h"

// ### CONSTRUCTORS ###

Vec2::Vec2(double x, double y)
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
	double x = (this->m_x + other.m_x); 
	double y = (this->m_y + other.m_y);
	return Vec2(x, y);
}

Vec2 Vec2::operator - (Vec2 other)
{
	double x = (this->m_x - other.m_x);
	double y = (this->m_y - other.m_y);
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

Vec2 Vec2::operator / (double num)
{
	double x = (this->m_x / num);
	double y =  (this->m_y / num);
	return Vec2(x, y);
}

Vec2 Vec2::operator * (double num)
{
	double x = (this->m_x * num);
	double y = (this->m_y * num);
	return Vec2(x, y);
}

Vec2 Vec2::operator + (double num)
{
	double magnitude = this->magnitude();
	double angle = this->angleInDegrees();
	magnitude += num;
	double x = (this->m_x = magnitude * std::cos(angle));
	double y = (this->m_y = magnitude * std::sin(angle));
	return Vec2(x, y);
}

Vec2 Vec2::operator - (double num)
{
	double magnitude = this->magnitude();
	double angle = this->angleInDegrees();
	magnitude -= num;
	double x = (this->m_x = magnitude * std::cos(angle));
	double y = (this->m_y = magnitude * std::sin(angle));
	return Vec2(x, y);
}

std::ostream& operator << (std::ostream& out, Vec2& vec)
{
	out << "Vec2: (" << vec.m_x << ", " << vec.m_y << ") ";
	return out;
}

// ### GETTERS ###

const double Vec2::getx() const { return this->m_x; }

const double Vec2::gety() const { return this->m_y; }

// ### SETTERS ###

void Vec2::setx(double x) { this->m_x = x; }

void Vec2::sety(double y) { this->m_y = y; }

void Vec2::setMagnitude(const double magnitude)
{
	double angle = this->angleInDegrees();
	this->m_x = magnitude * std::cos(angle);
	this->m_y = magnitude * std::sin(angle);
}

// ### FUNCTIONS ###

Vec2 Vec2::withMagnitude(const double magnitude)
{
	double angle = this->angleInDegrees();
	double x = magnitude * std::cos(angle);
	double y = magnitude * std::sin(angle);
	return Vec2(x, y);
}

const double Vec2::distance(Vec2 other) const
{
	return std::sqrt(
		(std::pow((other.m_x - this->m_x), 2)) + 
		(std::pow((other.m_y - this->m_y), 2)) 
	);
}

Vec2 Vec2::normalVectorTo(Vec2 other) const
{
	double distance = this->distance(other);
	double normalx = (other.m_x - this->m_x) / (distance);
	double normaly = (other.m_y - this->m_y) / (distance);
	return Vec2(normalx, normaly);
}

Vec2 Vec2::getTangent() const
{
	double tangentx = this->m_y * -1;
	double tangenty = this->m_x;
	return Vec2(tangentx, tangenty);
}

const double Vec2::magnitude() const
{
	return std::sqrt((std::pow(this->m_x, 2)) + ((std::pow(this->m_y, 2))));
}

const double Vec2::dotProduct(Vec2 other) const
{
	return ((this->m_x * other.m_x) + (this->m_y + other.m_y));
}

double Vec2::angleInDegrees()
{
	return std::atan2(this->m_y, this->m_x) * (180 / PI);
}

double Vec2::angleInRads()
{
	return std::atan2(this->m_y, this->m_x);
}