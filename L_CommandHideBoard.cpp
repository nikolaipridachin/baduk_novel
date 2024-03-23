#include "L_CommandHideBoard.h"

L_CommandHideBoard::L_CommandHideBoard() {
	can_process_next = true;
}

void L_CommandHideBoard::Do(L_Scene& scene) {
	scene.SetState(game_state::Gameplay);
}
