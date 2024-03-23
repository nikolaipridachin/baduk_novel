#include "L_BlockContextMenu.h"
using namespace std;

void L_BlockContextMenu::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	UpdateScale();
	color_normal = sf::Color(94, 92, 61);
	color_focused = sf::Color(217, 217, 217);

	if (!tex_background.loadFromFile("Content/ui/context_menu_background.png")) {
		cout << "Error loading background texture";
	}
	sprite_background.setTexture(&tex_background);

	button_back  = make_unique<L_TextButton>(				loc->GetW("cm back"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 168.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_show_background  = make_unique<L_TextButton>(	loc->GetW("cm show background"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 330.0f * scale_y, 390.0f * scale_x, 70.0f * scale_y, true);
	button_history = make_unique<L_TextButton>(				loc->GetW("cm history"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 473.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_skip = make_unique<L_TextButton>(				loc->GetW("cm skip"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 617.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_autoread = make_unique<L_TextButton>(			loc->GetW("cm autoread"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 765.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_settings = make_unique<L_TextButton>(			loc->GetW("cm settings"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 168.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_save = make_unique<L_TextButton>(				loc->GetW("cm save"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 330.0f * scale_y, 390.0f * scale_x, 70.0f * scale_y, true);
	button_load = make_unique<L_TextButton>(				loc->GetW("cm load"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 473.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_main_menu = make_unique<L_TextButton>(			loc->GetW("cm main menu"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 617.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_exit = make_unique<L_TextButton>(				loc->GetW("cm exit"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 765.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
}

void L_BlockContextMenu::Render() {
	window->draw(sprite_background);
	window->draw(button_back->text_main);
	window->draw(button_show_background->text_main);
	window->draw(button_history->text_main);
	window->draw(button_skip->text_main);
	window->draw(button_autoread->text_main);
	window->draw(button_settings->text_main);
	window->draw(button_save->text_main);
	window->draw(button_load->text_main);
	window->draw(button_main_menu->text_main);
	window->draw(button_exit->text_main);
}

void L_BlockContextMenu::Update() {

}

void L_BlockContextMenu::Resize() {
	UpdateScale();
	sprite_background.setPosition(714.0f * scale_x, 0.0f * scale_y);
	sprite_background.setSize(sf::Vector2f(492.0f * scale_x, 1080.0f * scale_y));

	button_back->Resize(				(int)(40 * scale_y), 770.0f * scale_x,  80.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_show_background->Resize(		(int)(40 * scale_y), 770.0f * scale_x, 183.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_history->Resize(				(int)(40 * scale_y), 770.0f * scale_x, 282.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_skip->Resize(				(int)(40 * scale_y), 770.0f * scale_x, 381.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_autoread->Resize(			(int)(40 * scale_y), 770.0f * scale_x, 479.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_settings->Resize(			(int)(40 * scale_y), 770.0f * scale_x, 581.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_save->Resize(				(int)(40 * scale_y), 770.0f * scale_x, 679.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_load->Resize(				(int)(40 * scale_y), 770.0f * scale_x, 777.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_main_menu->Resize(			(int)(40 * scale_y), 770.0f * scale_x, 875.0f * scale_y, 400.0f * scale_x, 70.0f * scale_y);
	button_exit->Resize(				(int)(40 * scale_y), 770.0f * scale_x, 973.0f * scale_y,  400.0f * scale_x, 70.0f * scale_y);
}

void L_BlockContextMenu::MouseMove(float mouse_x, float mouse_y) {
	button_back->MouseMove(mouse_x, mouse_y);
	button_show_background->MouseMove(mouse_x, mouse_y);
	button_history->MouseMove(mouse_x, mouse_y);
	button_skip->MouseMove(mouse_x, mouse_y);
	button_autoread->MouseMove(mouse_x, mouse_y);
	button_settings->MouseMove(mouse_x, mouse_y);
	button_save->MouseMove(mouse_x, mouse_y);
	button_load->MouseMove(mouse_x, mouse_y);
	button_main_menu->MouseMove(mouse_x, mouse_y);
	button_exit->MouseMove(mouse_x, mouse_y);
}

void L_BlockContextMenu::UpdateLanguage() {
	button_back->SetText(loc->GetW("cm back"));
	button_show_background->SetText(loc->GetW("cm show background"));
	button_history->SetText(loc->GetW("cm history"));
	button_skip->SetText(loc->GetW("cm skip"));
	button_autoread->SetText(loc->GetW("cm autoread"));
	button_settings->SetText(loc->GetW("cm settings"));
	button_save->SetText(loc->GetW("cm save"));
	button_load->SetText(loc->GetW("cm load"));
	button_main_menu->SetText(loc->GetW("cm main menu"));
	button_exit->SetText(loc->GetW("cm exit"));
}

void L_BlockContextMenu::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (p_event.type == sf::Event::MouseButtonPressed) {
		if (p_event.mouseButton.button == sf::Mouse::Left) {
			if (button_back->focused) {
				prevent_other_actions = true;
				button_back->Click();
				return;
			}
			if (button_show_background->focused) {
				prevent_other_actions = true;
				button_show_background->Click();
				return;
			}
			if (button_history->focused) {
				prevent_other_actions = true;
				button_history->Click();
				return;
			}
			if (button_skip->focused) {
				prevent_other_actions = true;
				button_skip->Click();
				return;
			}
			if (button_autoread->focused) {
				prevent_other_actions = true;
				button_autoread->Click();
				return;
			}
			if (button_settings->focused) {
				prevent_other_actions = true;
				button_settings->Click();
				return;
			}
			if (button_save->focused) {
				prevent_other_actions = true;
				button_save->Click();
				return;
			}
			if (button_load->focused) {
				prevent_other_actions = true;
				button_load->Click();
				return;
			}
			if (button_main_menu->focused) {
				prevent_other_actions = true;
				button_main_menu->Click();
				return;
			}
			if (button_exit->focused) {
				prevent_other_actions = true;
				button_exit->Click();
				return;
			}
		}
	}
}

void L_BlockContextMenu::SetFont(sf::Font p_font_main) {
	font_main = p_font_main;
	UpdateFont();
}

void L_BlockContextMenu::UpdateFont() const {
	button_back->SetFont(font_main);
	button_show_background->SetFont(font_main);
	button_history->SetFont(font_main);
	button_skip->SetFont(font_main);
	button_autoread->SetFont(font_main);
	button_settings->SetFont(font_main);
	button_save->SetFont(font_main);
	button_load->SetFont(font_main);
	button_main_menu->SetFont(font_main);
	button_exit->SetFont(font_main);
}
