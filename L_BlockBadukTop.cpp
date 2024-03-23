#include "L_BlockBadukTop.h"
using namespace std;

void L_BlockBadukTop::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	state = baduktop_state::MainScreen;
	UpdateScale();
	color_normal = sf::Color(255, 255, 255);
	color_focused = sf::Color(249, 236, 131);
	main_field.SetSize(10, 6);

	if (!tex_background.loadFromFile("Content/ui/smartphone/baduktop_background_select_screen.png")) {
		cout << "Error: Failed to load texture (baduktop background)";
	}
	tex_background.setSmooth(true);
	sprite_background.setTexture(&tex_background);

	//Main screen	
	if (!tex_background_main_screen.loadFromFile("Content/ui/smartphone/baduktop_background_main_screen.png")) {
		cout << "Error: Failed to load texture (baduktop background main screen)";
	}
	tex_background_main_screen.setSmooth(true);
	sprite_background_main_screen.setTexture(&tex_background_main_screen);

	button_back = make_unique<L_TextButton>(L"< " + loc->GetW("sm bt back"), font_main, (int)(60 * scale_y), color_normal, color_focused, 1430.0f * scale_x, 135.0f * scale_y, 130.0f * scale_x, 70.0f * scale_y);
	button_solving_left = make_unique<L_TextButton>(loc->GetW("pagination left"), font_main, (int)(80 * scale_y), color_normal, color_focused, 400.0f * scale_x, 400.0f * scale_y, 150.0f * scale_x, 90.0f * scale_y);
	button_solving_right = make_unique<L_TextButton>(loc->GetW("pagination right"), font_main, (int)(80 * scale_y), color_normal, color_focused, 1400.0f * scale_x, 400.0f * scale_y, 150.0f * scale_x, 90.0f * scale_y);
	button_level_1 = make_unique<L_TextButton>(loc->GetW("sm bt level 1"), font_main, (int)(80 * scale_y), color_normal, color_focused, 330.0f * scale_x, 250.0f * scale_y, 320.0f * scale_x, 70.0f * scale_y);
	button_level_2 = make_unique<L_TextButton>(loc->GetW("sm bt level 2"), font_main, (int)(80 * scale_y), color_normal, color_focused, 330.0f * scale_x, 330.0f * scale_y, 320.0f * scale_x, 70.0f * scale_y);
	button_level_3 = make_unique<L_TextButton>(loc->GetW("sm bt level 3"), font_main, (int)(80 * scale_y), color_normal, color_focused, 330.0f * scale_x, 410.0f * scale_y, 320.0f * scale_x, 70.0f * scale_y);
	button_level_4 = make_unique<L_TextButton>(loc->GetW("sm bt level 4"), font_main, (int)(80 * scale_y), color_normal, color_focused, 330.0f * scale_x, 490.0f * scale_y, 320.0f * scale_x, 70.0f * scale_y);
	button_collection_1 = make_unique<L_TextButton>(loc->GetW("sm sp variant 1"), font_main, (int)(80 * scale_y), color_normal, color_focused, 730.0f * scale_x, 250.0f * scale_y, 600.0f * scale_x, 70.0f * scale_y);
	button_collection_2 = make_unique<L_TextButton>(loc->GetW("sm sp variant 2"), font_main, (int)(80 * scale_y), color_normal, color_focused, 730.0f * scale_x, 330.0f * scale_y, 600.0f * scale_x, 70.0f * scale_y);
	button_collection_3 = make_unique<L_TextButton>(loc->GetW("sm sp variant 3"), font_main, (int)(80 * scale_y), color_normal, color_focused, 730.0f * scale_x, 410.0f * scale_y, 600.0f * scale_x, 70.0f * scale_y);
	button_collection_4 = make_unique<L_TextButton>(loc->GetW("sm sp variant 4"), font_main, (int)(80 * scale_y), color_normal, color_focused, 730.0f * scale_x, 490.0f * scale_y, 600.0f * scale_x, 70.0f * scale_y);
	button_collection_5 = make_unique<L_TextButton>(loc->GetW("sm sp variant 5"), font_main, (int)(80 * scale_y), color_normal, color_focused, 730.0f * scale_x, 570.0f * scale_y, 600.0f * scale_x, 70.0f * scale_y);
	button_pagination_main_screen_left = make_unique<L_TextButton>(loc->GetW("pagination left"), font_main, (int)(48 * scale_y), color_normal, color_focused, 800.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y, true);
	button_pagination_main_screen_right = make_unique<L_TextButton>(loc->GetW("pagination right"), font_main, (int)(48 * scale_y), color_normal, color_focused, 1200.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y, true);
	rect_pagination_main_screen.setPosition(780.0f * scale_x, 675.0f * scale_y);
	rect_pagination_main_screen.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_pagination_main_screen.setCharacterSize((int)(48 * scale_y));
	text_pagination_main_screen.setFillColor(color_normal);
	bnu::place_text_in_rect(rect_pagination_main_screen, text_pagination_main_screen);

	//Solving screen
	rect_result_message.setPosition(500.0f * scale_x, 130.0f * scale_y);
	rect_result_message.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_result_message.setCharacterSize((int)(80 * scale_y));
	text_result_message.setFillColor(color_focused);
	text_result_message.setString(L"Правильно!");
	bnu::place_text_in_rect(rect_result_message, text_result_message);

	if (!tex_preview_problem_background.loadFromFile("Content/ui/smartphone/baduk_field_background.png")) {
		cout << "Error: Failed to load texture (tex_preview_problem_background)" << "\n";
	}

	float preview_texture_width = 703.0f;
	float preview_texture_height = 431.0f;
	float sprite_goproblem_pos_x = 600.0f;
	float sprite_goproblem_pos_y = 215.0f;
	float scale_factor = 1.0f;	
	float preview_width = 245.0f;
	float preview_height = 149.0f;
	float pos_x = 345.0f;
	float pos_y = 260.0f;
	float step_x = 320.0f;
	float step_y = 220.0f;
	float stone_pos_x = 359.0f;
	float stone_pos_y = 371.0f;
	float stone_grid_step = 24.0f;
	float stone_size = 22.0f;
	float main_field_pos_x = 643.0f;
	float main_field_pos_y = 535.0f;
	float main_grid_step = 68.8f;
	float main_stone_size = 68.0f;

	sprite_goproblem_background.setPosition(sprite_goproblem_pos_x * scale_x, sprite_goproblem_pos_y * scale_y);
	sprite_goproblem_background.setSize(sf::Vector2f(preview_texture_width * scale_factor * scale_x, preview_texture_height * scale_factor * scale_y));
	sprite_goproblem_background.setTexture(&tex_preview_problem_background);

	main_field.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	main_field.SetPosition(main_field_pos_x * scale_x, main_field_pos_y * scale_y);
	main_field.SetGridStep(main_grid_step * scale_y);
	main_field.SetStoneSize(main_stone_size * scale_y);

	//Preview screen

	sprite_preview_background_1.setPosition(pos_x * scale_x, pos_y * scale_y);
	sprite_preview_background_1.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_1.setTexture(&tex_preview_problem_background);
	sprite_preview_background_2.setPosition((pos_x + step_x) * scale_x, pos_y * scale_y);
	sprite_preview_background_2.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_2.setTexture(&tex_preview_problem_background);
	sprite_preview_background_3.setPosition((pos_x + step_x * 2) * scale_x, pos_y * scale_y);
	sprite_preview_background_3.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_3.setTexture(&tex_preview_problem_background);
	sprite_preview_background_4.setPosition((pos_x + step_x * 3) * scale_x, pos_y * scale_y);
	sprite_preview_background_4.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_4.setTexture(&tex_preview_problem_background);
	sprite_preview_background_5.setPosition(pos_x * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_5.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_5.setTexture(&tex_preview_problem_background);
	sprite_preview_background_6.setPosition((pos_x + step_x) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_6.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_6.setTexture(&tex_preview_problem_background);
	sprite_preview_background_7.setPosition((pos_x + step_x * 2) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_7.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_7.setTexture(&tex_preview_problem_background);
	sprite_preview_background_8.setPosition((pos_x + step_x * 3) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_8.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_8.setTexture(&tex_preview_problem_background);

	sprite_preview_backgrounds.push_back(sprite_preview_background_1);
	sprite_preview_backgrounds.push_back(sprite_preview_background_2);
	sprite_preview_backgrounds.push_back(sprite_preview_background_3);
	sprite_preview_backgrounds.push_back(sprite_preview_background_4);
	sprite_preview_backgrounds.push_back(sprite_preview_background_5);
	sprite_preview_backgrounds.push_back(sprite_preview_background_6);
	sprite_preview_backgrounds.push_back(sprite_preview_background_7);
	sprite_preview_backgrounds.push_back(sprite_preview_background_8);

	graphic_field_preview_1.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_1.SetPosition(stone_pos_x * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_1.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_1.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_2.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_2.SetPosition((stone_pos_x + step_x) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_2.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_2.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_3.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_3.SetPosition((stone_pos_x + step_x * 2) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_3.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_3.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_4.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_4.SetPosition((stone_pos_x + step_x * 3) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_4.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_4.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_5.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_5.SetPosition(stone_pos_x * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_5.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_5.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_6.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_6.SetPosition((stone_pos_x + step_x) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_6.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_6.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_7.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_7.SetPosition((stone_pos_x + step_x * 2) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_7.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_7.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_8.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");
	graphic_field_preview_8.SetPosition((stone_pos_x + step_x * 3) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_8.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_8.SetStoneSize(stone_size * scale_y);

	graphic_fields.push_back(&graphic_field_preview_1);
	graphic_fields.push_back(&graphic_field_preview_2);
	graphic_fields.push_back(&graphic_field_preview_3);
	graphic_fields.push_back(&graphic_field_preview_4);
	graphic_fields.push_back(&graphic_field_preview_5);
	graphic_fields.push_back(&graphic_field_preview_6);
	graphic_fields.push_back(&graphic_field_preview_7);
	graphic_fields.push_back(&graphic_field_preview_8);

	button_pagination_select_problem_screen_left = make_unique<L_TextButton>(loc->GetW("pagination left"), font_main, (int)(80 * scale_y), color_normal, color_focused, 800.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y, true);
	button_pagination_select_problem_screen_right = make_unique<L_TextButton>(loc->GetW("pagination right"), font_main, (int)(80 * scale_y), color_normal, color_focused, 1200.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y, true);
	rect_pagination_select_problem_screen.setPosition(655.0f * scale_x, 675.0f * scale_y);
	rect_pagination_select_problem_screen.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_pagination_select_problem_screen.setCharacterSize((int)(48 * scale_y));
	text_pagination_select_problem_screen.setFillColor(color_normal);
	bnu::place_text_in_rect(rect_pagination_select_problem_screen, text_pagination_select_problem_screen);

	Resize();
}

void L_BlockBadukTop::Render() {
	if (state == baduktop_state::MainScreen) {
		window->draw(sprite_background_main_screen);
		window->draw(text_baduktop);
		if (button_level_1->active) {
			window->draw(button_level_1->text_main);
		}
		if (button_level_2->active) {
			window->draw(button_level_2->text_main);
		}
		if (button_level_3->active) {
			window->draw(button_level_3->text_main);
		}
		if (button_level_4->active) {
			window->draw(button_level_4->text_main);
		}
		window->draw(button_collection_1->text_main);
		window->draw(button_collection_2->text_main);
		window->draw(button_collection_3->text_main);
		window->draw(button_collection_4->text_main);
		window->draw(button_collection_5->text_main);
		window->draw(button_pagination_main_screen_left->text_main);
		window->draw(button_pagination_main_screen_right->text_main);
		window->draw(text_pagination_main_screen);
		window->draw(button_back->text_main);
	}
	if (state == baduktop_state::SelectProblem) {
		window->draw(sprite_background);
		window->draw(text_baduktop);
		for (int i = 0; i < previews_on_page; i++) {
			if (i < sprite_preview_backgrounds.size()) {
				window->draw(sprite_preview_backgrounds[i]);
			}
		}
		for (L_BadukGraphicField* current_field : graphic_fields) {
			current_field->Render(*window);
		}
		window->draw(button_pagination_select_problem_screen_left->text_main);
		window->draw(button_pagination_select_problem_screen_right->text_main);
		window->draw(text_pagination_select_problem_screen);
		window->draw(button_back->text_main);
	}
	if (state == baduktop_state::Solving) {
		window->draw(sprite_background);
		window->draw(text_baduktop);
		window->draw(sprite_goproblem_background);
		main_field.Render(*window);
		if (solving_state == problem_state::WatchingCorrectSolution || solving_state == problem_state::WatchingWrongSolution) {
			window->draw(text_result_message);
		}
		window->draw(button_back->text_main);
		window->draw(button_solving_left->text_main);
		window->draw(button_solving_right->text_main);
	}
}

void L_BlockBadukTop::Resize() {
	UpdateScale();
	sprite_background.setPosition(212.0f * scale_x, 68.0f * scale_y);
	sprite_background.setSize(sf::Vector2f(1496.0f * scale_x, 745.0f * scale_y));

	sprite_background_main_screen.setPosition(212.0f * scale_x, 68.0f * scale_y);
	sprite_background_main_screen.setSize(sf::Vector2f(1496.0f * scale_x, 745.0f * scale_y));

	button_back->Resize((int)(48 * scale_y), 330.0f * scale_x, 135.0f * scale_y, 170.0f * scale_x, 70.0f * scale_y);

	button_level_1->Resize((int)(48 * scale_y), 480.0f * scale_x, 250.0f * scale_y, 320.0f * scale_x, 48.0f * scale_y);
	button_level_2->Resize((int)(48 * scale_y), 480.0f * scale_x, 300.0f * scale_y, 320.0f * scale_x, 48.0f * scale_y);
	button_level_3->Resize((int)(48 * scale_y), 480.0f * scale_x, 350.0f * scale_y, 320.0f * scale_x, 48.0f * scale_y);
	button_level_4->Resize((int)(48 * scale_y), 480.0f * scale_x, 450.0f * scale_y, 320.0f * scale_x, 48.0f * scale_y);

	button_collection_1->Resize((int)(48 * scale_y), 730.0f * scale_x, 250.0f * scale_y, 600.0f * scale_x, 48.0f * scale_y);
	button_collection_2->Resize((int)(48 * scale_y), 730.0f * scale_x, 300.0f * scale_y, 600.0f * scale_x, 48.0f * scale_y);
	button_collection_3->Resize((int)(48 * scale_y), 730.0f * scale_x, 350.0f * scale_y, 600.0f * scale_x, 48.0f * scale_y);
	button_collection_4->Resize((int)(48 * scale_y), 730.0f * scale_x, 400.0f * scale_y, 600.0f * scale_x, 48.0f * scale_y);
	button_collection_5->Resize((int)(48 * scale_y), 730.0f * scale_x, 450.0f * scale_y, 600.0f * scale_x, 48.0f * scale_y);

	rect_pagination_main_screen.setPosition(780.0f * scale_x, 675.0f * scale_y);
	rect_pagination_main_screen.setSize(sf::Vector2f(750.0f * scale_x, 70.0f * scale_y));
	text_pagination_main_screen.setCharacterSize((int)(48 * scale_y));
	bnu::place_text_in_rect(rect_pagination_main_screen, text_pagination_main_screen);

	text_baduktop.setCharacterSize((int)(44 * scale_y));
	text_baduktop.setPosition(1420.0f * scale_x, 140.0f * scale_y);
	text_baduktop.setString(L"BadukTop");

	button_pagination_main_screen_left->Resize((int)(48 * scale_y), 800.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y);
	button_pagination_main_screen_right->Resize((int)(48 * scale_y), 1200.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y);

	button_pagination_select_problem_screen_left->Resize((int)(48 * scale_y), 600.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y);
	button_pagination_select_problem_screen_right->Resize((int)(48 * scale_y), 1000.0f * scale_x, 675.0f * scale_y, 300.0f * scale_x, 70.0f * scale_y);

	rect_pagination_select_problem_screen.setPosition(655.0f * scale_x, 675.0f * scale_y);
	rect_pagination_select_problem_screen.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_pagination_select_problem_screen.setCharacterSize((int)(80 * scale_y));
	text_pagination_select_problem_screen.setFillColor(color_normal);
	bnu::place_text_in_rect(rect_pagination_select_problem_screen, text_pagination_select_problem_screen);

	float preview_texture_width = 703.0f;
	float preview_texture_height = 431.0f;
	float sprite_goproblem_pos_x = 600.0f;
	float sprite_goproblem_pos_y = 255.0f;
	float scale_factor = 1.0f;
	float preview_width = 245.0f;
	float preview_height = 149.0f;
	float pos_x = 345.0f;
	float pos_y = 260.0f;
	float step_x = 320.0f;
	float step_y = 220.0f;
	float stone_pos_x = 359.0f;
	float stone_pos_y = 371.0f;
	float stone_grid_step = 24.0f;
	float stone_size = 22.0f;
	float main_field_pos_x = 643.0f;
	float main_field_pos_y = 575.0f;
	float main_grid_step = 68.8f;
	float main_stone_size = 68.0f;

	sprite_goproblem_background.setPosition(sprite_goproblem_pos_x * scale_x, sprite_goproblem_pos_y * scale_y);
	sprite_goproblem_background.setSize(sf::Vector2f(preview_texture_width * scale_factor * scale_x, preview_texture_height * scale_factor * scale_y));

	main_field.SetPosition(main_field_pos_x * scale_x, main_field_pos_y * scale_y);
	main_field.SetGridStep(main_grid_step * scale_y);
	main_field.SetStoneSize(main_stone_size * scale_y);

	sprite_preview_background_1.setPosition(pos_x * scale_x, pos_y * scale_y);
	sprite_preview_background_1.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_2.setPosition((pos_x + step_x) * scale_x, pos_y * scale_y);
	sprite_preview_background_2.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_3.setPosition((pos_x + step_x * 2) * scale_x, pos_y * scale_y);
	sprite_preview_background_3.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_4.setPosition((pos_x + step_x * 3) * scale_x, pos_y * scale_y);
	sprite_preview_background_4.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_5.setPosition(pos_x * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_5.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_6.setPosition((pos_x + step_x) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_6.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_7.setPosition((pos_x + step_x * 2) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_7.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));
	sprite_preview_background_8.setPosition((pos_x + step_x * 3) * scale_x, (pos_y + step_y) * scale_y);
	sprite_preview_background_8.setSize(sf::Vector2f(preview_width * scale_x, preview_height * scale_y));

	sprite_preview_backgrounds.clear();
	sprite_preview_backgrounds.push_back(sprite_preview_background_1);
	sprite_preview_backgrounds.push_back(sprite_preview_background_2);
	sprite_preview_backgrounds.push_back(sprite_preview_background_3);
	sprite_preview_backgrounds.push_back(sprite_preview_background_4);
	sprite_preview_backgrounds.push_back(sprite_preview_background_5);
	sprite_preview_backgrounds.push_back(sprite_preview_background_6);
	sprite_preview_backgrounds.push_back(sprite_preview_background_7);
	sprite_preview_backgrounds.push_back(sprite_preview_background_8);


	graphic_field_preview_1.SetPosition(stone_pos_x * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_1.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_1.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_2.SetPosition((stone_pos_x + step_x) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_2.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_2.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_3.SetPosition((stone_pos_x + step_x * 2) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_3.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_3.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_4.SetPosition((stone_pos_x + step_x * 3) * scale_x, stone_pos_y * scale_y);
	graphic_field_preview_4.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_4.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_5.SetPosition(stone_pos_x * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_5.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_5.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_6.SetPosition((stone_pos_x + step_x) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_6.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_6.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_7.SetPosition((stone_pos_x + step_x * 2) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_7.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_7.SetStoneSize(stone_size * scale_y);
	graphic_field_preview_8.SetPosition((stone_pos_x + step_x * 3) * scale_x, (stone_pos_y + step_y) * scale_y);
	graphic_field_preview_8.SetGridStep(stone_grid_step * scale_y);
	graphic_field_preview_8.SetStoneSize(stone_size * scale_y);

	graphic_fields.clear();
	graphic_fields.push_back(&graphic_field_preview_1);
	graphic_fields.push_back(&graphic_field_preview_2);
	graphic_fields.push_back(&graphic_field_preview_3);
	graphic_fields.push_back(&graphic_field_preview_4);
	graphic_fields.push_back(&graphic_field_preview_5);
	graphic_fields.push_back(&graphic_field_preview_6);
	graphic_fields.push_back(&graphic_field_preview_7);
	graphic_fields.push_back(&graphic_field_preview_8);

	rect_result_message.setPosition(500.0f * scale_x, 132.0f * scale_y);
	rect_result_message.setSize(sf::Vector2f(900.0f * scale_x, 70.0f * scale_y));
	text_result_message.setCharacterSize((int)(48 * scale_y));
	bnu::place_text_in_rect(rect_result_message, text_result_message);
}

void L_BlockBadukTop::Update() {
	if (state == baduktop_state::Solving) {
		if (solving_state == problem_state::WatchingCorrectSolution) {
			float elapsed_time = solving_clock.getElapsedTime().asSeconds();
			if (elapsed_time > watching_correct_result_delay) {
				ResetProblem();
			}
		}
		if (solving_state == problem_state::WatchingWrongSolution) {
			float elapsed_time = solving_clock.getElapsedTime().asSeconds();
			if (elapsed_time > watching_wrong_result_delay) {
				ResetProblem();
			}
		}
		if (solving_state == problem_state::WaitingForAnswer) {
			float elapsed_time = solving_clock.getElapsedTime().asSeconds();
			if (elapsed_time > opponent_answer_delay) {
				MakeAnswer();
			}
		}
	}
}

void L_BlockBadukTop::MouseMove(float mouse_x, float mouse_y) {
	if (state == baduktop_state::MainScreen) {
		button_back->MouseMove(mouse_x, mouse_y);
		button_level_1->MouseMove(mouse_x, mouse_y);
		button_level_2->MouseMove(mouse_x, mouse_y);
		button_level_3->MouseMove(mouse_x, mouse_y);
		button_level_4->MouseMove(mouse_x, mouse_y);
		button_collection_1->MouseMove(mouse_x, mouse_y);
		button_collection_2->MouseMove(mouse_x, mouse_y);
		button_collection_3->MouseMove(mouse_x, mouse_y);
		button_collection_4->MouseMove(mouse_x, mouse_y);
		button_collection_5->MouseMove(mouse_x, mouse_y);
		button_pagination_main_screen_left->MouseMove(mouse_x, mouse_y);
		button_pagination_main_screen_right->MouseMove(mouse_x, mouse_y);
	}
	if (state == baduktop_state::SelectProblem) {
		button_back->MouseMove(mouse_x, mouse_y);
		button_pagination_select_problem_screen_left->MouseMove(mouse_x, mouse_y);
		button_pagination_select_problem_screen_right->MouseMove(mouse_x, mouse_y);
	}
	if (state == baduktop_state::Solving) {
		button_back->MouseMove(mouse_x, mouse_y);
		button_solving_left->MouseMove(mouse_x, mouse_y);
		button_solving_right->MouseMove(mouse_x, mouse_y);
	}
}

void L_BlockBadukTop::UpdateLanguage() {
	
}

void L_BlockBadukTop::MouseDown(sf::Event p_event, game_state clicked_state) {
	if (clicked_state == game_state::Smartphone) {
		return;
	}
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
	if (p_event.mouseButton.button == sf::Mouse::Left) {
		if (!bnu::is_point_in_rect((float)mouse_position.x, (float)mouse_position.y, sprite_background)) {
			prevent_other_actions = true;
			if (action_clicked_outside != nullptr) {
				action_clicked_outside();
				return;
			}
		}
		if (state == baduktop_state::MainScreen) {
			if (button_back->focused) {
				GoBack();
				return;
			}
			if (button_collection_1->focused) {
				if (current_collections.size() > 0) {
					GoToCollection(current_collections[0]);
					return;
				}
			}
			if (button_collection_2->focused) {
				if (current_collections.size() > 1) {
					GoToCollection(current_collections[1]);
					return;
				}
			}
			if (button_collection_3->focused) {
				if (current_collections.size() > 2) {
					GoToCollection(current_collections[2]);
					return;
				}
			}
			if (button_collection_4->focused) {
				if (current_collections.size() > 3) {
					GoToCollection(current_collections[3]);
					return;
				}
			}
			if (button_collection_5->focused) {
				if (current_collections.size() > 4) {
					GoToCollection(current_collections[4]);
					return;
				}
			}
			if (button_level_1->focused) {
				collections_level = 1;
				pagination_main_screen.SetCurrentPage(1);
				UpdateMainScreen();
				return;
			}
			if (button_level_2->focused) {
				collections_level = 2;
				pagination_main_screen.SetCurrentPage(1);
				UpdateMainScreen();
				return;
			}
			if (button_level_3->focused) {
				collections_level = 3;
				pagination_main_screen.SetCurrentPage(1);
				UpdateMainScreen();
				return;
			}
			if (button_level_4->focused) {
				collections_level = 4;
				pagination_main_screen.SetCurrentPage(1);
				UpdateMainScreen();
				return;
			}
			if (button_pagination_main_screen_left->focused) {
				GoPreviousCollections();
			}
			if (button_pagination_main_screen_right->focused) {
				GoNextCollections();
			}
		}
		if (state == baduktop_state::SelectProblem) {
			if (button_back->focused) {
				GoBack();
				return;
			}
			if (button_pagination_select_problem_screen_left->focused) {
				GoPreviousPreviews();
			}
			if (button_pagination_select_problem_screen_right->focused) {
				GoNextPreviews();
			}
			if (previews_on_page > previews_per_page) {
				previews_on_page = previews_per_page;
			}
			for (int i = 0; i < previews_on_page; i++) {
				if (i > sprite_preview_backgrounds.size()) {
					return;
				}
				if (bnu::is_point_in_rect((float)mouse_position.x, (float)mouse_position.y, sprite_preview_backgrounds[i])) {
					L_GoProblem problem_to_prepare = cur_collection.GetGoProblem(i);
					if (problem_to_prepare.is_empty()) {
						return;
					}
					PrepareGoProblem(cur_collection.GetGoProblem(i));
					cur_problem_index = i;
					if (!cur_problem.is_empty()) {
						SetState(baduktop_state::Solving);
					}
					return;
				}
			}
		}
		if (state == baduktop_state::Solving) {
			if (button_back->focused) {
				GoBack();
				return;
			}
			if (button_solving_left->focused) {
				GoPreviousProblem();
				return;
			}
			if (button_solving_right->focused) {
				GoNextProblem();
				return;
			}

			BadukCoords point_under_mouse;
			int point_x = -1, point_y = -1;
			main_field.GetCoordsUnderPoints((float)mouse_position.x, (float)mouse_position.y, point_under_mouse);
			if (solving_state == problem_state::MakingMove) {
				if (main_field.is_ValidCoords(point_under_mouse)) {
					if (main_field.MakeMove(StoneColor::Black, point_under_mouse)) {
						std::string string_coords;
						if (bnu::coords_to_string(point_under_mouse, string_coords)) {
							if (cur_moves.length() > 0) {
								cur_moves += ' ';
							}
							cur_moves += string_coords;
							CheckSolution();
						}
					}
				}
			}
		}
	}
}

void L_BlockBadukTop::SetFont(sf::Font p_font_main) {
	font_main = p_font_main;
	UpdateFont();
}

void L_BlockBadukTop::SetGoProblems(L_GoProblemManager& p_goproblem_manager) {
	goproblem_manager = p_goproblem_manager;
	UpdateMainScreen();
}

void L_BlockBadukTop::UpdateFont() {

	button_level_1->SetFont(font_main);
	button_level_2->SetFont(font_main);
	button_level_3->SetFont(font_main);
	button_level_4->SetFont(font_main);

	button_collection_1->SetFont(font_main);
	button_collection_2->SetFont(font_main);
	button_collection_3->SetFont(font_main);
	button_collection_4->SetFont(font_main);
	button_collection_5->SetFont(font_main);

	button_pagination_main_screen_left->SetFont(font_main);
	button_pagination_main_screen_right->SetFont(font_main);
	text_pagination_main_screen.setFont(font_main);
	text_result_message.setFont(font_main);
	button_back->SetFont(font_main);
	button_solving_left->SetFont(font_main);
	button_solving_right->SetFont(font_main);

	button_pagination_select_problem_screen_left->SetFont(font_main);
	button_pagination_select_problem_screen_right->SetFont(font_main);
	text_pagination_select_problem_screen.setFont(font_main);

	text_baduktop.setFont(font_main);

}

void L_BlockBadukTop::UpdateSelectProblemScreen() {
	int num_previews = (int)ceil((float)cur_collection.goproblems.size() / (float)previews_per_page);
	if (num_previews < 1) {
		num_previews = 1;
	}
	pagination_selectproblem_screen.SetNumPages(num_previews);

	text_pagination_select_problem_screen.setString(std::to_wstring(pagination_selectproblem_screen.CurPage()) + L" / " + std::to_wstring(pagination_selectproblem_screen.NumPages()));
	rect_pagination_select_problem_screen.setPosition(655.0f * scale_x, 675.0f * scale_y);
	rect_pagination_select_problem_screen.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_pagination_select_problem_screen.setCharacterSize((int)(48 * scale_y));
	text_pagination_select_problem_screen.setFillColor(color_normal);
	bnu::place_text_in_rect(rect_pagination_select_problem_screen, text_pagination_select_problem_screen);

	for (L_BadukGraphicField* cur_field : graphic_fields) {
		cur_field->ClearStones();
	}
	int start = (pagination_selectproblem_screen.CurPage() - 1) * previews_per_page;
	for (int i = start; i < start + previews_per_page; i++) {
		int field_id = i - start;
		if (i < cur_collection.goproblems.size()) {
			SetPreview(field_id, cur_collection.goproblems[i]);
		}
	}
	previews_on_page = (int)cur_collection.goproblems.size();
	if (pagination_selectproblem_screen.isAtLastPage()) {
		while (previews_on_page > previews_per_page) {
			previews_on_page -= previews_per_page;
		}
	}
	if (previews_on_page > previews_per_page) {
		previews_on_page = previews_per_page;
	}
}

void L_BlockBadukTop::UpdateMainScreen() {
	button_level_1->SetActive(goproblem_manager.HaveCollectionsWithLevel(1));
	button_level_2->SetActive(goproblem_manager.HaveCollectionsWithLevel(2));
	button_level_3->SetActive(goproblem_manager.HaveCollectionsWithLevel(3));
	button_level_4->SetActive(goproblem_manager.HaveCollectionsWithLevel(4));

	int num_collection = goproblem_manager.GetNumCollectionOfLevel(collections_level);
	collections_page = (int)ceil((float)num_collection / (float)collections_per_page);
	if (collections_page < 1) {
		collections_page = 1;
	}
	pagination_main_screen.SetNumPages(collections_page);

	current_collections = goproblem_manager.GetCollectionNames(collections_level, collections_per_page, pagination_main_screen.CurPage());
	button_collection_1->SetText(std::wstring());
	button_collection_2->SetText(std::wstring());
	button_collection_3->SetText(std::wstring());
	button_collection_4->SetText(std::wstring());
	button_collection_5->SetText(std::wstring());

	text_pagination_main_screen.setString(std::to_wstring(pagination_main_screen.CurPage()) + L" / " + std::to_wstring(pagination_main_screen.NumPages()));
	rect_pagination_main_screen.setPosition(855.0f * scale_x, 675.0f * scale_y);
	rect_pagination_main_screen.setSize(sf::Vector2f(600.0f * scale_x, 70.0f * scale_y));
	text_pagination_main_screen.setCharacterSize((int)(48 * scale_y));
	text_pagination_main_screen.setFillColor(color_normal);
	bnu::place_text_in_rect(rect_pagination_main_screen, text_pagination_main_screen);

	if (current_collections.size() > 0) {
		wstring name_1 = loc->GetW("collection " + current_collections[0]);
		if (name_1.length() > 0) {
			button_collection_1->SetText(name_1);
		}
		else {
			button_collection_1->SetText(bnu::convert_to_wstring(current_collections[0].c_str()));
		}
	}
	if (current_collections.size() > 1) {
		wstring name_2 = loc->GetW("collection " + current_collections[1]);
		if (name_2.length() > 0) {
			button_collection_2->SetText(name_2);
		}
		else {
			button_collection_2->SetText(bnu::convert_to_wstring(current_collections[1].c_str()));
		}
	}
	if (current_collections.size() > 2) {
		wstring name_3 = loc->GetW("collection " + current_collections[2]);
		if (name_3.length() > 0) {
			button_collection_3->SetText(name_3);
		}
		else {
			button_collection_3->SetText(bnu::convert_to_wstring(current_collections[2].c_str()));
		}
	}
	if (current_collections.size() > 3) {
		wstring name_4 = loc->GetW("collection " + current_collections[3]);
		if (name_4.length() > 0) {
			button_collection_4->SetText(name_4);
		}
		else {
			button_collection_4->SetText(bnu::convert_to_wstring(current_collections[3].c_str()));
		}
	}
	if (current_collections.size() > 4) {
		wstring name_5 = loc->GetW("collection " + current_collections[4]);
		if (name_5.length() > 0) {
			button_collection_5->SetText(name_5);
		}
		else {
			button_collection_5->SetText(bnu::convert_to_wstring(current_collections[4].c_str()));
		}
	}
}

void L_BlockBadukTop::SetPreview(int index, L_GoProblem goproblem) {
	graphic_fields[index]->InitPosition(goproblem);
}

void L_BlockBadukTop::GoNextPreviews() {
	pagination_selectproblem_screen.GoToNext();
	UpdateSelectProblemScreen();
}

void L_BlockBadukTop::GoPreviousPreviews() {
	pagination_selectproblem_screen.GoToPrevious();
	UpdateSelectProblemScreen();
}

void L_BlockBadukTop::UnfocusButtons() const {
	button_collection_1->focused = false;
	button_collection_2->focused = false;
	button_collection_3->focused = false;
	button_collection_4->focused = false;
	button_collection_5->focused = false;
	button_level_1->focused = false;
	button_level_2->focused = false;
	button_level_3->focused = false;
	button_level_4->focused = false;
}

void L_BlockBadukTop::PrepareGoProblem(L_GoProblem goproblem) {
	cur_problem = goproblem;
	ResetProblem();
}

void L_BlockBadukTop::CheckSolution() {
	goproblem_result result = cur_problem.CheckResult(cur_moves);
	if (result == goproblem_result::GoodMove) {
		SetSolvingState(problem_state::WaitingForAnswer);
	}
	if (result == goproblem_result::Mistake) {
		SetSolvingState(problem_state::WatchingWrongSolution);
	}
	if (result == goproblem_result::Solved) {
		SetSolvingState(problem_state::WatchingCorrectSolution);
	}
}

void L_BlockBadukTop::SetSolvingState(problem_state p_state) {
	solving_state = p_state;
	if (solving_state == problem_state::WatchingCorrectSolution) {
		text_result_message.setString(loc->GetW("sm bt correct"));
		solving_clock.restart();
		return;
	}
	if (solving_state == problem_state::WatchingWrongSolution) {
		text_result_message.setString(loc->GetW("sm bt wrong"));
		solving_clock.restart();
		return;
	}
	if (solving_state == problem_state::WaitingForAnswer) {
		solving_clock.restart();
		return;
	}
}

void L_BlockBadukTop::ResetProblem() {
	cur_moves = std::string();
	SetSolvingState(problem_state::MakingMove);
	main_field.InitPosition(cur_problem);
}

void L_BlockBadukTop::MakeAnswer() {
	vector<BadukCoords> possible_moves;
	if (cur_problem.GetPossibleAnswer(cur_moves, possible_moves)) {
		int random_index = rand() % possible_moves.size();
		BadukCoords answer = possible_moves[random_index];
		if (main_field.is_ValidCoords(answer)) {
			if (main_field.MakeMove(StoneColor::White, answer)) {
				std::string string_coords;
				if (bnu::coords_to_string(answer, string_coords)) {
					if (cur_moves.length() > 0) {
						cur_moves += ' ';
					}
					cur_moves += string_coords;
					SetSolvingState(problem_state::MakingMove);
				}
			}
		}
	}
}

void L_BlockBadukTop::GoNextProblem() {
	L_GoProblem problem_to_prepare = cur_collection.GetGoProblem(cur_problem_index + 1);
	if (!problem_to_prepare.is_empty()) {
		cur_problem_index++;
		PrepareGoProblem(problem_to_prepare);
	}
}

void L_BlockBadukTop::GoPreviousProblem() {
	L_GoProblem problem_to_prepare = cur_collection.GetGoProblem(cur_problem_index - 1);
	if (!problem_to_prepare.is_empty()) {
		cur_problem_index--;
		PrepareGoProblem(problem_to_prepare);
	}
}

void L_BlockBadukTop::GoNextCollections() {
	pagination_main_screen.GoToNext();
	UpdateMainScreen();
}

void L_BlockBadukTop::GoPreviousCollections() {
	pagination_main_screen.GoToPrevious();
	UpdateMainScreen();
}

void L_BlockBadukTop::SetState(baduktop_state p_state) {
	state = p_state;
	if (state == baduktop_state::MainScreen) {
		UnfocusButtons();
		UpdateMainScreen();
		return;
	}
	if (state == baduktop_state::SelectProblem) {
		UnfocusButtons();
		UpdateSelectProblemScreen();
		return;
	}
	if (state == baduktop_state::Solving) {
		cur_moves = std::string();
		solving_state = problem_state::MakingMove;
	}
}

void L_BlockBadukTop::GoBack() {
	if (state == baduktop_state::MainScreen) {
		if (action_close != nullptr) {
			action_close();
		}
	}
	if (state == baduktop_state::SelectProblem) {
		SetState(baduktop_state::MainScreen);
		return;
	}
	if (state == baduktop_state::Solving) {
		SetState(baduktop_state::SelectProblem);
		return;
	}
}

void L_BlockBadukTop::GoToCollection(std::string p_collection_name) {
	cur_collection = goproblem_manager.GetCollection(p_collection_name);
	if (cur_collection.name.length() > 0) {
		cur_collection_name = p_collection_name;
		UpdateSelectProblemScreen();
		SetState(baduktop_state::SelectProblem);
	}
}
