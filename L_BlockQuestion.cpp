#include "L_BlockQuestion.h"

void L_BlockQuestion::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;

	color_normal = sf::Color(64, 61, 41);
	color_focused = sf::Color(217, 217, 217);

	if (!tex_answer_background.loadFromFile("Content/ui/variant_bg.png")) {
		std::cout << "Error: Failed to load variant background texture" << std::endl;
	}
	tex_answer_background.setSmooth(true);

	UpdateScale();
	Resize();
}

void L_BlockQuestion::Render() {
	for (AnswerBlock& cur_answer_block : answer_blocks) {
		window->draw(cur_answer_block.m_background);
		window->draw(cur_answer_block.button->text_main);
	}
}

void L_BlockQuestion::Update() {
	
}

void L_BlockQuestion::Resize() {
	UpdateScale();
	start_position.x = 300.0f * scale_x;
	start_position.y = 150.0f * scale_y;

	delta_y = 600.0f / (float)answer_blocks.size() * scale_y;

	int cur_position = 0;
	for (AnswerBlock& cur_answer_block : answer_blocks) {
		cur_answer_block.m_background.setPosition(start_position + sf::Vector2f(0.0f, cur_position * delta_y));
		cur_answer_block.m_background.setSize({ 1320.0f * scale_x, 100 * scale_y });
		if (cur_answer_block.m_background.getTexture() == NULL) {
			cur_answer_block.m_background.setTexture(&tex_answer_background);
		}
		cur_answer_block.button->SetRectBounds(cur_answer_block.m_background.getPosition(), cur_answer_block.m_background.getSize());
		cur_answer_block.button->SetFontSize((int)(60 * scale_y));
		bnu::place_text_in_rect(cur_answer_block.m_background, cur_answer_block.button->text_main);
		cur_position++;
	}
}

void L_BlockQuestion::MouseMove(float mouse_x, float mouse_y) {
	for (AnswerBlock cur_answer_block : answer_blocks) {
		cur_answer_block.button->MouseMove(mouse_x, mouse_y);
	}
}

void L_BlockQuestion::UpdateLanguage() {

}

void L_BlockQuestion::MouseDown(sf::Event p_event, game_state clicked_state) {
	UpdateClickedMark();
}

void L_BlockQuestion::SetFont(sf::Font p_font_main) {
	font_main = p_font_main;
}

void L_BlockQuestion::SetVariants(std::vector<QuestionVariant> p_variants) {
	variants = p_variants;
	UpdateBlocks();
}

void L_BlockQuestion::UpdateBlocks() {
	answer_blocks.clear();
	for (QuestionVariant cur_variant : variants) {
		if (cur_variant.mark.empty() || cur_variant.text.empty()) {
			continue;
		}
		AnswerBlock block_to_add;
		block_to_add.texture = tex_answer_background;
		block_to_add.button->SetFont(font_main);
		block_to_add.button->SetText(cur_variant.text);
		block_to_add.button->SetColors(color_normal, color_focused);
		block_to_add.mark = cur_variant.mark;
		answer_blocks.push_back(block_to_add);
	}
	Resize();
}

void L_BlockQuestion::UpdateClickedMark() {
	clicked_mark = std::string();
	for (AnswerBlock cur_answer_block : answer_blocks) {
		if (cur_answer_block.button->focused) {
			clicked_mark = cur_answer_block.mark;
			if (action_go_forward != NULL) {
				action_go_forward();
			}
			return;
		}
	}
}
