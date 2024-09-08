#include "TextureManager.h"
#include <iostream>

std::shared_ptr<sf::Texture> TextureManager::GetTexture(const std::string& texture)
{
    auto it = mTextureMap.find(texture);
    if (it != mTextureMap.end()) { return it->second; } // If texture is already loaded, return it.
    else { return LoadTexture(texture); } // If texture isn't loaded, load and return it.
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