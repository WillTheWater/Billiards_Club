#include "Game.h"

PlayState::PlayState(Game& game)
	: mGameRef(game)
{
	PlayGUISetup(game);
}

void PlayState::HandleInput(Game& game)
{
	sf::Event event;
	auto& inputManager = mGameRef.GetInputManager();
	auto& physicsEngine = mGameRef.GetPhysicsEngine();
	auto& cueStick = mGameRef.GetEntityManager().getCueStick();

	if (physicsEngine.AreBallsAtRest() && !game.IsGameOver())
	{
		game.CheckWinConditionOnBallSunk();
	}

	while (game.GetWindow().pollEvent(event))
	{
		if (game.IsGameOver())
		{
			if (event.key.scancode == sf::Keyboard::Scan::R)
			{
				game.ResetGame();
				return;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left && physicsEngine.AreBallsAtRest() && !inputManager.IsMouseOverCueBall() && !game.IsGameOver())
			{
				game.IncrementShotsTaken();
				inputManager.initialiazeCueStickAnim(60);
			}
		}
		else if(!cueStick.isAnimationActive() && physicsEngine.AreBallsAtRest() && !game.IsGameOver())
		{
			mGameRef.GetInputManager().updateCueStick();
		}

		game.GetGUI().PlayInput(event);
	}
}

void PlayState::Update(Game& game, float deltaTime)
{
	auto& cueBall = mGameRef.GetEntityManager().getCueBall();
	auto& cueStick = mGameRef.GetEntityManager().getCueStick();
	auto& inputManager = mGameRef.GetInputManager();
	if (cueStick.isAnimationActive())
	{
		cueStick.stepAnimation();
		if (!cueStick.animationStepsLeft())
		{
			inputManager.giveCueBallStrikeVelocity();
			cueStick.toggleVisiblity(false);
		}
	}
	if (game.GetPhysicsEngine().AreBallsAtRest())
	{
		if (!cueBall.isVisible())
		{
			mGameRef.GetEntityManager().ResetCueBall();
		}
	}
	game.GetPhysicsEngine().Update(deltaTime);
	game.GetInputManager().debugCueOutline();
}

void PlayState::Draw(Game& game)
{
	game.GetWindow().clear(sf::Color::Black);
	game.GetGUI().DrawBackground(game);
	auto& renderManager = game.GetRenderManager();
	renderManager.RenderBalls();
	renderManager.RenderCue();
	renderManager.DrawShotsTaken();
	if (game.IsGameWon())
	{
		renderManager.DrawGameWon();
	}
	if (game.isGameLost())
	{
		renderManager.DrawGameLost();
	}
	game.GetGUI().DrawPlay(game);
	game.GetWindow().display();
	

	
}

void PlayState::PlayGUISetup(Game& game)
{
	game.GetGUI().PlaySetup(game);
}
