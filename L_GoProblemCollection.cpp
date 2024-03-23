#include "L_GoProblemCollection.h"
using namespace std;

void L_GoProblemCollection::Clear() {
	name = string();
}

void L_GoProblemCollection::SetName(string p_name) {
	name = p_name;
}

void L_GoProblemCollection::AddGoProblem(L_GoProblem problem_to_add) {
	goproblems.push_back(problem_to_add);
}

L_GoProblem L_GoProblemCollection::GetGoProblem(int index) {
	if (index < goproblems.size() && index >= 0) {
		return goproblems[index];
	}
	return L_GoProblem();
}

void L_GoProblemCollection::SetLevel(int p_level) {
	level = p_level;
}
