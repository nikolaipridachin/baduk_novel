#include "L_BlockMessageBox.h"
using namespace std;

void L_BlockMessageBox::Render() {
	window->draw(sprite_background);
	window->draw(sprite_icon_smartphone);
	window->draw(text_name);
	window->draw(text_message);
}

void L_BlockMessageBox::Update() {
	UpdateMessageBoxText();
}

void L_BlockMessageBox::Resize() {
	UpdateScale();
	sprite_background.setPosition(0.0f, 863.0f * scale_y);
	sprite_background.setSize(sf::Vector2f(1920.0f * scale_x, 217.0f * scale_y));
	sprite_icon_smartphone.setPosition(1840.0f * scale_x, 783.0f * scale_y);
	sprite_icon_smartphone.setSize(sf::Vector2f(60.0f * scale_x, 60.0f * scale_y));
	text_name.setCharacterSize((int)(77 * scale_y));
	text_name.setPosition(30.0f * scale_x, 753.0f * scale_y);
	text_message.setCharacterSize((int)(46 * scale_y));
	text_message.setPosition(20.0f * scale_x, 880.0f * scale_y);
}

void L_BlockMessageBox::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (clicked_state != game_state::Gameplay) {
		return;
	}
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
	if (bnu::is_point_in_rect((float)mouse_position.x, (float)mouse_position.y, sprite_icon_smartphone)) {
		prevent_other_actions = true;
		if (action_icon_smartphone_clicked != nullptr) {
			action_icon_smartphone_clicked();
		}
	}
}

void L_BlockMessageBox::SetNameFont(sf::Font p_name_font) {
	name_font = p_name_font;
	text_name.setFont(name_font);
}

void L_BlockMessageBox::SetMessageBoxFont(sf::Font p_message_font) {
	message_font = p_message_font;
	text_message.setFont(message_font);
}

void L_BlockMessageBox::Say(std::wstring p_message, bool show_instantly) {
	if (show_instantly) {
		source_string = p_message;
		is_typing = false;
		ProcessSourceString();
		text_message.setString(result_string);
	}
	else {
		source_string = p_message;
		is_typing = true;
		ProcessSourceString();
		clock_type.restart();
	}
}

void L_BlockMessageBox::SetName(std::wstring p_name) {
	text_name.setString(p_name);
}

void L_BlockMessageBox::Init(sf::RenderWindow* p_window) {
	window = p_window;
	UpdateScale();

	if (!tex_background.loadFromFile("Content/ui/messagebox_bg.png")) {
		cout << "Error: Failed to load texture (messagebox background)";
	}
	sprite_background.setTexture(&tex_background);

	if (!tex_icon_smartphone.loadFromFile("Content/ui/smartphone_icon.png")) {
		cout << "Error: Failed to load texture (messagebox smartphone icon)";
	}
	sprite_icon_smartphone.setTexture(&tex_icon_smartphone);

	text_name.setString(L"");
	text_name.setCharacterSize((int)(77 * scale_y));
	text_name.setFillColor(sf::Color::White);
	text_name.setPosition(30.0f * scale_x, 753.0f * scale_y);
	text_name.setOutlineColor(sf::Color::Black);
	text_name.setOutlineThickness(2.0f);

	text_message.setString(L"");
	text_message.setCharacterSize((int)(46 * scale_y));
	text_message.setFillColor(sf::Color::White);
	text_message.setPosition(20.0f * scale_x, 880.0f * scale_y);
	text_message.setOutlineColor(sf::Color::Black);
	text_message.setOutlineThickness(2.0f);

	Resize();
}

void L_BlockMessageBox::ProcessSourceString() {
	float messagebox_width = base_messagebox_width * scale_y;
	sf::Vector2f text_local_bounds;
	wstring constructed_string;
	wstring partial_string;
	int string_length = (int)source_string.length();
	int accepted_width = 0;
	for (int i = 0; i < string_length; i++) {
		partial_string += source_string[i];
		text_message.setString(partial_string);
		if (text_message.getLocalBounds().width > messagebox_width) {
			constructed_string += partial_string.substr(0, accepted_width) + L"\n";
			partial_string.replace(0, accepted_width, L"");
			accepted_width = 0;
		}
		else {
			if (source_string[i] == L' ') {
				accepted_width = (int)partial_string.length();
			}
		}
	}
	constructed_string += partial_string;
	result_string = constructed_string;
}

void L_BlockMessageBox::UpdateMessageBoxText() {
	if (is_typing) {
		characters_to_show = (int)(clock_type.getElapsedTime().asMilliseconds() / type_interval);
		if (characters_to_show < result_string.length()) {
			text_message.setString(result_string.substr(0, characters_to_show));
		}
		else {
			text_message.setString(result_string);
			is_typing = false;
		}
	}
}
