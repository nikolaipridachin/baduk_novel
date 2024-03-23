#include "L_BlockSaveLoadScreen.h"

void L_BlockSaveLoadScreen::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;

	UpdateScale();

	color_normal = sf::Color(79, 79, 79);
	color_focused = sf::Color(158, 158, 158);
	color_inacvite = sf::Color(158, 158, 158);

	button_back = std::make_unique<L_TextButton>(loc->GetW("st back"), font_main, (int)(46 * scale_y), color_focused, color_normal, 80.0f * scale_x, 0.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);

	if (!tex_background.loadFromFile("Content/ui/saveload_background.jpg")) {
		std::cout << "Error: Failed to load saveload background texture\n";
	}
	sprite_background.setTexture(&tex_background);
	sprite_background.setPosition(0.0f, 0.0f);

	text_title.setFillColor(color_normal);

	UpdateElements();
	UpdateLanguage();
}

void L_BlockSaveLoadScreen::Render() {
	window->draw(sprite_background);
	window->draw(text_title);
	window->draw(button_back->text_main);

	for (SaveLoadUIElement cur_element : save_load_elements) {
		window->draw(cur_element.sprite_preview);
		window->draw(cur_element.text_date);
		window->draw(cur_element.text_title);
	}
}

void L_BlockSaveLoadScreen::Update() {

}

void L_BlockSaveLoadScreen::Resize() {
	UpdateScale();
	sprite_background.setPosition(0.0f, 0.0f);
	sprite_background.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));

	text_title.setCharacterSize((int)(72 * scale_y));
	text_title.setPosition(530.0f * scale_x, 0.0f * scale_y);

	button_back->Resize((int)(46 * scale_y), 80.0f * scale_x, 0.0f * scale_y, 140.0f * scale_x, 70.0f * scale_y);
}

void L_BlockSaveLoadScreen::UpdateLanguage() {
	text_title.setString(loc->GetW("st title"));
	button_back->SetText(L"< " + loc->GetW("st back"));
}

void L_BlockSaveLoadScreen::MouseMove(float mouse_x, float mouse_y) {
	button_back->MouseMove(mouse_x, mouse_y);
}

void L_BlockSaveLoadScreen::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (clicked_state != game_state::SaveGame || clicked_state != game_state::LoadGame) {
		return;
	}
	if (p_event.type == sf::Event::MouseButtonPressed) {
		if (p_event.mouseButton.button == sf::Mouse::Left) {
			if (button_back->focused) {
				button_back->Click();
				return;
			}
		}
	}
}

void L_BlockSaveLoadScreen::SetFont(sf::Font p_font) {
	font_main = p_font;
	UpdateFont();
}

void L_BlockSaveLoadScreen::UpdateElements() {
	save_load_elements.clear();
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			SaveLoadUIElement element_to_add;
			save_load_elements.push_back(element_to_add);
			auto& new_element = save_load_elements.back();
			new_element.position = {(145.0f + 468.0f * i) * scale_x, (289.0f + 144.0f * j) * scale_y};
			new_element.preview_position = { 10.0f * scale_x, 8.0f * scale_y };

			if (!new_element.tex_preview.loadFromFile("Content/ui/test_preview.jpg")) {
				std::cout << "Failed to load preview" << std::endl;
			}
			new_element.preview_size = { 160.0f * scale_x, 90.0f * scale_y };
			new_element.sprite_preview.setTexture(&new_element.tex_preview);
			new_element.sprite_preview.setPosition(new_element.position + new_element.preview_position);
			new_element.sprite_preview.setSize(new_element.preview_size);

			new_element.date_position = { 185.0f * scale_x, 15.0f * scale_y };
			new_element.text_date.setString(L"10 февраля 2024");
			new_element.text_date.setPosition(new_element.position + new_element.date_position);
			new_element.text_date.setCharacterSize((int)(24.0f * scale_y));
			new_element.text_date.setFillColor(color_normal);
			 
			new_element.title_position = { 185.0f * scale_x, 55.0f * scale_y };
			new_element.text_title.setString(L"Твой новый мир");
			new_element.text_title.setPosition(new_element.position + new_element.title_position);
			new_element.text_title.setCharacterSize((int)(24.0f * scale_y));
			new_element.text_title.setFillColor(color_normal);
		}
	}
	for (int i = 0; i < save_load_elements.size(); i++) {
		save_load_elements[i].sprite_preview.setTexture(&save_load_elements[i].tex_preview);
	}
}

void L_BlockSaveLoadScreen::SetMode(std::string param) {
	if (param == "save") {
		text_title.setString(loc->GetW("sls save"));
		return;
	}
	if (param == "load") {
		text_title.setString(loc->GetW("sls load"));
		return;
	}
}

void L_BlockSaveLoadScreen::UpdateFont() {
	text_title.setFont(font_main);
	button_back->SetFont(font_main);
	for (int i = 0; i < save_load_elements.size(); i++) {
		save_load_elements[i].text_date.setFont(font_main);
		save_load_elements[i].text_title.setFont(font_main);
	}
}
