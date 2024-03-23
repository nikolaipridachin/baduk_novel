#pragma once
#include <memory>
#include "L_Block.h"
#include "SFML/Graphics.hpp"
class L_BlockCharacters : public L_Block {
public:
	void Init(sf::RenderWindow* p_window);
	void Render() override;
	void Update() override;
	void Resize() override;
	void ShowCharacter(std::string name, std::string emotion, float p_pos_left, float p_pos_down, float p_scale, bool show_instantly);
	void HideCharacters();

private:
	float character_base_height = 1080.0f;
	bool character1_visible = true;
	std::string character1_name;
	std::string character1_emotion;
	float character1_pos_left;
	float character1_pos_down;
	float character1_scale;
	sf::RectangleShape sprite_character1;
	sf::Texture tex_character1;
};

