#include "Table.h"

Table::Table(float width, float height)
	:mRect{ sf::Vector2f(width, height) }
{
	
}

float Table::getGlobalHeight()
{
	return mRect.getGlobalBounds().height;
}

float Table::getGlobalWidth()
{
	return mRect.getGlobalBounds().width;
}

float Table::getTopBound() const
{
	return mRect.getGlobalBounds().top;
}

float Table::getBottomBound() const
{
	return mRect.getGlobalBounds().height;
}

float Table::getLeftBound() const
{
	return mRect.getGlobalBounds().left;
}

float Table::getRightBound() const
{
	return mRect.getGlobalBounds().width;
}



float Table::getPositionX()
{
	return mRect.getPosition().x;
}

float Table::getPositionY()
{
	return mRect.getPosition().y;
}

void Table::setPosition(float x, float y)
{
	mRect.setPosition(x, y);
}

sf::RectangleShape& Table::getRect()
{
	return mRect;
}
