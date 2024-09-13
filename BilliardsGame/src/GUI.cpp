#include "Game.h"

GUI::GUI(Game& game)
	: mGameRef{game}
	, mAudioOn{false}
{
	Audio::IsMuted = true;
}

void GUI::MainMenuSetup(Game& game)
{
	// ================== Background ==================
	auto mFloorTexture = game.GetTextureManager().GetTexture("assets/graphics/carpet.png");
	mFloor.setTexture(*mFloorTexture);
	mFloor.setOrigin(sf::Vector2f{ mFloor.getGlobalBounds().width / 2.f, mFloor.getGlobalBounds().height / 2.f });
	mFloor.setPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f,game.GetWindowSize().y / 2.f });

	auto mBackgroundTexture = game.GetTextureManager().GetTexture("assets/graphics/table.png");
	mBackground.setTexture(*mBackgroundTexture);
	mBackground.setOrigin(sf::Vector2f{ mBackground.getGlobalBounds().width / 2.f, mBackground.getGlobalBounds().height / 2.f });
	mBackground.setPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f,game.GetWindowSize().y / 2.f });
	
	// ================== GUI ==================
	mStartButton = std::make_unique<Button>(game.GetTextureManager());
	mExitButton = std::make_unique<Button>(game.GetTextureManager());
	mAudioButton = std::make_unique<Button>(game.GetTextureManager());
	
	mStartButton->SetTexture("assets/graphics/button.png");
	mStartButton->SetupButton("assets/fonts/brush.ttf", "Play", 60, sf::Color::White, sf::Vector2f{ 645, 825});
	mStartButton->ScaleFont(1.8f, 1.f);
	
	mExitButton->SetTexture("assets/graphics/button.png");
	mExitButton->SetupButton("assets/fonts/brush.ttf", "Quit", 60, sf::Color::White, sf::Vector2f{ 955, 825 });
	mExitButton->ScaleFont(1.8f, 1.f);

	mAudioButton->SetTexture("assets/graphics/buttons.png"); mAudioButton->SetScale(0.35f);
	mAudioButton->SetPosition(sf::Vector2f{ 1510, 815 });
}

void GUI::DrawMainMenu(Game& game)
{
	if (!mAudioOn) { mAudioButton->SetTextureRect(2036, 624, 200, 200); }
	else { mAudioButton->SetTextureRect(1827, 624, 200, 200); }
	game.GetWindow().draw(mFloor);
	game.GetWindow().draw(mBackground);
	mStartButton->Draw(game.GetWindow());
	game.GetWindow().draw(mStartButton->GetButtonText());
	mExitButton->Draw(game.GetWindow());
	game.GetWindow().draw(mExitButton->GetButtonText());
	mAudioButton->Draw(game.GetWindow());
}

void GUI::MainMenuInput(Game& game)
{
	sf::Event event;
	while (game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			game.GetWindow().close();
		}
		if (mStartButton->HandleEvent(event))
		{
			game.GetStateStack().PushState(std::make_unique<PlayState>(game));
		}
		if (mExitButton->HandleEvent(event))
		{
			game.GetWindow().close();
		}
		if (mAudioButton->HandleEvent(event))
		{
			mAudioOn = !mAudioOn;
			if (mAudioOn) { Audio::ToggleMute(); std::cout << "Audio is turned on\n"; }
			if (!mAudioOn) { Audio::ToggleMute(); std::cout << "Audio is turned off\n"; }
		}
	}
}

void GUI::PlaySetup(Game& game)
{
	mAudioButton = std::make_unique<Button>(game.GetTextureManager());

	mExitButton->SetupButton("assets/fonts/brush.ttf", "Quit", 60, sf::Color::White, sf::Vector2f{ 800, 825 });

	mAudioButton->SetTexture("assets/graphics/buttons.png"); mAudioButton->SetScale(0.35f);
	mAudioButton->SetPosition(sf::Vector2f{1510, 815 });
}

void GUI::DrawPlay(Game& game)
{
	if (!mAudioOn) { mAudioButton->SetTextureRect(2036, 624, 200, 200); }
	else { mAudioButton->SetTextureRect(1827, 624, 200, 200); }
	game.GetWindow().draw(mFloor);
	game.GetWindow().draw(mBackground);
	mExitButton->Draw(game.GetWindow());
	game.GetWindow().draw(mExitButton->GetButtonText());
	mAudioButton->Draw(game.GetWindow());
}

void GUI::PlayInput(Game& game)
{
	sf::Event event;
	while (game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			game.GetWindow().close();
		}
		if (mExitButton->HandleEvent(event))
		{
			game.GetWindow().close();
		}
		if (mAudioButton->HandleEvent(event))
		{
			mAudioOn = !mAudioOn;
			if (mAudioOn) { Audio::ToggleMute(); std::cout << "Audio is turned on\n"; }
			if (!mAudioOn) { Audio::ToggleMute(); std::cout << "Audio is turned off\n"; }
		}
	}
}
