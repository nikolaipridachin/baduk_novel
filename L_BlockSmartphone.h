#pragma once
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "L_Block.h"
#include "L_TextButton.h"
#include "L_ImageButton.h"

class L_BlockSmartphone : public L_Block{
public:
	std::function<void()> action_clicked_outside;

	std::unique_ptr<L_ImageButton> button_notes;
	std::unique_ptr<L_ImageButton> button_gallery;
	std::unique_ptr<L_ImageButton> button_baduktop;
	std::unique_ptr<L_ImageButton> button_maps;
	std::unique_ptr<L_ImageButton> button_calls;
	std::unique_ptr<L_ImageButton> button_messages;
	std::unique_ptr<L_ImageButton> button_settings;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Resize() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void UpdateLanguage() override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font_main);
private:
	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::Color color_normal;
	sf::Color color_focused;

	void UpdateFont();
};

