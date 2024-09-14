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
	while (game.GetWindow().pollEvent(event))
	{
		game.GetGUI().PlayInput(event);
		if (physicsEngine.AreBallsAtRest())
		{
		
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if(event.key.scancode == sf::Keyboard::Scan::R)
			game.GetPhysicsEngine().debugRandomizeBalls();
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left && physicsEngine.AreBallsAtRest() && !inputManager.IsMouseOverCueBall())
			{
				inputManager.initialiazeCueStickAnim(60);
			}
		}
		else if(!cueStick.isAnimationActive() && physicsEngine.AreBallsAtRest())
		{
			mGameRef.GetInputManager().updateCueStick();
		}
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
	game.GetGUI().DrawPlay(game);
	auto& renderManager = game.GetRenderManager();
	renderManager.RenderBalls();
	renderManager.RenderCue();
	game.GetWindow().display();
}

void PlayState::PlayGUISetup(Game& game)
{
	game.GetGUI().PlaySetup(game);
}
