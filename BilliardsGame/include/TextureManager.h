#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Game;

class TextureManager
{
public:
	TextureManager() = delete;
	TextureManager(Game& game);
	std::shared_ptr<sf::Texture>	GetTexture(const std::string& texture);
	std::shared_ptr<sf::Font>		GetFont(const std::string& font);

private:
	Game& mGameRef;
	std::shared_ptr<sf::Texture>	LoadTexture(const std::string& texturePath);
	std::shared_ptr<sf::Font>		LoadFont(const std::string& fontPath);
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTextureMap;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> mFontMap;
};