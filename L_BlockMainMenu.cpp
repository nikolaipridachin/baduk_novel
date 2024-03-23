#include "L_BlockMainMenu.h"
#include "bnu.h"
using namespace std;

void L_BlockMainMenu::Render() {
	window->draw(sprite_background);
	window->draw(button_new_game->text_main);
	window->draw(button_continue->text_main);
	window->draw(button_settings->text_main);
	window->draw(button_extras->text_main);
	window->draw(button_exit->text_main);
}

void L_BlockMainMenu::Update() {

}

void L_BlockMainMenu::Resize() {
	UpdateScale();
	sprite_background.setPosition(110.0f * scale_x, 0.0f * scale_y);
	sprite_background.setSize(sf::Vector2f(439.0f * scale_x, 882.0f * scale_y));

	button_new_game->Resize((int)(58 * scale_y), 137.0f * scale_x, 168.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y);
	button_continue->Resize((int)(58 * scale_y), 137.0f * scale_x, 330.0f * scale_y, 390.0f * scale_x, 70.0f * scale_y);
	button_settings->Resize((int)(58 * scale_y), 137.0f * scale_x, 473.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y);
	button_extras->Resize((int)(58 * scale_y), 137.0f * scale_x, 617.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y);
	button_exit->Resize((int)(58 * scale_y), 137.0f * scale_x, 765.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y);
}

void L_BlockMainMenu::MouseMove(float mouse_x, float mouse_y) {
	button_new_game->MouseMove(mouse_x, mouse_y);
	button_continue->MouseMove(mouse_x, mouse_y);
	button_settings->MouseMove(mouse_x, mouse_y);
	button_extras->MouseMove(mouse_x, mouse_y);
	button_exit->MouseMove(mouse_x, mouse_y);
}

void L_BlockMainMenu::UpdateLanguage() {
	button_new_game->SetText(loc->GetW("mm new game"));
	button_continue->SetText(loc->GetW("mm continue"));
	button_settings->SetText(loc->GetW("mm settings"));
	button_extras->SetText(loc->GetW("mm extras"));
	button_exit->SetText(loc->GetW("mm exit"));
}

void L_BlockMainMenu::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (p_event.mouseButton.button == sf::Mouse::Left) {
		if (button_new_game->focused) {
			button_new_game->Click();
			return;
		}
		if (button_continue->focused) {
			prevent_other_actions = true;
			button_continue->Click();
			return;
		}
		if (button_settings->focused) {
			button_settings->Click();
			return;
		}
		if (button_exit->focused) {
			button_exit->Click();
			return;
		}
	}
}

void L_BlockMainMenu::SetFont(sf::Font p_font_main) {
	font_main = p_font_main;
	UpdateFont();
}

void L_BlockMainMenu::UpdateFont() const {
	button_new_game->SetFont(font_main);
	button_continue->SetFont(font_main);
	button_settings->SetFont(font_main);
	button_extras->SetFont(font_main);
	button_exit->SetFont(font_main);
}

void L_BlockMainMenu::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	UpdateScale();
	color_normal = sf::Color(94, 92, 61);
	color_focused = sf::Color(217, 217, 217);

	if (!tex_background.loadFromFile("Content/ui/menu_buttons_background.png")) {
		cout << "Error loading background texture";
	}
	sprite_background.setTexture(&tex_background);

	button_new_game = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 168.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_continue = make_unique<L_TextButton>(loc->GetW("mm continue"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 330.0f * scale_y, 390.0f * scale_x, 70.0f * scale_y, true);
	button_settings = make_unique<L_TextButton>(loc->GetW("mm settings"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 473.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_extras = make_unique<L_TextButton>(loc->GetW("mm extras"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 617.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
	button_exit = make_unique<L_TextButton>(loc->GetW("mm exit"), font_main, (int)(58 * scale_y), color_normal, color_focused, 137.0f * scale_x, 765.0f * scale_y, 390.0f * scale_x, 84.0f * scale_y, true);
}