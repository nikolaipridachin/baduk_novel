#include "L_CommandGoProblem.h"

L_CommandGoProblem::L_CommandGoProblem() {
	can_process_next = false;
}

void L_CommandGoProblem::SetGoProblem(L_GoProblem problem_to_set) {
	go_problem = problem_to_set;
}

void L_CommandGoProblem::Do(L_Scene& scene) {
	scene.board.SetupGoProblem(go_problem);
	scene.messagebox.Say(scene.board.GetProblemTask());
}
