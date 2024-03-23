#pragma once
#include <vector>
#include <iostream>
#include "baduk_structs.h"

class L_BadukField {
public:
	int width = 19;
	int height = 19;
	std::vector<BadukStone> stones;

	bool PlaceStone(StoneColor color, BadukCoords coords);
	bool MakeMove(StoneColor color, BadukCoords coords);
	bool GetStone(BadukCoords coords, BadukStone& stone);
	bool is_PointEmpty(BadukCoords coords);
	bool is_LegalMove(StoneColor move_color, BadukCoords coords);
	bool is_ValidCoords(BadukCoords coords) const;
	BadukGroup InitGroup(BadukCoords coords);
	void CalculateDame(BadukGroup& group_to_update);
	void SetSize(int p_width, int p_height);
	void RemoveGroup(BadukCoords coords);
	void RemoveStone(BadukCoords coords_to_delete);
};

