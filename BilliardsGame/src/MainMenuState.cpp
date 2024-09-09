#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"

MainMenuState::MainMenuState()
{
}

void MainMenuState::HandleInput(Game& game)
{
	sf::Event event;
	while (game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			game.GetWindow().close();
		}
		if (mStartButton.HandleEvent(event))
		{
			game.GetStateStack().PushState(std::make_unique<PlayState>());
		}
		if (mExitButton.HandleEvent(event))
		{
			game.GetWindow().close();
		}
	}
}

void MainMenuState::Update(Game& game, float deltaTime)
{
}

void MainMenuState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	BackgroundSetup(game);
	GUISetup(game);
	game.GetWindow().display();
}

void MainMenuState::GUISetup(Game& game)
{
	mStartButton.SetTexture("assets/graphics/buttons.png"); mStartButton.SetTextureRect(0, 0, 600, 200);
	mExitButton.SetTexture("assets/graphics/buttons.png"); mExitButton.SetTextureRect(1218, 624, 600, 200);
	
	mStartButton.SetPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f - mStartButton.GetBounds().width / 2.f, game.GetWindowSize().y / 2.f - 200});
	mExitButton.SetPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f - mExitButton.GetBounds().width / 2.f, game.GetWindowSize().y / 2.f + 8});
	mStartButton.Draw(game.GetWindow());
	mExitButton.Draw(game.GetWindow());
}

void MainMenuState::BackgroundSetup(Game& game)
{
	auto mBackgroundTexture = game.GetTextureManager().GetTexture("assets/graphics/table.png");
	mBackground.setTexture(*mBackgroundTexture);
	mBackground.setOrigin(sf::Vector2f{ mBackground.getGlobalBounds().width / 2.f, mBackground.getGlobalBounds().height / 2.f });
	mBackground.setPosition(sf::Vector2f{ game.GetWindowSize().x / 2.f,game.GetWindowSize().y / 2.f });
	game.GetWindow().draw(mBackground);
}
