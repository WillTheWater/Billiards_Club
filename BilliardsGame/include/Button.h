#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

class Button
{
public:
	Button() = delete;
	Button(TextureManager& textureManager);
	bool						HandleEvent(const sf::Event& event);
	void						Draw(sf::RenderWindow& window);
	void						SetTexture(const std::string& texturePath);
	void						SetTextureRect(int left, int top, int width, int height);
	void						SetText(const std::string& buttonText);
	void						SetFont(const std::string& fontPath);
	void						SetFontSize(const unsigned int& fontSize);
	void						ScaleFont(const float& width, const float& height);
	void						CenterText();
	void						SetPosition(const sf::Vector2f& position);
	void						SetScale(const float& scale);
	void						SetFontColor(sf::Color& color);
	void						SetupButton(const std::string& fontPath, const std::string& buttonText, const unsigned int& fontSize, sf::Color color, const sf::Vector2f& position);
	sf::FloatRect				GetBounds() const;
	sf::Text&					GetButtonText();
	bool						WasClicked();
	
private:
	sf::Texture					mButtonTexture;
	sf::Sprite					mButtonSprite;
	sf::Font					mButtonFont;
	sf::Text					mButtonText;
	sf::Color					mDefaultColor = sf::Color{ 255, 255, 255, 255 };
	sf::Color					mDownColor = sf::Color{ 100, 100, 100, 255 };
	sf::Color					mHoverColor = sf::Color{ 200, 200, 200, 255 };
	bool						IsButtonDown;
	void						OnButtonUp();
	void						OnButtonDown();
	void						OnButtonHover();
	TextureManager&				mTextureManager;
};