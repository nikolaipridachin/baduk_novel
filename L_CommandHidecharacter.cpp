#include "L_CommandHidecharacter.h"

L_CommandHidecharacter::L_CommandHidecharacter() {
	can_process_next = true;

}

void L_CommandHidecharacter::Do(L_Scene& scene) {
	scene.characters.HideCharacters();
}
