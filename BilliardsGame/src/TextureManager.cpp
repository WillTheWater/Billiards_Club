#include <iostream>
#include "Game.h"

TextureManager::TextureManager(Game& game)
    :mGameRef{ game }
{
    loadBallTextures();
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

const sf::Texture& TextureManager::getBallOverlay()
{
    return *mBallOverlay;
}

void TextureManager::loadBallTextures()
{
    //
    for (size_t i{ 0 }; i < BallId_MAX_BALL_ID; i++)
    {
        mBallTextures.push_back(std::make_unique<sf::Texture>());
        mBallTags.push_back(std::make_unique<sf::Texture>());
    }
    assert(mBallTextures.size() == BallId_MAX_BALL_ID && "LoadBallTextures in texture manager did not create the right number of ball textures!\n");
    assert(mBallTags.size() == BallId_MAX_BALL_ID && "LoadBallTextures in texture manager did not create the right number of tag textures!\n");

    mBallTextures[BallId::BallId_cueBall]->loadFromFile("assets/graphics/cueball.png");
    mBallTextures[BallId::BallId_one]->loadFromFile("assets/graphics/ball_yellow.png");
    mBallTextures[BallId::BallId_two]->loadFromFile("assets/graphics/ball_blue.png");
    mBallTextures[BallId::BallId_three]->loadFromFile("assets/graphics/ball_red.png");
    mBallTextures[BallId::BallId_four]->loadFromFile("assets/graphics/ball_purple.png");
    mBallTextures[BallId::BallId_five]->loadFromFile("assets/graphics/ball_orange.png");
    mBallTextures[BallId::BallId_six]->loadFromFile("assets/graphics/ball_green.png");
    mBallTextures[BallId::BallId_seven]->loadFromFile("assets/graphics/ball_magenta.png");
    mBallTextures[BallId::BallId_eight]->loadFromFile("assets/graphics/8ball.png");
    mBallTextures[BallId::BallId_nine]->loadFromFile("assets/graphics/ball_yellow.png");
    mBallTextures[BallId::BallId_ten]->loadFromFile("assets/graphics/ball_blue.png");
    mBallTextures[BallId::BallId_eleven]->loadFromFile("assets/graphics/ball_red.png");
    mBallTextures[BallId::BallId_twelve]->loadFromFile("assets/graphics/ball_purple.png");
    mBallTextures[BallId::BallId_thirteen]->loadFromFile("assets/graphics/ball_orange.png");
    mBallTextures[BallId::BallId_fourteen]->loadFromFile("assets/graphics/ball_green.png");
    mBallTextures[BallId::BallId_fifteen]->loadFromFile("assets/graphics/ball_magenta.png");

    mBallOverlay = std::make_unique<sf::Texture>();
    if (!mBallOverlay->loadFromFile("assets/graphics/alphaball.png"))
    {
        assert(0 && "TextureManager::loadBallTextures failed to load the ball overlay! \n");
    }
    
    // Load all of the tags
    mBallTags[0].reset(nullptr);    // Cue Ball has no tags, but we still want the vector to offest by ballid so we need an empty one here.
    for (size_t i{ 1 }; i < BallId_MAX_BALL_ID; i++)
    {
        std::string file = std::to_string(i) + "tag.png";
        std::string path = "assets/graphics/" + file;
        if (!mBallTags[i]->loadFromFile(path))
        {
            std::cout << "TextureManager::loadBallTextures failed to load the ball tag at: " << path << " ! \n";
        };
    }
}

const sf::Texture& TextureManager::getBallTexture(BallId id)
{
    assert(id < BallId::BallId_MAX_BALL_ID && id >= 0);
    return *mBallTextures[id];
}

const sf::Texture& TextureManager::getBallTag(BallId id)
{
    if (id < BallId_one || id >= BallId_MAX_BALL_ID)
    {
        assert("getBallTag called on ball that does not have a tag, or outside of range!\n");
    } 
    else if (mBallTags[id] == nullptr)
    {
        assert("getBallTag called on ball that does not have a tag, or outside of range!\n");
        
    }
    else
    {
        return *mBallTags[id];
    }

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
