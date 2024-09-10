#include <iostream>
#include "Game.h"

TextureManager::TextureManager(Game& game)
    :mGameRef{ game }
{
}

std::shared_ptr<sf::Texture> TextureManager::GetTexture(const std::string& texture)
{
    auto it = mTextureMap.find(texture);
    if (it != mTextureMap.end()) { return it->second; } // If texture is already loaded, return it.
    else { return LoadTexture(texture); } // If texture isn't loaded, load and return it.
}

std::shared_ptr<sf::Font> TextureManager::GetFont(const std::string& font)
{
    auto it = mFontMap.find(font);
    if (it != mFontMap.end()) { return it->second; } // If font is already loaded, return it.
    else { return LoadFont(font); } // If font isn't loaded, load and return it.
}

std::shared_ptr<sf::Texture> TextureManager::LoadTexture(const std::string& texturePath)
{
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture.\n"; return nullptr;
    }
    mTextureMap[texturePath] = texture;
    return texture;
}

std::shared_ptr<sf::Font> TextureManager::LoadFont(const std::string& fontPath)
{
    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(fontPath))
    {
        std::cerr << "Failed to load font.\n"; return nullptr;
    }
    mFontMap[fontPath] = font;
    return font;
}
