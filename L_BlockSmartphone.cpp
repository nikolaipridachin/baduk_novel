#include "L_BlockSmartphone.h"
using namespace std;

void L_BlockSmartphone::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	UpdateScale();
	color_normal = sf::Color(94, 92, 61);
	color_focused = sf::Color(217, 217, 217);

	if (!tex_background.loadFromFile("Content/ui/smartphone/smartphone_background.png")) {
		cout << "Error: Failed to load texture (smartphone background)";
	}
	tex_background.setSmooth(true);
	sprite_background.setTexture(&tex_background);

	button_notes = make_unique<L_ImageButton>("Content/ui/smartphone/icon_notes.png", "Content/ui/smartphone/icon_notes_focused.png", 93.0f * scale_x, 93.0f * scale_y, 836.0f * scale_x, 280.0f * scale_y);
	button_gallery = make_unique<L_ImageButton>("Content/ui/smartphone/icon_gallery.png", "Content/ui/smartphone/icon_gallery_focused.png", 1013.0f * scale_x, 279.0f * scale_y, 97.0f * scale_x, 91.0f * scale_y);
	button_baduktop = make_unique<L_ImageButton>("Content/ui/smartphone/icon_baduktop.png", "Content/ui/smartphone/icon_baduktop_focused.png", 1191.0f * scale_x, 277.0f * scale_y, 91.0f * scale_x, 90.0f * scale_y);
	button_maps = make_unique<L_ImageButton>("Content/ui/smartphone/icon_maps.png", "Content/ui/smartphone/icon_maps_focused.png", 835.0f * scale_x, 442.0f * scale_y, 92.0f * scale_x, 91.0f * scale_y);
	button_calls = make_unique<L_ImageButton>("Content/ui/smartphone/icon_calls.png", "Content/ui/smartphone/icon_calls_focused.png", 1431.0f * scale_x, 257.0f * scale_y, 93.0f * scale_x, 88.0f * scale_y);
	button_messages = make_unique<L_ImageButton>("Content/ui/smartphone/icon_messages.png", "Content/ui/smartphone/icon_messages_focused.png", 1430.0f * scale_x, 393.0f * scale_y, 95.0f * scale_x, 92.0f * scale_y);
	button_settings = make_unique<L_ImageButton>("Content/ui/smartphone/icon_settings.png", "Content/ui/smartphone/icon_settings_focused.png", 1431.0f * scale_x, 526.0f * scale_y, 94.0f * scale_x, 90.0f * scale_y);

	Resize();
}

void L_BlockSmartphone::Render() {
	window->draw(sprite_background);
	window->draw(button_notes->rect_main);
	window->draw(button_gallery->rect_main);
	window->draw(button_baduktop->rect_main);
	window->draw(button_maps->rect_main);
	window->draw(button_calls->rect_main);
	window->draw(button_messages->rect_main);
	window->draw(button_settings->rect_main);
}

void L_BlockSmartphone::Resize() {
	UpdateScale();
	sprite_background.setPosition(212.0f * scale_x, 68.0f * scale_y);
	sprite_background.setSize(sf::Vector2f(1496.0f * scale_x, 745.0f * scale_y));

	button_notes->Resize(836.0f * scale_x, 280.0f * scale_y, 93.0f * scale_x, 93.0f * scale_y);
	button_gallery->Resize(1013.0f * scale_x, 279.0f * scale_y, 97.0f * scale_x, 91.0f * scale_y);
	button_baduktop->Resize(1191.0f * scale_x, 277.0f * scale_y, 91.0f * scale_x, 90.0f * scale_y);
	button_maps->Resize(835.0f * scale_x, 442.0f * scale_y, 92.0f * scale_x, 91.0f * scale_y);
	button_calls->Resize(1431.0f * scale_x, 257.0f * scale_y, 93.0f * scale_x, 88.0f * scale_y);
	button_messages->Resize(1430.0f * scale_x, 393.0f * scale_y, 95.0f * scale_x, 92.0f * scale_y);
	button_settings->Resize(1431.0f * scale_x, 526.0f * scale_y, 94.0f * scale_x, 90.0f * scale_y);
}

void L_BlockSmartphone::MouseMove(float mouse_x, float mouse_y) {
	button_notes->MouseMove(mouse_x, mouse_y);
	button_gallery->MouseMove(mouse_x, mouse_y);
	button_baduktop->MouseMove(mouse_x, mouse_y);
	button_maps->MouseMove(mouse_x, mouse_y);
	button_calls->MouseMove(mouse_x, mouse_y);
	button_messages->MouseMove(mouse_x, mouse_y);
	button_settings->MouseMove(mouse_x, mouse_y);
}

void L_BlockSmartphone::UpdateLanguage() {

}

void L_BlockSmartphone::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (clicked_state != game_state::Smartphone) {
		return;
	}
	if (p_event.mouseButton.button == sf::Mouse::Right) {
		if (action_clicked_outside != nullptr) {
			prevent_other_actions = true;
			action_clicked_outside();
			return;
		}
	}
	if (p_event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
		if (button_baduktop->focused) {
			button_baduktop->Click();
			return;
		}
		if (!bnu::is_point_in_rect((float)mouse_position.x, (float)mouse_position.y, sprite_background)) {
			prevent_other_actions = true;
			if (action_clicked_outside != nullptr) {
				action_clicked_outside();
				return;
			}
		}
	}
}

void L_BlockSmartphone::SetFont(sf::Font p_font_main) {

}

void L_BlockSmartphone::UpdateFont() {

}
