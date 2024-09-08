#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	std::shared_ptr<sf::Texture> GetTexture(const std::string& texture);

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTextureMap;
	std::shared_ptr<sf::Texture> LoadTexture(const std::string& texturePath);
};