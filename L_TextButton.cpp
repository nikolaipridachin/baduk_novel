#include "L_TextButton.h"

L_TextButton::L_TextButton() {

}

L_TextButton::L_TextButton(std::wstring p_title, sf::Font p_font_title, int p_font_size, sf::Color p_color_normal, sf::Color p_color_active, float p_pos_x, float p_pos_y, float p_width, float p_height, bool p_centered) {
	color_normal = p_color_normal;
	color_focused = p_color_active;
	title = p_title;
	font_main = p_font_title;
	font_size = p_font_size;
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	width = p_width;
	height = p_height;
	centered = p_centered;

	UpdateState();
}

void L_TextButton::SetFont(sf::Font p_font_main) {
	font_main = p_font_main;
	UpdateState();
}

void L_TextButton::SetText(std::wstring p_title) {
	title = p_title;
	UpdateState();
}

void L_TextButton::MouseMove(float mouse_x, float mouse_y) {
	if (!active) {
		return;
	}
	if (bnu::is_point_in_rect(mouse_x, mouse_y, rect_bounds)) {
		if (!focused && iteractable) {
			text_main.setFillColor(color_focused);
		}
		focused = true;
	}
	else {
		if (focused && iteractable) {
			text_main.setFillColor(color_normal);
		}
		focused = false;
	}
}

void L_TextButton::Click() {
	if (action_click != nullptr) {
		action_click();
	}
}

void L_TextButton::SetFontSize(int p_font_size) {
	font_size = p_font_size;
	text_main.setCharacterSize(font_size);
}

void L_TextButton::SetPosition(float p_pos_x, float p_pos_y) {
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	UpdateState();
}

void L_TextButton::Resize(int p_font_size, float p_pos_x, float p_pos_y, float p_width, float p_height) {
	font_size = p_font_size;
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	width = p_width;
	height = p_height;
	UpdateState();
}

void L_TextButton::SetRectBounds(sf::Vector2f p_position, sf::Vector2f p_size) {
	rect_bounds.setPosition(p_position);
	rect_bounds.setSize(p_size);
}

void L_TextButton::SetColors(sf::Color p_color_normal, sf::Color p_color_focused) {
	color_normal = p_color_normal;
	color_focused = p_color_focused;
	UpdateState();
}

void L_TextButton::SetIteractable(bool param) {
	iteractable = param;
}

void L_TextButton::SetActive(bool p_active) {
	active = p_active;
}

void L_TextButton::UpdateState() {
	rect_bounds.setPosition(pos_x, pos_y);
	rect_bounds.setSize(sf::Vector2f(width, height));

	text_main.setString(title);
	text_main.setCharacterSize(font_size);
	if (focused) {
		text_main.setFillColor(color_focused);
	}
	else {
		text_main.setFillColor(color_normal);
	}

	text_main.setFont(font_main);
	if (centered) {
		bnu::place_text_in_rect(rect_bounds, text_main);
	}
	else {
		text_main.setPosition(pos_x, pos_y);
	}
}
	
