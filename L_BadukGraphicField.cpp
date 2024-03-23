#include "L_BadukGraphicField.h"
using namespace std;

void L_BadukGraphicField::SetTextures(string p_tex_black_stone_filename, string p_tex_white_stone_filename) {
	SetBlackStoneTexture(p_tex_black_stone_filename);
	SetWhiteStoneTexture(p_tex_white_stone_filename);
}

void L_BadukGraphicField::SetBlackStoneTexture(std::string p_tex_black_stone_filename) {
	if (!tex_black_stone.loadFromFile(p_tex_black_stone_filename)) {
		cout << "Error: Failed to load BadukGraphicField black stone texture - " << p_tex_black_stone_filename << "\n";
	}
	tex_black_stone.setSmooth(true);
}

void L_BadukGraphicField::SetWhiteStoneTexture(std::string p_tex_white_stone_filename) {
	if (!tex_white_stone.loadFromFile(p_tex_white_stone_filename)) {
		cout << "Error: Failed to load BadukGraphicField white stone texture - " << p_tex_white_stone_filename << "\n";
	}
	tex_white_stone.setSmooth(true);
}

void L_BadukGraphicField::SetPosition(float p_pos_x, float p_pos_y) {
	pos_x = p_pos_x;
	pos_y = p_pos_y;
	Resize();
}

void L_BadukGraphicField::SetGridStep(float p_grid_step) {
	grid_step = p_grid_step;
	Resize();
}

void L_BadukGraphicField::SetStoneSize(float p_stone_size) {
	stone_size = p_stone_size;
}

void L_BadukGraphicField::Render(sf::RenderWindow& window) {
	for (GraphicStone current_stone : stones) {
		window.draw(current_stone.sprite_main);
	}
}

void L_BadukGraphicField::Resize() {
	UpdateStones();
}

void L_BadukGraphicField::ClearStones() {
	field.stones.clear();
	UpdateStones();
}

void L_BadukGraphicField::PlaceStone(StoneColor stone_color, BadukCoords coords) {
	field.PlaceStone(stone_color, coords);
	UpdateStones();
}

bool L_BadukGraphicField::MakeMove(StoneColor color, BadukCoords coords) {
	if (field.MakeMove(color, coords)) {
		UpdateStones();
		return true;
	}
	return false;
}

void L_BadukGraphicField::InitPosition(L_GoProblem goproblem) {
	field.stones.clear();
	vector<string> black_coords = bnu::split_string(goproblem.black_stones, ' ');
	vector<string> white_coords = bnu::split_string(goproblem.white_stones, ' ');
	for (string current_coords : black_coords) {
		int coord_x, coord_y;
		bnu::extract_coords(current_coords, coord_x, coord_y);
		if (coord_x != -1 && coord_y != -1) {
			PlaceStone(StoneColor::Black, BadukCoords{ coord_x, coord_y });
		}
	}
	for (string current_coords : white_coords) {
		int coord_x, coord_y;
		bnu::extract_coords(current_coords, coord_x, coord_y);
		if (coord_x != -1 && coord_y != -1) {
			PlaceStone(StoneColor::White, BadukCoords{ coord_x, coord_y });
		}
	}
	UpdateStones();
}

void L_BadukGraphicField::GetCoordsUnderPoints(float point_x, float point_y, BadukCoords& result) {
	result.x = (int)round(((point_x - pos_x) / grid_step));
	result.y = (int)round(((pos_y - point_y) / grid_step)) + 1;
	
}

void L_BadukGraphicField::SetSize(int p_width, int p_height) {
	field.SetSize(p_width, p_height);
}

bool L_BadukGraphicField::is_ValidCoords(BadukCoords coords) {
	return field.is_ValidCoords(coords);
}

void L_BadukGraphicField::UpdateStonePosition(GraphicStone& stone_to_update) {
	stone_to_update.sprite_main.setPosition(pos_x + grid_step * stone_to_update.x - stone_size / 2, pos_y - grid_step * stone_to_update.y + stone_size / 2 );
	stone_to_update.sprite_main.setSize(sf::Vector2f(grid_step, grid_step));
}

void L_BadukGraphicField::UpdateStones() {
	stones.clear();
	for (BadukStone cur_stone : field.stones) {
		CreateGraphicStone(cur_stone);
	}
}

void L_BadukGraphicField::CreateGraphicStone(BadukStone source_stone) {
	GraphicStone stone_to_insert;
	stone_to_insert.x = source_stone.coords.x;
	stone_to_insert.y = source_stone.coords.y;
	stone_to_insert.color = source_stone.color;
	if (stone_to_insert.color == StoneColor::Black) {
		stone_to_insert.sprite_main.setTexture(&tex_black_stone);
	}
	if (stone_to_insert.color == StoneColor::White) {
		stone_to_insert.sprite_main.setTexture(&tex_white_stone);
	}
	UpdateStonePosition(stone_to_insert);
	stones.push_back(stone_to_insert);
}
