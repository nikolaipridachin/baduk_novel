#include "L_BlockCharacters.h"
using namespace std;

void L_BlockCharacters::Init(sf::RenderWindow* p_window) {
	window = p_window;
}

void L_BlockCharacters::Render() {
	if (character1_visible) {
		window->draw(sprite_character1);
	}
}

void L_BlockCharacters::Update() {
	UpdateScale();
}

void L_BlockCharacters::Resize() {
	UpdateScale();
	float texture_aspect = (float)tex_character1.getSize().x / (float)tex_character1.getSize().y;
	float character_height = character_base_height * scale_y * character1_scale;
	float character_width = character_height * texture_aspect;
	float character_pos_x = 1920.0f * scale_x * character1_pos_left;
	float character_pos_y = 1080.0f * scale_y - character_height + character_height * character1_pos_down;

	tex_character1.setSmooth(true);
	sprite_character1.setTexture(&tex_character1);
	sprite_character1.setPosition(character_pos_x, character_pos_y);
	sprite_character1.setSize(sf::Vector2f(character_width, character_height));
	sprite_character1.setTextureRect(sf::IntRect(0, 0, tex_character1.getSize().x, tex_character1.getSize().y));
	character1_visible = true;
}

void L_BlockCharacters::ShowCharacter(std::string name, std::string emotion, float p_pos_left, float p_pos_down, float p_scale, bool show_instantly) {
	string character_image_filename = "Content/characters/" + name + "/" + name + "_" + emotion + ".png";
	if (!tex_character1.loadFromFile(character_image_filename)) {
		// Error loading texture (character sprite)
		cout << "Error: Character load texture failed." << "\n";
		return;
	}
	character1_visible = true;
	character1_name = name;
	character1_emotion = emotion;
	character1_pos_left = p_pos_left;
	character1_pos_down = p_pos_down;
	character1_scale = p_scale;
	Resize();
}

void L_BlockCharacters::HideCharacters() {
	character1_visible = false;
}
