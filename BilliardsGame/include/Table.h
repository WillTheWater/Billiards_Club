#pragma once
#include "SFML/Graphics.hpp"

class Table
{
public:
	Table(float width, float height);

	float getGlobalHeight();

	float getGlobalWidth(); 

	float getTopBound() const;
	float getBottomBound() const;
	float getLeftBound() const;
	float getRightBound() const;

	float getPositionX();
	float getPositionY();

	void setPosition(float x, float y);
	void setOrigin(float x, float y);

	sf::RectangleShape& getRect();

private:
	sf::RectangleShape mRect;
};