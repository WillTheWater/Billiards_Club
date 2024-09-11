#include "Game.h"
#include "PlayState.h"

GUI::GUI(Game& game)
	: mGameRef{game}
	, mAudioOn{false}
{

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
	
	mStartButton->SetTexture("assets/graphics/button.png");
	mStartButton->SetupButton("assets/fonts/brush.ttf", "Play", 60, sf::Color::White, sf::Vector2f{ 645, 825});
	mStartButton->ScaleFont(1.8f, 1.f);
	
	mExitButton->SetTexture("assets/graphics/button.png");
	mExitButton->SetupButton("assets/fonts/brush.ttf", "Quit", 60, sf::Color::White, sf::Vector2f{ 955, 825 });
	mExitButton->ScaleFont(1.8f, 1.f);
}

void GUI::DrawMainMenu(Game& game)
{
	game.GetWindow().draw(mFloor);
	game.GetWindow().draw(mBackground);
	mStartButton->Draw(game.GetWindow());
	game.GetWindow().draw(mStartButton->GetButtonText());
	mExitButton->Draw(game.GetWindow());
	game.GetWindow().draw(mExitButton->GetButtonText());
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
	}
}

void GUI::PlaySetup(Game& game)
{
	mAudioButton = std::make_unique<Button>(game.GetTextureManager());

	mExitButton->SetupButton("assets/fonts/brush.ttf", "Quit", 60, sf::Color::White, sf::Vector2f{ 800, 825 });

	mAudioButton->SetTexture("assets/graphics/buttons.png"); mAudioButton->SetScale(0.35f);
	mAudioButton->SetPosition(sf::Vector2f{1510, 815 });

	// ================= Table Polygon ======================
	// Polygon vertices
	
	polygon.setPointCount(40);

	polygon.setPoint(0, sf::Vector2f(200, 150));
	polygon.setPoint(1, sf::Vector2f(285, 150));
	polygon.setPoint(2, sf::Vector2f(285, 200));
	polygon.setPoint(3, sf::Vector2f(315, 220));
	polygon.setPoint(4, sf::Vector2f(760, 220));
	polygon.setPoint(5, sf::Vector2f(765, 200));
	polygon.setPoint(6, sf::Vector2f(765, 150));
	polygon.setPoint(7, sf::Vector2f(835, 150));
	polygon.setPoint(8, sf::Vector2f(835, 200));
	polygon.setPoint(9, sf::Vector2f(840, 220));
	polygon.setPoint(10, sf::Vector2f(1285, 220));
	polygon.setPoint(11, sf::Vector2f(1315, 200));
	polygon.setPoint(12, sf::Vector2f(1315, 150));
	polygon.setPoint(13, sf::Vector2f(1400, 150));
	polygon.setPoint(14, sf::Vector2f(1400, 235));
	polygon.setPoint(15, sf::Vector2f(1350, 235));
	polygon.setPoint(16, sf::Vector2f(1330, 265));
	polygon.setPoint(17, sf::Vector2f(1330, 635));
	polygon.setPoint(18, sf::Vector2f(1350, 665));
	polygon.setPoint(19, sf::Vector2f(1400, 665));
	polygon.setPoint(20, sf::Vector2f(1400, 750));
	polygon.setPoint(21, sf::Vector2f(1315, 750));
	polygon.setPoint(22, sf::Vector2f(1315, 700));
	polygon.setPoint(23, sf::Vector2f(1285, 680));
	polygon.setPoint(24, sf::Vector2f(840, 680));
	polygon.setPoint(25, sf::Vector2f(835, 700));
	polygon.setPoint(26, sf::Vector2f(835, 750));
	polygon.setPoint(27, sf::Vector2f(765, 750));
	polygon.setPoint(28, sf::Vector2f(765, 700));
	polygon.setPoint(29, sf::Vector2f(760, 680));
	polygon.setPoint(30, sf::Vector2f(315, 680));
	polygon.setPoint(31, sf::Vector2f(285, 700));
	polygon.setPoint(32, sf::Vector2f(285, 750));
	polygon.setPoint(33, sf::Vector2f(200, 750));
	polygon.setPoint(34, sf::Vector2f(200, 665));
	polygon.setPoint(35, sf::Vector2f(250, 665));
	polygon.setPoint(36, sf::Vector2f(270, 635));
	polygon.setPoint(37, sf::Vector2f(270, 265));
	polygon.setPoint(38, sf::Vector2f(250, 235));
	polygon.setPoint(39, sf::Vector2f(200, 235));

	// Set holes (offset +200, +150)
	hole1.setRadius(35); hole1.setOrigin(35.f, 35.f); hole1.setPosition(250, 200); hole1.setFillColor(sf::Color(192, 57, 43, 100));
	hole2.setRadius(35); hole2.setOrigin(35.f, 35.f); hole2.setPosition(800, 200); hole2.setFillColor(sf::Color(192, 57, 43, 100));
	hole3.setRadius(35); hole3.setOrigin(35.f, 35.f); hole3.setPosition(1350, 200); hole3.setFillColor(sf::Color(192, 57, 43, 100));
	hole4.setRadius(35); hole4.setOrigin(35.f, 35.f); hole4.setPosition(250, 700); hole4.setFillColor(sf::Color(192, 57, 43, 100));
	hole5.setRadius(35); hole5.setOrigin(35.f, 35.f); hole5.setPosition(800, 700); hole5.setFillColor(sf::Color(192, 57, 43, 100));
	hole6.setRadius(35); hole6.setOrigin(35.f, 35.f); hole6.setPosition(1350, 700); hole6.setFillColor(sf::Color(192, 57, 43, 100));

	// Set color
	polygon.setFillColor(sf::Color(0,0,0,0));
	polygon.setOutlineColor(sf::Color::White);
	polygon.setOutlineThickness(1);
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

	// Debug Draw
	
	game.GetWindow().draw(hole1);
	game.GetWindow().draw(hole2);
	game.GetWindow().draw(hole3);
	game.GetWindow().draw(hole4);
	game.GetWindow().draw(hole5);
	game.GetWindow().draw(hole6);
	game.GetWindow().draw(polygon);
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
			if (mAudioOn) { std::cout << "Audio is turned on\n"; }
			if (!mAudioOn) { std::cout << "Audio is turned off\n"; }
		}
	}
}
