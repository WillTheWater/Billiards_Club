#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

// DEPRECATED AND NO LONGER IN USE

namespace Audio
{
	enum AudioType
	{
		BALL_WITH_BALL_COLLISION,
		BALL_WITH_TABLE_COLLISION,
		CUE_HIT,
		POCKET,
		BUTTON_DOWN,
		BUTTON_UP
	};

	static void				AddBuffer(AudioType type, const std::string& path);
	void					Init();
	sf::SoundBuffer&		GetSoundBuffer(AudioType type);
	void					PlaySound(sf::Sound& sound, AudioType type, float volume = 100.0f, float pitch = 1.0f);
	void					ToggleMute();
	

	static bool				IsMuted = false;
	static std::unordered_map<AudioType, sf::SoundBuffer> buffers;
}