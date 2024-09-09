#include "PlayState.h"
#include "Game.h"

PlayState::PlayState()
	: mAudioOn {false}
{
}

void PlayState::HandleInput(Game& game)
{
	sf::Event event;
	while (game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			game.GetWindow().close();
		}
		if (mQuitButton.HandleEvent(event))
		{
			game.GetWindow().close();
		}
		if (mAudioButton.HandleEvent(event))
		{
			mAudioOn = !mAudioOn;
			if (mAudioOn) { std::cout << "Audio is turned on\n"; }
			if (!mAudioOn) { std::cout << "Audio is turned off\n"; }
		}
	}
}

void PlayState::Update(Game& game, float deltaTime)
{
}

void PlayState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	BackgroundSetup(game);
	GUISetup(game);
	game.GetWindow().display();
}

void PlayState::GUISetup(Game& game)
{
	float margin = 8.f;
	mQuitButton.SetTexture("assets/graphics/buttons.png"); mQuitButton.SetTextureRect(609, 624, 600, 200); mQuitButton.SetScale(0.35f);
	mAudioButton.SetTexture("assets/graphics/buttons.png"); mAudioButton.SetScale(0.35f);
	if (!mAudioOn) { mAudioButton.SetTextureRect(2036, 624, 200, 200); }
	else { mAudioButton.SetTextureRect(1827, 624, 200, 200); }
	
	mQuitButton.SetPosition(sf::Vector2f{ game.GetWindowSize().x - 4.f * mQuitButton.GetBounds().width, game.GetWindowSize().y - mQuitButton.GetBounds().height - margin });
	mAudioButton.SetPosition(sf::Vector2f{ game.GetWindowSize().x - 3.f * mQuitButton.GetBounds().width + margin, game.GetWindowSize().y - mQuitButton.GetBounds().height - margin });
	mQuitButton.Draw(game.GetWindow());
	mAudioButton.Draw(game.GetWindow());
}

void PlayState::BackgroundSetup(Game& game)
{
	auto mBackgroundTexture = game.GetTextureManager().GetTexture("assets/graphics/table.png");
	mBackground.setTexture(*mBackgroundTexture);
	mBackground.setOrigin(sf::Vector2f{ mBackground.getGlobalBounds().width / 2.f, mBackground.getGlobalBounds().height / 2.f });
	mBackground.setPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f,game.GetWindowSize().y / 2.f });
	game.GetWindow().draw(mBackground);
}
