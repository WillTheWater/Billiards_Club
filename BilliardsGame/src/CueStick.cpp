#include "CueStick.h"

CueStick::CueStick()
    :mVisible{false}
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

void CueStick::setPosition(const Vec2& pos)
{
    mSprite.setPosition(pos.getx(), pos.gety());
}

void CueStick::setRotationDegrees(const float angle)
{
    mSprite.setRotation(angle);
}

Vec2 CueStick::getPositon()
{
    return { mSprite.getPosition().x, mSprite.getPosition().y };
}
