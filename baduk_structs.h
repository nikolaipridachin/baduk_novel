#pragma once
#include <vector>

enum StoneColor {
	Undefined, Black, White
};

struct BadukCoords {
	int x = -1;
	int y = -1;

	bool operator==(const BadukCoords& p) const {
		return x == p.x && y == p.y;
	}
	bool operator!=(const BadukCoords& p) const {
		return x != p.x || y != p.y;
	}
};

struct BadukStone {
	StoneColor color = StoneColor::Undefined;
	BadukCoords coords;

	BadukStone() {};
	BadukStone(StoneColor p_color, BadukCoords p_coords) {
		color = p_color;
		coords.x = p_coords.x;
		coords.y = p_coords.y;
	}
};

struct BadukGroup {
	StoneColor color = StoneColor::Undefined;
	int dame_count = -1;
	std::vector<BadukStone> stones;

	void AddStone(BadukStone stone) {
		if (stone.color == color) {
			stones.push_back(stone);
		}
	}

	bool HaveStoneAt(int point_x, int point_y) {
		for (BadukStone cur_stone : stones) {
			if (cur_stone.coords.x == point_x && cur_stone.coords.y == point_y) {
				return true;
			}
		}
		return false;
	}

	bool HaveStoneAt(BadukCoords coords) {
		return HaveStoneAt(coords.x, coords.y);
	}
};

struct QuestionVariant {
	std::wstring text;
	std::string mark;
};