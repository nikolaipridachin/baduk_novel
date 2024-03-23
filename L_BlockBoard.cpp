#include "L_BlockBoard.h"

void L_BlockBoard::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	cur_problem_state = problem_state::NotInProblem;

	graphic_field.SetSize(19, 19);
	graphic_field.SetTextures("Content/ui/smartphone/stone_black.png", "Content/ui/smartphone/stone_white.png");

	//Init background
	if (!tex_background.loadFromFile("Content/ui/table/table_dark_wood.jpg")) {
		std::cout << "Error: Failed to load table texture\n";
	}
	tex_background.setSmooth(true);
	sprite_background.setTexture(&tex_background);

	// Init board
	if (!tex_board.loadFromFile("Content/ui/board/board_dark_wood.png")) {
		std::cout << "Error: Failed to load board texture\n";
	}
	tex_board.setSmooth(true);
	sprite_board.setTexture(&tex_board);

	// Init grid
	if (!tex_grid.loadFromFile("Content/ui/grid/grid_19_19.png")) {
		std::cout << "Error: Failed to load board texture\n";
	}
	tex_grid.setSmooth(true);
	sprite_grid.setTexture(&tex_grid);

	// Init bowls
	if (!tex_bowl_left.loadFromFile("Content/ui/bowl/bowl_left_white.png")) {
		std::cout << "Error: Failed to load bowl left texture\n";
	}
	tex_bowl_left.setSmooth(true);
	sprite_bowl_left.setTexture(&tex_bowl_left);
	if (!tex_bowl_right.loadFromFile("Content/ui/bowl/bowl_right_black.png")) {
		std::cout << "Error: Failed to load bowl right dark texture\n";
	}
	tex_bowl_right.setSmooth(true);
	sprite_bowl_right.setTexture(&tex_bowl_right);

	//Init active stone
	if (!tex_active_stone.loadFromFile("Content/ui/smartphone/stone_black.png")) {
		std::cout << "Error: Failed to load active stone texture\n";
	}
	tex_active_stone.setSmooth(true);
	sprite_active_stone.setTexture(&tex_active_stone);

	Resize();
}

void L_BlockBoard::Render() {
	window->draw(sprite_background);
	window->draw(sprite_board);
	window->draw(sprite_grid);
	window->draw(sprite_bowl_left);
	window->draw(sprite_bowl_right);
	graphic_field.Render(*window);
	if (is_stone_in_hand) {
		window->draw(sprite_active_stone);
	}
}

void L_BlockBoard::Update() {
	if (cur_problem_state == problem_state::WatchingCorrectSolution) {
		float elapsed_time = solving_clock.getElapsedTime().asSeconds();
		if (elapsed_time > watching_correct_result_delay) {
			CompleteProblem();
		}
	}
	if (cur_problem_state == problem_state::WatchingWrongSolution) {
		float elapsed_time = solving_clock.getElapsedTime().asSeconds();
		if (elapsed_time > watching_wrong_result_delay) {
			ResetProblem();
		}
	}
	if (cur_problem_state == problem_state::WaitingForAnswer) {
		float elapsed_time = solving_clock.getElapsedTime().asSeconds();
		if (elapsed_time > opponent_answer_delay) {
			MakeAnswer();
		}
	}

}

void L_BlockBoard::ResetProblem() {
	cur_moves = std::string();
	SetSolvingState(problem_state::MakingMove);
	graphic_field.InitPosition(cur_problem);
	if (action_say) {
		action_say(cur_problem.task);
	}
}

void L_BlockBoard::MakeAnswer() {
	std::vector<BadukCoords> possible_moves;
	if (cur_problem.GetPossibleAnswer(cur_moves, possible_moves)) {
		int random_index = rand() % possible_moves.size();
		BadukCoords answer = possible_moves[random_index];
		if (graphic_field.is_ValidCoords(answer)) {
			if (graphic_field.MakeMove(StoneColor::White, answer)) {
				if (action_place_stone) {
					action_place_stone();
				}
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

void L_BlockBoard::CompleteProblem() {
	cur_problem_state = problem_state::NotInProblem;
	cur_moves = std::string();
	action_problem_completed();
}

void L_BlockBoard::Resize() {
	UpdateScale();
	sprite_background.setPosition(0.0f, 0.0f);
	sprite_background.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	sprite_grid.setPosition(0.0f, 0.0f);
	sprite_grid.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	sprite_board.setPosition(0.0f, 0.0f);
	sprite_board.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	sprite_bowl_left.setPosition(0.0f, 0.0f);
	sprite_bowl_left.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	sprite_bowl_right.setPosition(0.0f, 0.0f);
	sprite_bowl_right.setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));

	area_bowl_black.setPosition(1500.0f * scale_x, 630.0f * scale_y);
	area_bowl_black.setSize(sf::Vector2f(200.0f * scale_x, 200.0f * scale_y));

	area_bowl_white.setPosition(225.0f * scale_x, 40.0f * scale_y);
	area_bowl_white.setSize(sf::Vector2f(200.0f * scale_x, 200.0f * scale_y));

	graphic_field.SetPosition(584.0f * scale_x, 780.0f * scale_y);
	graphic_field.SetGridStep(42.6f * scale_y);
	graphic_field.SetStoneSize(42.0f * scale_y);
	graphic_field.Resize();

	sprite_active_stone.setSize(sf::Vector2f(active_stone_size * scale_x, active_stone_size * scale_y));
}

void L_BlockBoard::SetActive(bool p_active) {
	active = p_active;
	graphic_field.ClearStones();
	graphic_field.InitPosition(cur_problem);
	if (active) {
		Resize();
	}
}

void L_BlockBoard::UpdateLanguage() {

}

void L_BlockBoard::MouseMove(float mouse_x, float mouse_y) {
	if (is_stone_in_hand) {
		sprite_active_stone.setPosition(mouse_x - active_stone_size * scale_x / 2, mouse_y - active_stone_size * scale_y / 2);
	}
}

void L_BlockBoard::MouseDown(sf::Event p_event, game_state clicked_state) {
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
	if (cur_problem_state == problem_state::MakingMove &&
		bnu::is_point_in_rect((float)mouse_position.x, (float)mouse_position.y, area_bowl_black)) {
		is_stone_in_hand = true;
		if (action_take_stone) {
			action_take_stone();
		}
	}
}

void L_BlockBoard::MouseUp(sf::Event p_event, game_state clicked_state) {
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
	if (is_stone_in_hand) {
		if (p_event.mouseButton.button == sf::Mouse::Left) {
			BadukCoords point_under_mouse;
			int point_x = -1, point_y = -1;
			graphic_field.GetCoordsUnderPoints((float)mouse_position.x, (float)mouse_position.y, point_under_mouse);
			if (cur_problem_state == problem_state::MakingMove) {
				if (graphic_field.is_ValidCoords(point_under_mouse)) {
					if (graphic_field.MakeMove(StoneColor::Black, point_under_mouse)) {
						if (action_place_stone) {
							action_place_stone();
						}
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
	is_stone_in_hand = false;
}

void L_BlockBoard::SetSolvingState(problem_state p_state) {
	cur_problem_state = p_state;
	if (cur_problem_state == problem_state::WatchingCorrectSolution) {
		solving_clock.restart();
		return;
	}
	if (cur_problem_state == problem_state::WatchingWrongSolution) {
		if (action_say) {
			action_say(cur_problem.fail_comment);
		}
		solving_clock.restart();
		return;
	}
	if (cur_problem_state == problem_state::WaitingForAnswer) {
		solving_clock.restart();
		return;
	}
}

void L_BlockBoard::CheckSolution() {
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

void L_BlockBoard::SetFont(sf::Font p_font) {

}

void L_BlockBoard::SetupGoProblem(L_GoProblem go_problem) {
	cur_problem = go_problem;
	graphic_field.InitPosition(cur_problem);
	cur_problem_state = problem_state::MakingMove;
}

bool L_BlockBoard::CanProcessNextCommand() {
	if (cur_problem_state == problem_state::NotInProblem) {
		return true;
	}
	else {
		return false;
	}
}
