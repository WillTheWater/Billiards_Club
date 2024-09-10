#pragma once
#include "State.h"
#include "Button.h"

class PlayState : public State
{
public:
	PlayState();
	virtual						~PlayState() = default;
	void						HandleInput(Game& game) override;
	virtual void				Update(Game& game, float deltaTime) override;
	virtual void				Draw(Game& game) override;

private:
	void						GUISetup(Game& game);
	void						BackgroundSetup(Game& game);
	sf::Sprite					mBackground;
	std::unique_ptr<Button>		mQuitButton;
	std::unique_ptr<Button>		mAudioButton;
	bool						mAudioOn;
};

