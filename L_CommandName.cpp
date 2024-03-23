#include "L_CommandName.h"

L_CommandName::L_CommandName(std::wstring p_name) {
	can_process_next = true;
	name = p_name;
}

void L_CommandName::Do(L_Scene& scene) {
	scene.messagebox.SetName(name);
}
