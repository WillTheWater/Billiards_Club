#pragma once
#include <cmath>
#include <iostream>

class Vec2
{
public:
	// ### PUBLIC PARAMETERS ###
	const float PI = 3.14159265f;

	// ### CONSTRUCTORS ###
	Vec2(float x = 0, float y = 0);

	~Vec2();

	// ### OPERATORS ###
	Vec2 operator -();	// Unary negative operator

	Vec2 operator + (Vec2 other);

	Vec2 operator - (Vec2 other);

	Vec2& operator = (Vec2 other);

	Vec2& operator += (Vec2 other);

	Vec2& operator -= (Vec2 other);

	Vec2 operator / (float num);

	Vec2 operator * (float num);

	Vec2 operator + (float num);

	Vec2 operator - (float num);

	friend std::ostream& operator << (std::ostream& out, Vec2& vec);

	// ### GETTERS ###

	const float getx() const;

	const float gety() const;

	// ### SETTERS ###

	void setx(float x);

	void sety(float y);

	void setMagnitude(const float magnitude);

	// ### FUNCTIONS ###

	Vec2 withMagnitude(const float magnitude);

	const float distance(Vec2 other) const;

	Vec2 getNormalized() const;

	// Calculates the normal between two vectors
	Vec2 normalVectorTo(Vec2 other) const;

	// Call this on a normal vector to get a tangent vector
	Vec2 getTangent() const;

	const float magnitude() const;

	const float dotProduct (Vec2 other) const;

	float angleInDegrees();

	float angleInRads();

private:
	float m_x;
	float m_y;
};