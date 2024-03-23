#include "L_AudioSystem.h"

#include <filesystem>
#include <ctime>

L_AudioSystem::L_AudioSystem() {
	InitStoneSounds();
	std::srand(std::time(nullptr));
}

void L_AudioSystem::PlayMusic(std::string p_background_music) {
	std::string t_background_music_name = "Content/sound/background/" + p_background_music + ".wav";
	if (!background_music_player.openFromFile(t_background_music_name)) {
		// Error loading background music
		std::cout << "Error: Load background music failed - " << t_background_music_name << "\n";
	}
	else {
		background_music_player.setLoop(true);
		background_music_player.play();
	}
}

void L_AudioSystem::StopMusic() {
	background_music_player.stop();
}

void L_AudioSystem::InitStoneSounds() {
	take_stone_sounds.clear();
	std::string take_stone_sounds_path = "Content/sound/board/take_stone";
	for (const auto& entry : std::filesystem::directory_iterator(take_stone_sounds_path)) {
		sf::SoundBuffer buffer_to_add;
		if (buffer_to_add.loadFromFile(entry.path().string().c_str())) {
			take_stone_sounds.push_back(buffer_to_add);
		}
	}
	place_stone_sounds.clear();
	std::string place_stone_sounds_path = "Content/sound/board/place_stone";
	for (const auto& entry : std::filesystem::directory_iterator(place_stone_sounds_path)) {
		sf::SoundBuffer buffer_to_add;
		if (buffer_to_add.loadFromFile(entry.path().string().c_str())) {
			place_stone_sounds.push_back(buffer_to_add);
		}
	}
}

void L_AudioSystem::PlayTakeStoneSound() {
	int random_index = (std::rand() % (int)take_stone_sounds.size());
	sound_board.setBuffer(take_stone_sounds[random_index]);
	sound_board.play();
}

void L_AudioSystem::PlayPlaceStoneSound() {
	int random_index = (std::rand() % (int)place_stone_sounds.size());
	sound_board.setBuffer(place_stone_sounds[random_index]);
	sound_board.play();
}
