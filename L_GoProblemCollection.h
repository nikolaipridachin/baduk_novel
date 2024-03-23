#pragma once
#include <iostream>
#include <vector>
#include "L_GoProblem.h"

class L_GoProblemCollection {
public:
	std::string name;
	int level = 1;
	std::vector<L_GoProblem> goproblems;

	void Clear();
	void SetName(std::string p_name);
	void SetLevel(int p_level);
	void AddGoProblem(L_GoProblem problem_to_add);
	L_GoProblem GetGoProblem(int index);
};

