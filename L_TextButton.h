#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "bnu.h"

class L_TextButton {
public:
	bool active = true;
	bool focused = false;
	sf::RectangleShape rect_bounds;
	sf::Font font_main;
	sf::Text text_main;
	sf::Color color_normal;
	sf::Color color_focused;
	std::wstring title;
	int font_size = 60;
	float pos_x = 0.0f, pos_y = 0.0f;
	float width = 100.0f, height = 100.0f;
	std::function<void()> action_click;
	bool centered = false;
	bool iteractable = true;

	L_TextButton();
	L_TextButton(	std::wstring p_title,
				sf::Font p_font_title,
				int p_font_size, 
				sf::Color p_color_normal, 
				sf::Color p_color_focused, 
				float p_pos_x, 
				float p_pos_y,
				float p_width,
				float p_height,
				bool p_centered = false);
	void SetFont(sf::Font p_font_main);
	void SetText(std::wstring p_title);
	void MouseMove(float mouse_x, float mouse_y);
	void Click();
	void SetFontSize(int p_font_size);
	void SetPosition(float p_pos_x, float p_pos_y);
	void Resize(int p_font_size, float p_pos_x, float p_pos_y, float p_width, float p_height);
	void SetRectBounds(sf::Vector2f p_position, sf::Vector2f p_size);
	void SetColors(sf::Color p_color_normal, sf::Color p_color_focused);
	void SetIteractable(bool param);
	void SetActive(bool p_active);
private:
	void UpdateState();
};

