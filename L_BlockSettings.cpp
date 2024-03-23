#include "L_BlockSettings.h"

void L_BlockSettings::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	is_russian_selected = true;
	is_fullscreen_selected = false;
	is_whole_selected = false;

	UpdateScale();
	color_normal = sf::Color(79, 79, 79);
	color_focused = sf::Color(158, 158, 158);
	color_inacvite = sf::Color(158, 158, 158);

	if (!tex_background.loadFromFile("Content/ui/settings_background.jpg")) {
		std::cout << "Error: Failed to load settings screen background texture\n";
	}
	sprite_background.setTexture(&tex_background);
	sprite_background.setPosition(0.0f, 0.0f);

	button_back = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 80.0f * scale_x, 0.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_russian = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 770.0f * scale_x, 230.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_english = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 920.0f * scale_x, 230.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_fullscreen = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 820.0f * scale_x, 360.0f * scale_y, 180.0f * scale_x, 50.0f * scale_y);
	button_windowed = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 820.0f * scale_x, 420.0f * scale_y, 180.0f * scale_x, 50.0f * scale_y);
	button_whole = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 400.0f * scale_x, 360.0f * scale_y, 250.0f * scale_x, 50.0f * scale_y);
	button_readed = make_unique<L_TextButton>(loc->GetW("mm new game"), font_main, (int)(46 * scale_y), color_focused, color_normal, 400.0f * scale_x, 420.0f * scale_y, 250.0f * scale_x, 50.0f * scale_y);

	text_title.setFillColor(color_normal);
	text_skip.setFillColor(color_normal);
	text_screen_state.setFillColor(color_normal);
	text_text_speed.setFillColor(color_normal);
	text_autoread_speed.setFillColor(color_normal);
	text_music_volume.setFillColor(color_normal);
	text_sound_volume.setFillColor(color_normal);
	text_no_sound.setFillColor(color_inacvite);

	UpdateLanguage();
	UpdateColors();
	Resize();
}

void L_BlockSettings::Render() {
	window->draw(sprite_background);
	window->draw(text_title);
	window->draw(button_back->text_main);
	window->draw(text_skip);
	window->draw(button_whole->text_main);
	window->draw(button_readed->text_main);
	window->draw(text_screen_state);
	window->draw(button_windowed->text_main);
	window->draw(button_fullscreen->text_main);
	window->draw(text_text_speed);
	window->draw(text_autoread_speed);
	window->draw(text_music_volume);
	window->draw(text_sound_volume);
	window->draw(text_no_sound);
	window->draw(button_russian->text_main);
	window->draw(button_english->text_main);
}

void L_BlockSettings::Update() {

}

void L_BlockSettings::Resize() {
	UpdateScale();
	sprite_background.setPosition(0.0f, 0.0f);
	sprite_background.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));

	button_back->Resize((int)(46 * scale_y), 80.0f * scale_x, 0.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_russian->Resize((int)(46 * scale_y), 770.0f * scale_x, 230.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_english->Resize((int)(46 * scale_y), 920.0f * scale_x, 230.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
	button_fullscreen->Resize((int)(46 * scale_y), 820.0f * scale_x, 360.0f * scale_y, 180.0f * scale_x, 50.0f * scale_y);
	button_windowed->Resize((int)(46 * scale_y), 820.0f * scale_x, 420.0f * scale_y, 180.0f * scale_x, 50.0f * scale_y);
	button_whole->Resize((int)(46 * scale_y), 400.0f * scale_x, 360.0f * scale_y, 350.0f * scale_x, 50.0f * scale_y);
	button_readed->Resize((int)(46 * scale_y), 400.0f * scale_x, 420.0f * scale_y, 350.0f * scale_x, 50.0f * scale_y);

	text_title.setCharacterSize((int)(72 * scale_y));
	text_title.setPosition(530.0f * scale_x, 0.0f * scale_y);
	text_skip.setCharacterSize((int)(46 * scale_y));
	text_skip.setPosition(350.0f * scale_x, 300.0f * scale_y);
	text_screen_state.setCharacterSize((int)(46 * scale_y));
	text_screen_state.setPosition(770.0f * scale_x, 300.0f * scale_y);
	text_text_speed.setCharacterSize((int)(46 * scale_y));
	text_text_speed.setPosition(350.0f * scale_x, 540.0f * scale_y);
	text_autoread_speed.setCharacterSize((int)(46 * scale_y));
	text_autoread_speed.setPosition(350.0f * scale_x, 600.0f * scale_y);
	text_music_volume.setCharacterSize((int)(46 * scale_y));
	text_music_volume.setPosition(350.0f * scale_x, 720.0f * scale_y);
	text_sound_volume.setCharacterSize((int)(46 * scale_y));
	text_sound_volume.setPosition(350.0f * scale_x, 780.0f * scale_y);
	text_no_sound.setCharacterSize((int)(46 * scale_y));
	text_no_sound.setPosition(400.0f * scale_x, 840.0f * scale_y);
}

void L_BlockSettings::UpdateLanguage() {
	text_title.setString(loc->GetW("st title"));
	button_back->SetText(L"< " + loc->GetW("st back"));
	text_skip.setString(loc->GetW("st skip"));
	button_whole->SetText(loc->GetW("st all text"));
	button_readed->SetText(loc->GetW("st only readed"));
	text_screen_state.setString(loc->GetW("st screen state"));
	button_windowed->SetText(loc->GetW("st windowed"));
	button_fullscreen->SetText(loc->GetW("st fullscreen"));
	text_text_speed.setString(loc->GetW("st text speed"));
	text_autoread_speed.setString(loc->GetW("st autoread speed"));
	text_music_volume.setString(loc->GetW("st music volume"));
	text_sound_volume.setString(loc->GetW("st sounds volume"));
	text_no_sound.setString(loc->GetW("st no sound"));
	button_russian->SetText(loc->GetW("st russian"));
	button_english->SetText(loc->GetW("st english"));
}

void L_BlockSettings::MouseMove(float mouse_x, float mouse_y) {
	button_back->MouseMove(mouse_x, mouse_y);
	button_russian->MouseMove(mouse_x, mouse_y);
	button_english->MouseMove(mouse_x, mouse_y);
	button_fullscreen->MouseMove(mouse_x, mouse_y);
	button_windowed->MouseMove(mouse_x, mouse_y);
	button_whole->MouseMove(mouse_x, mouse_y);
	button_readed->MouseMove(mouse_x, mouse_y);
}

void L_BlockSettings::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (clicked_state != game_state::Settings) {
		return;
	}
	if (p_event.type == sf::Event::MouseButtonPressed) {
		if (p_event.mouseButton.button == sf::Mouse::Left) {
			if (button_back->focused) {
				button_back->Click();
				return;
			}
			if (!is_russian_selected && button_russian->focused) {
				is_russian_selected = true;
				UpdateColors();
				button_russian->Click();
				return;
			}
			if (is_russian_selected && button_english->focused) {
				is_russian_selected = false;
				UpdateColors();
				button_english->Click();
				return;
			}
			if (is_fullscreen_selected && button_windowed->focused) {
				is_fullscreen_selected = false;
				UpdateColors();
				button_windowed->Click();
				return;
			}
			if (!is_fullscreen_selected && button_fullscreen->focused) {
				is_fullscreen_selected = true;
				UpdateColors();
				button_fullscreen->Click();
				return;
			}
			if (is_whole_selected && button_readed->focused) {
				is_whole_selected = false;
				UpdateColors();
				button_readed->Click();
				return;
			}
			if (!is_whole_selected && button_whole->focused) {
				is_whole_selected = true;
				UpdateColors();
				button_whole->Click();
				return;
			}
		}
	}
}

void L_BlockSettings::SetFont(sf::Font p_font) {
	font_main = p_font;
	UpdateFont();
}

void L_BlockSettings::UpdateFont() {
	text_title.setFont(font_main);
	button_back->SetFont(font_main);
	text_skip.setFont(font_main);
	button_whole->SetFont(font_main);
	button_readed->SetFont(font_main);
	text_screen_state.setFont(font_main);
	button_windowed->SetFont(font_main);
	button_fullscreen->SetFont(font_main);
	text_text_speed.setFont(font_main);
	text_autoread_speed.setFont(font_main);
	text_music_volume.setFont(font_main);
	text_sound_volume.setFont(font_main);
	text_no_sound.setFont(font_main);
	button_russian->SetFont(font_main);
	button_english->SetFont(font_main);
}

void L_BlockSettings::InitTextObjects() {

}

void L_BlockSettings::InitRects() {

}

void L_BlockSettings::UpdateColors() {
	if (is_russian_selected) {
		button_russian->SetColors(color_normal, color_normal);
		button_english->SetColors(color_focused, color_focused);
	}
	else {
		button_russian->SetColors(color_focused, color_focused);
		button_english->SetColors(color_normal, color_normal);
	}
	if (is_fullscreen_selected) {
		button_windowed->SetColors(color_focused, color_focused);
		button_fullscreen->SetColors(color_normal, color_normal);
	}
	else {
		button_windowed->SetColors(color_normal, color_normal);
		button_fullscreen->SetColors(color_focused, color_focused);
	}
	if (is_whole_selected) {
		button_whole->SetColors(color_normal, color_normal);
		button_readed->SetColors(color_focused, color_focused);
	}
	else {
		button_whole->SetColors(color_focused, color_focused);
		button_readed->SetColors(color_normal, color_normal);
	}
}
