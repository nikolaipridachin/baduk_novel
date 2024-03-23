#include "L_CommandQuestion.h"

L_CommandQuestion::L_CommandQuestion() {
	can_process_next = false;
	variants.clear();
}

void L_CommandQuestion::AddVariant(QuestionVariant variant_to_add) {
	variants.push_back(variant_to_add);
}

void L_CommandQuestion::Do(L_Scene& scene) {
	scene.question.SetVariants(variants);
	scene.SetState(game_state::Question);
}
