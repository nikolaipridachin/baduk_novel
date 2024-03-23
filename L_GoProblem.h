#pragma once
#include <vector>
#include <iostream>
#include "baduk_structs.h"
#include "bnu.h"

struct GoProblemBranch {
	std::string moves;
	std::string result;
};

enum goproblem_result {
	GoodMove, Mistake, Solved
};

class L_GoProblem {
public:
	std::string black_stones;
	std::string white_stones;
	std::vector<GoProblemBranch> branches;
	std::wstring task;
	std::wstring fail_comment;
	void Clear();
	void SetBlackStones(std::string p_black_stones);
	void SetWhiteStones(std::string p_white_stones);
	void AddBranch(std::string p_moves, std::string p_result);
	void SetTask(std::wstring task_to_setup);
	void SetFailComment(std::wstring fail_comment_to_setup);
	bool is_empty();
	goproblem_result CheckResult(std::string moves);
	bool GetPossibleAnswer(std::string moves, std::vector<BadukCoords>& out_coords);
};

