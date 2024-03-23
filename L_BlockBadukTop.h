#pragma once
#pragma once
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "game_structs.h"
#include "L_Block.h"
#include "L_TextButton.h"
#include "L_ImageButton.h"
#include "L_BadukGraphicField.h"
#include "L_GoProblemManager.h"
#include "L_Pagination.h"

class L_BlockBadukTop : public L_Block{
public:
	std::function<void()> action_clicked_outside;
	std::function<void()> action_close;

	std::vector<L_BadukGraphicField*> graphic_fields;
	L_BadukGraphicField graphic_field_preview_1;
	L_BadukGraphicField graphic_field_preview_2;
	L_BadukGraphicField graphic_field_preview_3;
	L_BadukGraphicField graphic_field_preview_4;
	L_BadukGraphicField graphic_field_preview_5;
	L_BadukGraphicField graphic_field_preview_6;
	L_BadukGraphicField graphic_field_preview_7;
	L_BadukGraphicField graphic_field_preview_8;
	L_BadukGraphicField main_field;

	baduktop_state state;
	problem_state solving_state;
	int collections_level = 1;
	int collections_page = 1;
	std::vector<std::string> current_collections;

	std::unique_ptr<L_TextButton> button_back;

	std::unique_ptr<L_TextButton> button_level_1;
	std::unique_ptr<L_TextButton> button_level_2;
	std::unique_ptr<L_TextButton> button_level_3;
	std::unique_ptr<L_TextButton> button_level_4;

	std::unique_ptr<L_TextButton> button_collection_1;
	std::unique_ptr<L_TextButton> button_collection_2;
	std::unique_ptr<L_TextButton> button_collection_3;
	std::unique_ptr<L_TextButton> button_collection_4;
	std::unique_ptr<L_TextButton> button_collection_5;

	std::unique_ptr<L_TextButton> button_solving_left;
	std::unique_ptr<L_TextButton> button_solving_right;

	std::unique_ptr<L_TextButton> button_pagination_main_screen_left;
	std::unique_ptr<L_TextButton> button_pagination_main_screen_right;
	sf::RectangleShape rect_pagination_main_screen;
	sf::Text text_pagination_main_screen;
	sf::Text text_baduktop;

	std::unique_ptr<L_TextButton> button_pagination_select_problem_screen_left;
	std::unique_ptr<L_TextButton> button_pagination_select_problem_screen_right;
	sf::RectangleShape rect_pagination_select_problem_screen;
	sf::Text text_pagination_select_problem_screen;

	std::string cur_moves;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Resize() override;
	void Update() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void UpdateLanguage() override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font_main);
	void SetGoProblems(L_GoProblemManager& p_goproblems);
	void GoToCollection(std::string p_collection_name);
	void SetState(baduktop_state p_state);
	void GoBack();
private:
	L_GoProblemManager goproblem_manager;
	std::string cur_collection_name;
	L_GoProblemCollection cur_collection;
	L_GoProblem cur_problem;
	int cur_problem_index = 0;

	int previews_on_page = 8;
	int previews_per_page = 8;
	L_Pagination pagination_selectproblem_screen;

	sf::Clock solving_clock;
	float watching_correct_result_delay = 1.5f;
	float watching_wrong_result_delay = 1.5f;
	float opponent_answer_delay = 1.0f;

	int collections_per_page = 5;
	L_Pagination pagination_main_screen;

	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::RectangleShape sprite_background_main_screen;
	sf::Texture tex_background_main_screen;

	sf::RectangleShape rect_result_message;
	sf::Text text_result_message;

	sf::Texture tex_preview_problem_background;
	std::vector<sf::RectangleShape> sprite_preview_backgrounds;
	sf::RectangleShape sprite_preview_background_1;
	sf::RectangleShape sprite_preview_background_2;
	sf::RectangleShape sprite_preview_background_3;
	sf::RectangleShape sprite_preview_background_4;
	sf::RectangleShape sprite_preview_background_5;
	sf::RectangleShape sprite_preview_background_6;
	sf::RectangleShape sprite_preview_background_7;
	sf::RectangleShape sprite_preview_background_8;

	sf::RectangleShape sprite_goproblem_background;

	sf::Color color_normal;
	sf::Color color_focused;

	void UpdateFont();
	void UnfocusButtons() const;

	// Main screen
	void UpdateMainScreen();
	void GoNextCollections();
	void GoPreviousCollections();

	// Select problem screen
	void UpdateSelectProblemScreen();
	void SetPreview(int index, L_GoProblem goproblem);
	void GoNextPreviews();
	void GoPreviousPreviews();

	// Solving screen
	void GoNextProblem();
	void GoPreviousProblem();
	void CheckSolution();
	void SetSolvingState(problem_state p_state);
	void PrepareGoProblem(L_GoProblem goproblem);
	void ResetProblem();
	void MakeAnswer();
};

