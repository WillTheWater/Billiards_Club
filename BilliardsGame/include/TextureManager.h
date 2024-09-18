#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "EntityGlobals.h"

class Game;

class TextureManager
{
public:
	TextureManager() = delete;
	TextureManager(Game& game);
	std::shared_ptr<sf::Texture>	GetTexture(const std::string& texture);
	std::shared_ptr<sf::Font>		GetFont(const std::string& font);
	const sf::Texture&				getBallOverlay();
	const sf::Texture&				getBallTexture(BallId id);
	const sf::Texture&				getBallTag(BallId id);
	const sf::Texture&				getCueStick();
	const sf::Sprite&				getWinSplashSprite();
	const sf::Sprite&				getLostSplashSprite();

private:
	Game& mGameRef;
	std::vector<std::unique_ptr<sf::Texture>>	mBallTextures;
	std::vector<std::unique_ptr<sf::Texture>>	mBallTags;
	std::unique_ptr<sf::Texture>				mBallOverlay;
	std::unique_ptr<sf::Texture>				mCueStick;
	std::unique_ptr<sf::Sprite>					mWinSplashSprite;
	std::unique_ptr<sf::Sprite>					mLostSplashSprite;
	std::unique_ptr<sf::Texture>				mWinSplashTexture;
	std::unique_ptr<sf::Texture>				mLostSplashTexture;

	void							loadBallTextures();
	void							loadCueStick();
	void							loadWinSplash();
	void							loadLostSplash();
	std::shared_ptr<sf::Texture>	LoadTexture(const std::string& texturePath);
	std::shared_ptr<sf::Font>		LoadFont(const std::string& fontPath);
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTextureMap;
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> mFontMap;
	
};