#pragma once
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "L_Block.h"
class L_BlockMessageBox : public L_Block {
public:
	std::function<void()> action_icon_smartphone_clicked;

	void Init(sf::RenderWindow* p_window);
	void Render() override;
	void Update() override;
	void Resize() override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetNameFont(sf::Font p_name_font);
	void SetMessageBoxFont(sf::Font p_message_font);
	void Say(std::wstring p_message, bool show_instantly = false);
	void SetName(std::wstring p_name);

	std::wstring GetName() const { return text_name.getString(); };
	std::wstring GetMessage() const { return text_message.getString(); };
private:
	sf::Font name_font;
	sf::Font message_font;
	sf::Text text_name;
	sf::Text text_message;

	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::RectangleShape sprite_icon_smartphone;
	sf::Texture tex_icon_smartphone;

	float base_messagebox_width = 1900.0f;
	std::wstring source_string;
	std::wstring result_string;
	bool is_typing = false;
	sf::Clock clock_type;
	float type_interval = 10.0f;
	int characters_to_show = 0;

	void ProcessSourceString();
	void UpdateMessageBoxText();
};

