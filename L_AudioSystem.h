#pragma once
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>

class L_AudioSystem {
public:
	L_AudioSystem();
	void PlayMusic(std::string p_background_music);
	void StopMusic();

	void InitStoneSounds();
	void PlayTakeStoneSound();
	void PlayPlaceStoneSound();
private:
	sf::Music background_music_player;
	std::string background_music_name;
	sf::Sound sound_board;

	std::vector<sf::SoundBuffer> take_stone_sounds;
	std::vector<sf::SoundBuffer> place_stone_sounds;
};

