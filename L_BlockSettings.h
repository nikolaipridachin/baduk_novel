#pragma once
#include "L_Block.h"
#include "L_TextButton.h"
#include "L_Localization.h"

class L_BlockSettings : public L_Block {
public:
	game_state state_from = game_state::MainMenu;

	std::unique_ptr<L_TextButton> button_back;
	std::unique_ptr<L_TextButton> button_russian;
	std::unique_ptr<L_TextButton> button_english;
	std::unique_ptr<L_TextButton> button_fullscreen;
	std::unique_ptr<L_TextButton> button_windowed;
	std::unique_ptr<L_TextButton> button_whole;
	std::unique_ptr<L_TextButton> button_readed;

	bool is_russian_selected;
	bool is_fullscreen_selected;
	bool is_whole_selected;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Update() override;
	void Resize() override;
	void UpdateLanguage() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font);
private:
	sf::Color color_normal;
	sf::Color color_inacvite;
	sf::Color color_focused;

	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::Text text_title;
	sf::Text text_skip;
	sf::Text text_screen_state;
	sf::Text text_text_speed;
	sf::Text text_autoread_speed;
	sf::Text text_music_volume;
	sf::Text text_sound_volume;
	sf::Text text_no_sound;

	void UpdateFont();
	void InitTextObjects();
	void InitRects();
	void UpdateColors();
};

