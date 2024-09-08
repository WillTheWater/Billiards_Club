#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class Button
{
public:
	Button();
	bool						HandleEvent(const sf::Event& event);
	void						Draw(sf::RenderWindow& window);
	void						SetTexture(const std::string& texturePath);
	void						SetTextureRect(int left, int top, int width, int height);
	void						SetPosition(const sf::Vector2f& position);
	void						SetScale(const float& scale);
	sf::FloatRect				GetBounds() const;
	bool						WasClicked();
	
private:
	sf::Texture					mButtonTexture;
	sf::Sprite					mButtonSprite;
	sf::Color					mDefaultColor = sf::Color{ 255, 255, 255, 255 };
	sf::Color					mDownColor = sf::Color{ 100, 100, 100, 255 };
	sf::Color					mHoverColor = sf::Color{ 200, 200, 200, 255 };
	bool						IsButtonDown;
	void						OnButtonUp();
	void						OnButtonDown();
	void						OnButtonHover();
	TextureManager				mTextureManager;
};