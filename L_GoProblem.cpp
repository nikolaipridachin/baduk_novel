#include "L_GoProblem.h"
using namespace std;

void L_GoProblem::Clear() {
	black_stones = string();
	white_stones = string();
	branches.clear();
}

void L_GoProblem::SetBlackStones(std::string p_black_stones) {
	black_stones = p_black_stones;
}

void L_GoProblem::SetWhiteStones(std::string p_white_stones) {
	white_stones = p_white_stones;
}

void L_GoProblem::AddBranch(std::string p_moves, std::string p_result) {
	GoProblemBranch branch_to_insert;
	branch_to_insert.moves = p_moves;
	branch_to_insert.result = p_result;
	branches.push_back(branch_to_insert);
}

void L_GoProblem::SetTask(std::wstring task_to_setup) {
	task = task_to_setup;
}

void L_GoProblem::SetFailComment(std::wstring fail_comment_to_setup) {
	fail_comment = fail_comment_to_setup;
}

bool L_GoProblem::is_empty() {
	if (black_stones.empty() && white_stones.empty() && branches.empty()) {
		return true;
	}
	else {
		return false;
	}
}

goproblem_result L_GoProblem::CheckResult(std::string moves) {
	for (GoProblemBranch cur_branch : branches) {
		if (cur_branch.moves == moves && cur_branch.result == "solved") {
			return goproblem_result::Solved;
		}
		if (cur_branch.moves == moves && cur_branch.result == "mistake") {
			return goproblem_result::Mistake;
		}
		if (cur_branch.moves.length() > moves.length()) {
			std::string fragment = cur_branch.moves.substr(0, moves.length());
			if (fragment == moves) {
				return goproblem_result::GoodMove;
			}
		}
	}
	return goproblem_result::Mistake;
}

bool L_GoProblem::GetPossibleAnswer(std::string moves, std::vector<BadukCoords>& out_coords) {
	out_coords.clear();
	for (GoProblemBranch cur_branch : branches) {
		if (cur_branch.moves.length() > moves.length()) {
			std::string fragment = cur_branch.moves.substr(0, moves.length());
			if (fragment == moves) {
				std::string rest_moves = cur_branch.moves.substr(moves.length() + 1);
				std::string next_move = rest_moves.substr(0, rest_moves.find(' '));
				BadukCoords answer_to_insert;
				if (bnu::extract_coords(next_move, answer_to_insert)) {
					out_coords.push_back(answer_to_insert);
				}
			}
		}
	}
	if ((int)out_coords.size() > 0) {
		return true;
	}
	else {
		return false;
	}
}
