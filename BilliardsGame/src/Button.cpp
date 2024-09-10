#include "Button.h"
#include <iostream>

Button::Button(TextureManager& textureManager)
	:mTextureManager{textureManager}
{
	mButtonSprite.setColor(mDefaultColor);
	IsButtonDown = false;
}

sf::FloatRect Button::GetBounds() const
{
	return mButtonSprite.getGlobalBounds();
}

sf::Text& Button::GetButtonText()
{
	return mButtonText;
}

bool Button::HandleEvent(const sf::Event& event)
{
	bool handled = false;
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				std::cout << "Button Clicked\n";
				IsButtonDown = true;
				OnButtonDown();
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (IsButtonDown && mButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				std::cout << "Button Released\n";
				OnButtonDown();
				WasClicked();
				handled = true;
			}
			OnButtonUp();
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (mButtonSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
			{
				OnButtonHover();
			}
			else
			{
				OnButtonUp();
			}
		}
	}
	return handled;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(mButtonSprite);
}

void Button::SetTexture(const std::string& texturePath)
{
	auto mButtonTexture = mTextureManager.GetTexture(texturePath);
	mButtonSprite.setTexture(*mButtonTexture);
}

void Button::SetTextureRect(int left, int top, int width, int height)
{
	mButtonSprite.setTextureRect(sf::IntRect{ left, top, width, height });
}

void Button::SetText(const std::string& buttonText)
{
	mButtonText.setString(buttonText);
	
}

void Button::SetFont(const std::string& fontPath)
{
	auto mButtonFont = mTextureManager.GetFont(fontPath);
	mButtonText.setFont(*mButtonFont);
}

void Button::SetFontSize(const unsigned int& fontSize)
{
	mButtonText.setCharacterSize(fontSize);
}

void Button::ScaleFont(const float& width, const float& height)
{
	mButtonText.setScale({ width, height });
}

void Button::CenterText()
{
	sf::FloatRect buttonBounds = mButtonSprite.getGlobalBounds();
	sf::FloatRect textBounds = mButtonText.getLocalBounds();
	mButtonSprite.setOrigin(buttonBounds.width / 2.f, buttonBounds.height / 2.f);
	mButtonText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
	mButtonText.setPosition(mButtonSprite.getPosition());
}

void Button::SetPosition(const sf::Vector2f& position)
{
	mButtonSprite.setPosition(position);
}

void Button::SetScale(const float& scale)
{
	mButtonSprite.setScale(scale, scale);
}

void Button::SetFontColor(sf::Color& color)
{
	mButtonText.setFillColor(color);
}

void Button::SetupButton(const std::string& fontPath, const std::string& buttonText, const unsigned int& fontSize, sf::Color color, const sf::Vector2f& position)
{
	SetFont(fontPath);
	SetText(buttonText);
	SetFontSize(fontSize);
	SetFontColor(color);
	SetPosition(position);
	CenterText();
}

bool Button::WasClicked()
{
	return true;
}

void Button::OnButtonUp()
{
	IsButtonDown = false;
	mButtonSprite.setColor(mDefaultColor);
}

void Button::OnButtonDown()
{
	IsButtonDown = true;
	mButtonSprite.setColor(mDownColor);
}

void Button::OnButtonHover()
{
	mButtonSprite.setColor(mHoverColor);
}