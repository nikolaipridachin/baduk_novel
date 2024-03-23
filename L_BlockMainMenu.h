#pragma once
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "L_Block.h"
#include "L_TextButton.h"

class L_BlockMainMenu : public L_Block {
public:
	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Update() override;
	void Resize() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void UpdateLanguage() override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font_main);

	std::unique_ptr<L_TextButton> button_new_game;
	std::unique_ptr<L_TextButton> button_continue;
	std::unique_ptr<L_TextButton> button_settings;
	std::unique_ptr<L_TextButton> button_extras;
	std::unique_ptr<L_TextButton> button_exit;
private:
	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::Color color_normal;
	sf::Color color_focused;

	void UpdateFont() const;
};

