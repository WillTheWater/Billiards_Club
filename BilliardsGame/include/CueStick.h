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

	bool isAnimationActive();

	Vec2 getStrikeVelocity();	// Get the vector to apply to the cueball

	void setPosition(const Vec2& pos);

	void setRotationDegrees(const float angle);

	void setAnimVectors(const Vec2& start, const Vec2& finish, int steps);	// Provide the stored animation start/finish positions, and the number of steps

	void initializeAnim();	// Sets the cue position the animation start position

	bool stepAnimation();	// Returns false if there are no more animation steps

	bool animationStepsLeft();

	sf::RectangleShape& getPowerBar();

	void setPowerBarColor(sf::Color color);



	Vec2 getPosition();

private:
	sf::Sprite mSprite;
	bool mVisible;
	bool mAnimation;		//Is true if here is animation to play
	int mAnimSteps;			//How many steps the cue should make from the start to finish
	Vec2 mAnimStart;		//The start position of the cue for the animation
	Vec2 mAnimFinish;		//The position the cue should be at when the animation finishes
	Vec2 mAnimUnit;			//The amount the cue should move each frame1
	float mAnimDistance;	//The total distance the cue will travel during the animation
	sf::RectangleShape mPowerBar;
	sf::Color mPowerBarColor;
};

