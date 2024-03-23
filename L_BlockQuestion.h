#pragma once
#include <vector>
#include <functional>
#include "L_Block.h"
#include "L_TextButton.h"
#include "baduk_structs.h"

struct AnswerBlock {
	sf::Texture texture;
	sf::RectangleShape m_background;
	std::shared_ptr<L_TextButton> button;
	std::string mark;

	AnswerBlock() {
		button = std::make_shared<L_TextButton>();
	}
};

class L_BlockQuestion : public L_Block {
public:
	std::string clicked_mark;
	std::function<void()> action_go_forward;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Update() override;
	void Resize() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void UpdateLanguage() override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font_main);
	void SetVariants(std::vector<QuestionVariant> p_variants);
	void UpdateBlocks();
private:
	std::vector<QuestionVariant> variants;	
	std::vector<AnswerBlock> answer_blocks;
	sf::Font font_main;
	sf::Vector2f start_position;
	float delta_y = 100.0f;

	sf::Texture tex_answer_background;
	sf::Color color_normal;
	sf::Color color_focused;
	void UpdateClickedMark();
};

