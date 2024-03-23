#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "bnu.h"

class L_ImageButton {
public:
	bool focused = false;
	sf::RectangleShape rect_main;
	std::string tex_normal_filename;
	sf::Texture tex_normal;
	std::string tex_focused_filename;
	sf::Texture tex_focused;
	float pos_x, pos_y;
	float width, height;
	bool iteractable = true;

	std::function<void()> action_click;

	L_ImageButton(std::string p_tex_normal_filename,
		std::string p_tex_focused_filename,
		float p_pos_x,
		float p_pos_y,
		float p_width,
		float p_height);
	void MouseMove(float mouse_x, float mouse_y);
	void Click();
	void SetPosition(float p_pos_x, float p_pos_y);
	void SetSize(float p_width, float p_height);
	void Resize(float p_pos_x, float p_pos_y, float p_width, float p_height);
	void SetIteractable(bool param);
private:
	void UpdateState();
	void InitTextures();
};

