#include "L_CommandShowBoard.h"

L_CommandShowBoard::L_CommandShowBoard() {
	can_process_next = true;
}

void L_CommandShowBoard::Do(L_Scene& scene) {
	scene.SetState(game_state::Board);
}
