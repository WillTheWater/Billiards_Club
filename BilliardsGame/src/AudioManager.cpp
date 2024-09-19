#include "AudioManager.h"
#include <cassert>
#include <iostream>


static void Audio::AddBuffer(Audio::AudioType type, const std::string& path)
{
	sf::SoundBuffer buff;
	assert(buff.loadFromFile(path));
	buffers.emplace(type, buff);
}

void Audio::Init()
{
	AddBuffer(Audio::AudioType::BALL_WITH_BALL_COLLISION, "assets/audio/ballcollision.wav");
	AddBuffer(Audio::AudioType::BALL_WITH_TABLE_COLLISION, "assets/audio/tablecollision.wav");
	AddBuffer(Audio::AudioType::CUE_HIT, "assets/audio/cuehit.wav");
	AddBuffer(Audio::AudioType::POCKET, "assets/audio/pocket.wav");
	AddBuffer(Audio::AudioType::BUTTON_DOWN, "assets/audio/buttonpressdown.wav");
	AddBuffer(Audio::AudioType::BUTTON_UP, "assets/audio/buttonpressup.wav");
}

sf::SoundBuffer& Audio::GetSoundBuffer(Audio::AudioType type)
{
	const auto& it = buffers.find(type);
	assert(it != buffers.end());
	return it->second;
}

void Audio::PlaySound(sf::Sound& sound, Audio::AudioType type, float volume, float pitch)
{
	if (!IsMuted)
	{
		const sf::SoundBuffer& buffer = Audio::GetSoundBuffer(type);
		sound.setBuffer(buffer);
		sound.setVolume(volume);
		sound.setPitch(pitch);
		sound.play();
	}
}

void Audio::ToggleMute()
{
	IsMuted = !IsMuted;
	float volumeMultiplier = IsMuted ? 0.0f : 100.0f;
	for (auto& pair : buffers)
	{
		sf::Sound sound;
		sound.setBuffer(pair.second);
		sound.setVolume(sound.getVolume() * volumeMultiplier);
	}
	if (IsMuted) { std::cout << "ToggleMute: Muted\n"; }
	if (!IsMuted) { std::cout << "ToggleMute: Not Muted\n"; }
}