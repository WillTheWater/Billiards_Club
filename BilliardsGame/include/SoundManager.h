#pragma once
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <cassert>
#include <memory>


enum AudioType
{
	BALL_WITH_BALL_COLLISION,
	BALL_WITH_TABLE_COLLISION,
	CUE_HIT,
	POCKET,
	BUTTON_DOWN,
	BUTTON_UP,
	MAX_SOUNDS
};

class SoundManager
{
public:
	SoundManager();
	void initializeAudio();
	void playSound(AudioType sound, float volume = 100.0f, float pitch = 1.0f);
	void toggleMute(bool mute);
	bool isMuted();

	


private:
	std::vector<std::unique_ptr<sf::Sound>> mSounds;
	std::vector<std::unique_ptr<sf::SoundBuffer>> mBuffers;
	bool mMuted;
};

