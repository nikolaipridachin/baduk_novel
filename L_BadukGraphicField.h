#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "bnu.h"
#include "L_GoProblem.h"
#include "L_BadukField.h"

struct GraphicStone {
	StoneColor color = StoneColor::Undefined;
	int x = -1, y = -1;
	sf::RectangleShape sprite_main;
};

class L_BadukGraphicField {
public:
	void SetTextures(std::string p_tex_black_stone_filename, std::string p_tex_white_stone_filename);
	void SetBlackStoneTexture(std::string p_tex_black_stone_filename);
	void SetWhiteStoneTexture(std::string p_tex_white_stone_filename);
	void SetPosition(float p_pos_x, float p_pos_y);
	void SetGridStep(float p_grid_step);
	void SetStoneSize(float p_stone_size);

	void Render(sf::RenderWindow& window);
	void Resize();
	void ClearStones();
	void PlaceStone(StoneColor stone_color, BadukCoords coords);
	bool MakeMove(StoneColor color, BadukCoords coords);
	void InitPosition(L_GoProblem goproblem);
	void GetCoordsUnderPoints(float point_x, float point_y, BadukCoords &result);
	void SetSize(int p_width, int p_height);
	bool is_ValidCoords(BadukCoords coords);
private:
	L_BadukField field;

	sf::Texture tex_black_stone;
	sf::Texture tex_white_stone;
	std::vector<GraphicStone> stones;

	float pos_x = 0.0f, pos_y = 0.0f;
	float grid_step = 20.0f;
	float stone_size = 18.0f;

	void UpdateStonePosition(GraphicStone& stone_to_update);
	void UpdateStones();
	void CreateGraphicStone(BadukStone source_stone);
};

