#pragma once
#include "L_Command.h"
#include "L_Scene.h"
#include "L_GoProblem.h"

class L_CommandGoProblem : public L_Command {
private:
	L_GoProblem go_problem;
	void virtual Do(L_Scene& scene) override;
public:
	L_CommandGoProblem();

	void SetGoProblem(L_GoProblem problem_to_set);
	L_GoProblem GetGoProblem() { return go_problem; };
};

