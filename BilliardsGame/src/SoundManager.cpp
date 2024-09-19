#include "SoundManager.h"

SoundManager::SoundManager()
	:mMuted{false}
{
	mSounds.reserve(AudioType::MAX_SOUNDS);
	mBuffers.reserve(AudioType::MAX_SOUNDS);
	initializeAudio();
}

void SoundManager::initializeAudio()
{
	for (int i{ 0 }; i < AudioType::MAX_SOUNDS; i++)
	{
		mSounds.push_back(std::make_unique<sf::Sound>());
		mBuffers.push_back(std::make_unique<sf::SoundBuffer>());
	}
	assert(std::ssize(mSounds) == AudioType::MAX_SOUNDS && "SoundManager failed to initialize correct number of sf::sound objects!\n");
	assert(std::ssize(mBuffers) == AudioType::MAX_SOUNDS && "SoundManager failed to initialize correct number of sf::soundbuffer objects!\n");

	mBuffers[BALL_WITH_BALL_COLLISION]->loadFromFile("assets/audio/ballcollision.wav");
	mBuffers[BALL_WITH_TABLE_COLLISION]->loadFromFile("assets/audio/tablecollision.wav");
	mBuffers[CUE_HIT]->loadFromFile("assets/audio/cuehit.wav");
	mBuffers[POCKET]->loadFromFile("assets/audio/pocket.wav");
	mBuffers[BUTTON_DOWN]->loadFromFile("assets/audio/buttonpressdown.wav");
	mBuffers[BUTTON_UP]	->loadFromFile("assets/audio/buttonpressup.wav");

	// Assign each sound to it's corresponding buffer
	for (int i{ 0 }; i < AudioType::MAX_SOUNDS; i++)
	{
		mSounds[i]->setBuffer(*mBuffers[i]);
	}
}

void SoundManager::playSound(AudioType sound, float volume, float pitch)
{
	assert(sound >= 0 && sound < AudioType::MAX_SOUNDS && "SoundManager::playSound attempted to call out of bounds sound/buffer!\n");
	mSounds[sound]->setVolume(volume);
	mSounds[sound]->setPitch(pitch);
	if (!mMuted || sound == AudioType::BUTTON_DOWN || sound == AudioType::BUTTON_UP)
	{
		mSounds[sound]->play();
	}
	
}

void SoundManager::toggleMute(bool mute)
{
	mMuted = mute;
}

bool SoundManager::isMuted()
{
	return mMuted;
}
