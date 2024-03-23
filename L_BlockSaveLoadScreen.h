#pragma once
#include "L_Block.h"
#include "L_TextButton.h"
#include "L_Localization.h"
#include "L_SaveLoadElement.h"

struct SaveLoadUIElement {
	sf::Vector2f position;

	sf::Vector2f date_position;
	sf::Text text_date;

	sf::Vector2f title_position;
	sf::Text text_title;

	sf::Texture tex_preview;
	sf::RectangleShape sprite_preview;

	sf::Vector2f preview_size;
	sf::Vector2f preview_position;
};

class L_BlockSaveLoadScreen : public L_Block {
public:
	std::unique_ptr<L_TextButton> button_back;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Update() override;
	void Resize() override;
	void UpdateLanguage() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font);
	void UpdateElements();
	void SetMode(std::string param);
private:
	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::Text text_title;

	sf::Color color_normal;
	sf::Color color_inacvite;
	sf::Color color_focused;

	std::vector<SaveLoadUIElement> save_load_elements;

	void UpdateFont();
};

