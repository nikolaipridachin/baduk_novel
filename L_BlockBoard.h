#pragma once
#include "L_Block.h"
#include "L_TextButton.h"
#include "L_Localization.h"
#include "L_BadukGraphicField.h"

class L_BlockBoard : public L_Block {
private:
	sf::Font font_main;
	sf::RectangleShape sprite_background;
	sf::Texture tex_background;

	sf::RectangleShape sprite_board;
	sf::Texture tex_board;

	sf::RectangleShape sprite_bowl_left;
	sf::RectangleShape sprite_bowl_right;
	sf::Texture tex_bowl_left;
	sf::Texture tex_bowl_right;

	sf::RectangleShape sprite_grid;
	sf::Texture tex_grid;

	sf::RectangleShape area_bowl_black;
	sf::RectangleShape area_bowl_white;

	L_BadukGraphicField graphic_field;
	L_GoProblem cur_problem;

	sf::RectangleShape sprite_active_stone;
	sf::Texture tex_active_stone;

	std::string cur_moves;
	sf::Clock solving_clock;
	float watching_correct_result_delay = 0.0f;
	float watching_wrong_result_delay = 1.5f;
	float opponent_answer_delay = 1.0f;

	bool is_stone_in_hand = false;
	float active_stone_size = 42.0f;

	void CheckSolution();
	void SetSolvingState(problem_state p_state);
	void ResetProblem();
	void MakeAnswer();
	void CompleteProblem();

public:
	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Render() override;
	void Update() override;
	void Resize() override;
	void SetActive(bool p_active) override;
	void UpdateLanguage() override;
	void MouseMove(float mouse_x, float mouse_y) override;
	void MouseDown(sf::Event p_event, game_state clicked_state) override;
	void MouseUp(sf::Event p_event, game_state clicked_state) override;
	void SetFont(sf::Font p_font);
	void SetupGoProblem(L_GoProblem go_problem);
	bool CanProcessNextCommand();

	std::function<void(std::wstring)> action_say;
	std::function<void()> action_problem_completed;
	std::function<void()> action_take_stone;
	std::function<void()> action_place_stone;

	problem_state cur_problem_state;

	std::wstring GetProblemTask() { return cur_problem.task; };
};

