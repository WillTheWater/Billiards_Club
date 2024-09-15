#pragma once
#include "Vec2.h"
#include "EntityGlobals.h"
#include <cmath>
#include <SFML/Graphics.hpp>

class CueStick
{
public:
	CueStick();

	void toggleVisiblity(bool visible);

	bool isVisible();
	
	sf::Sprite& getSprite();

	void setPosition(const Vec2& pos);

	void setRotationDegrees(const float angle);

	Vec2 getPositon();

private:
	sf::Sprite mSprite;
	bool mVisible;
};

