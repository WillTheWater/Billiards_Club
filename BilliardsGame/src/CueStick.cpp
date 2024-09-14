#include "CueStick.h"

CueStick::CueStick()
    :mVisible{false}
    ,mAnimation{false}
    ,mPowerBar{sf::Vector2f(1,5)}
{
}

void CueStick::toggleVisiblity(bool visible)
{
    mVisible = visible; 
}

bool CueStick::isVisible()
{
    return mVisible;
}


sf::Sprite& CueStick::getSprite()
{
    return mSprite;
}

bool CueStick::isAnimationActive()
{
    return mAnimation;
}

Vec2 CueStick::getStrikeVelocity()
{
    return -mAnimUnit;
}

void CueStick::setPosition(const Vec2& pos)
{
    mSprite.setPosition(pos.getx(), pos.gety());
    mPowerBar.setPosition(pos.getx(), pos.gety());
}

void CueStick::setRotationDegrees(const float angle)
{
    mSprite.setRotation(angle);
    mPowerBar.setRotation(angle);
}

void CueStick::setAnimVectors(const Vec2& start, const Vec2& finish, int steps)
{
    mAnimation = true;
    mAnimStart = start;
    mAnimFinish = finish;
    mAnimSteps = steps;
    mAnimDistance = start.distance(finish);
    Vec2 animUnit = mAnimStart - mAnimFinish;
    animUnit = animUnit / animUnit.magnitude();
    animUnit = animUnit * (mAnimDistance / steps);
    mAnimUnit = animUnit; 
}

void CueStick::initializeAnim()
{
    setPosition(mAnimStart);
}

bool CueStick::stepAnimation()
{
    if (mAnimSteps > 0)
    {
        setPosition(getPosition() - mAnimUnit);
        mAnimSteps--;
        return true;
    }
    mAnimation = false;
    return false;
    
}

bool CueStick::animationStepsLeft()
{
    return mAnimSteps > 0;
}

sf::RectangleShape& CueStick::getPowerBar()
{
    return mPowerBar;
}

void CueStick::setPowerBarColor(sf::Color color)
{
    mPowerBarColor = color;
}

Vec2 CueStick::getPosition()
{
    return { mSprite.getPosition().x, mSprite.getPosition().y };
}
