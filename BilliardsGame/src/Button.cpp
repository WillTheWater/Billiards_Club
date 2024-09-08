#include "Button.h"
#include <iostream>

Button::Button()
{
	mButtonSprite.setColor(mDefaultColor);
	IsButtonDown = false;
}

sf::FloatRect Button::GetBounds() const
{
	return mButtonSprite.getGlobalBounds();
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

void Button::SetPosition(const sf::Vector2f& position)
{
	mButtonSprite.setPosition(position);
}

void Button::SetScale(const float& scale)
{
	mButtonSprite.setScale(scale, scale);
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