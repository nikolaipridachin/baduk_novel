#include "L_ImageButton.h"
using namespace std;

L_ImageButton::L_ImageButton(std::string p_tex_normal_filename, std::string p_tex_focused_filename, float p_pos_x, float p_pos_y, float p_width, float p_height) {
	tex_normal_filename = p_tex_normal_filename;
	tex_focused_filename = p_tex_focused_filename;
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	width = p_width;
	height = p_height;

	InitTextures();
	UpdateState();
}

void L_ImageButton::MouseMove(float mouse_x, float mouse_y) {
	if (bnu::is_point_in_rect(mouse_x, mouse_y, rect_main)) {
		if (!focused && iteractable) {
			rect_main.setTexture(&tex_focused);
		}
		focused = true;
	}
	else {
		if (focused && iteractable) {
			rect_main.setTexture(&tex_normal);
		}
		focused = false;
	}
}

void L_ImageButton::Click() {
	if (action_click != nullptr) {
		action_click();
	}
}

void L_ImageButton::SetPosition(float p_pos_x, float p_pos_y) {
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	UpdateState();
}

void L_ImageButton::SetSize(float p_width, float p_height) {
	width = p_width;
	height = p_height;
	UpdateState();
}

void L_ImageButton::Resize(float p_pos_x, float p_pos_y, float p_width, float p_height) {
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	width = p_width;
	height = p_height;
	UpdateState();
}

void L_ImageButton::SetIteractable(bool param) {
	iteractable = param;
}

void L_ImageButton::UpdateState() {
	rect_main.setTexture(&tex_normal);
	rect_main.setPosition(pos_x, pos_y);
	rect_main.setSize(sf::Vector2f(width, height));
}

void L_ImageButton::InitTextures() {
	if (!tex_normal.loadFromFile(tex_normal_filename)) {
		cout << "Error: Faled to load texture (Image button texture):" << tex_normal_filename << "\n";
	}
	if (!tex_focused.loadFromFile(tex_focused_filename)) {
		cout << "Error: Faled to load texture (Image button texture):" << tex_focused_filename << "\n";
	}
}
