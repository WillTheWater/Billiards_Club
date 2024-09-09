#pragma once
#include <cmath>
#include <iostream>

class Vec2
{
public:
	// ### PUBLIC PARAMETERS ###
	const double PI = 3.14159265;

	// ### CONSTRUCTORS ###
	Vec2(double x = 0, double y = 0);

	~Vec2();

	// ### OPERATORS ###
	Vec2 operator + (Vec2 other);

	Vec2 operator - (Vec2 other);

	Vec2& operator = (Vec2 other);

	Vec2& operator += (Vec2 other);

	Vec2& operator -= (Vec2 other);

	Vec2 operator / (double num);

	Vec2 operator * (double num);

	Vec2 operator + (double num);

	Vec2 operator - (double num);

	friend std::ostream& operator << (std::ostream& out, Vec2& vec);

	// ### GETTERS ###

	const double getx() const;

	const double gety() const;

	// ### SETTERS ###

	void setx(double x);

	void sety(double y);

	void setMagnitude(const double magnitude);

	// ### FUNCTIONS ###

	Vec2 withMagnitude(const double magnitude);

	double distance(Vec2 other);

	const double magnitude() const;

	double dotProduct (Vec2 other);

	double angleInDegrees();

	double angleInRads();

private:
	double m_x;
	double m_y;
};