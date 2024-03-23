#include "L_BadukField.h"

bool L_BadukField::PlaceStone(StoneColor color, BadukCoords coords) {
    if (is_PointEmpty(coords)) {
        stones.emplace_back(color, coords);
        return true;
    }
    return false;
}

bool L_BadukField::MakeMove(StoneColor color, BadukCoords coords) {
    if (is_LegalMove(color, coords)) {
        PlaceStone(color, coords);
        std::vector<BadukCoords> coords_to_check;
        coords_to_check.push_back(BadukCoords{ coords.x - 1, coords.y });
        coords_to_check.push_back(BadukCoords{ coords.x + 1, coords.y });
        coords_to_check.push_back(BadukCoords{ coords.x, coords.y - 1 });
        coords_to_check.push_back(BadukCoords{ coords.x, coords.y + 1 });
        for (BadukCoords cur_coords : coords_to_check) {
            BadukGroup group_to_check = InitGroup(cur_coords);
            if (group_to_check.color != StoneColor::Undefined && group_to_check.dame_count == 0) {
                RemoveGroup(cur_coords);
            }
        }
        return true;
    }
    return false;
}

bool L_BadukField::GetStone(BadukCoords coords, BadukStone& stone) {
    for (BadukStone cur_stone : stones) {
        if (cur_stone.coords.x == coords.x && cur_stone.coords.y == coords.y) {
            stone = cur_stone;
            return true;
        }
    }
    return false;
}

bool L_BadukField::is_PointEmpty(BadukCoords coords)
{
    if (coords.x < 0 || coords.x >= width || coords.y < 0 || coords.y >= height) {
        return false;
    }
    for (BadukStone cur_stone : stones) {
        if (cur_stone.coords.x == coords.x && cur_stone.coords.y == coords.y) {
            return false;
        }
    }
    return true;
}

bool L_BadukField::is_LegalMove(StoneColor move_color, BadukCoords coords) {
    if (!is_PointEmpty(coords)) {
        return false;
    }
    StoneColor opponent_color = StoneColor::Undefined;
    if (move_color == StoneColor::Black) {
        opponent_color = StoneColor::White;
    }
    if (move_color == StoneColor::White) {
        opponent_color = StoneColor::Black;
    }
    std::vector<BadukCoords> coords_to_check;
    coords_to_check.push_back(BadukCoords{ coords.x - 1, coords.y });
    coords_to_check.push_back(BadukCoords{ coords.x + 1, coords.y });
    coords_to_check.push_back(BadukCoords{ coords.x, coords.y - 1 });
    coords_to_check.push_back(BadukCoords{ coords.x, coords.y + 1 });
    for (BadukCoords cur_coords : coords_to_check) {
        // Empty point is near
        if (is_PointEmpty(cur_coords)) {
            return true;
        }
        // Opponent with 1 dame is near
        BadukGroup group_to_check = InitGroup(cur_coords);
        if (group_to_check.color == opponent_color && group_to_check.dame_count <= 1) {
            return true;
        }
        // Connecting with allied stones with dame
        if (group_to_check.color == move_color && group_to_check.dame_count > 1) {
            return true;
        }
    }
    return false;
}

bool L_BadukField::is_ValidCoords(BadukCoords coords) const {
    return coords.x >= 0 && coords.x < width && coords.y >= 0 && coords.y < height;
}

BadukGroup L_BadukField::InitGroup(BadukCoords coords) {
    BadukGroup result;
    BadukStone start_stone;

    if (GetStone(coords, start_stone)) {
        bool we_have_new_stones = true;
        result.color = start_stone.color;
        result.AddStone(start_stone);
        while (we_have_new_stones) {
            we_have_new_stones = false;
            std::vector<BadukCoords> coords_to_check;
            for (BadukStone cur_stone : result.stones) {
                coords_to_check.clear();
                coords_to_check.push_back(BadukCoords{ cur_stone.coords.x - 1, cur_stone.coords.y });
                coords_to_check.push_back(BadukCoords{ cur_stone.coords.x + 1, cur_stone.coords.y });
                coords_to_check.push_back(BadukCoords{ cur_stone.coords.x, cur_stone.coords.y - 1 });
                coords_to_check.push_back(BadukCoords{ cur_stone.coords.x, cur_stone.coords.y + 1 });
                for (BadukCoords cur_coords : coords_to_check) {
                    BadukStone cur_stone;
                    if (GetStone(cur_coords, cur_stone)) {
                        if (!result.HaveStoneAt(cur_coords) && cur_stone.color == result.color) {
                            we_have_new_stones = true;
                            result.AddStone(cur_stone);
                        }
                    }
                }
            }
        }
    }
    CalculateDame(result);
    return result;
}

void L_BadukField::CalculateDame(BadukGroup& group_to_update) {
    std::vector<BadukCoords> dame_points;
    std::vector<BadukCoords> coords_to_check;
    for (BadukStone cur_stone : group_to_update.stones) {
        coords_to_check.push_back(BadukCoords{ cur_stone.coords.x - 1, cur_stone.coords.y });
        coords_to_check.push_back(BadukCoords{ cur_stone.coords.x + 1, cur_stone.coords.y });
        coords_to_check.push_back(BadukCoords{ cur_stone.coords.x, cur_stone.coords.y - 1 });
        coords_to_check.push_back(BadukCoords{ cur_stone.coords.x, cur_stone.coords.y + 1 });
        for (BadukCoords cur_coords : coords_to_check) {
            if (is_PointEmpty(cur_coords)) {
                bool is_dame_already_in_vector = false;
                for (BadukCoords cur_point : dame_points) {
                    if (cur_point.x == cur_coords.x && cur_point.y == cur_coords.y) {
                        is_dame_already_in_vector = true;
                    }
                }
                if (!is_dame_already_in_vector) {
                    dame_points.push_back(cur_coords);
                }
            }
        }
    }
    group_to_update.dame_count = (int)dame_points.size();
}

void L_BadukField::SetSize(int p_width, int p_height) {
    width = p_width;
    height = p_height;
    if (width < 0) {
        width = 0;
    }
    if (height < 0) {
        height = 0;
    }
}

void L_BadukField::RemoveGroup(BadukCoords coords) {
    BadukGroup group_to_delete = InitGroup(coords);
    if (group_to_delete.color != StoneColor::Undefined) {
        for (BadukStone cur_stone : group_to_delete.stones) {
            RemoveStone(cur_stone.coords);
        }
    }
}

void L_BadukField::RemoveStone(BadukCoords coords_to_delete) {
    for (auto it = stones.begin(); it != stones.end();) {
        auto& stone = *it;
        if (stone.coords == coords_to_delete) {
            it = stones.erase(it);
        }
        else {
            it++;
        }
    }
}
