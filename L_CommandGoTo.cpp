#include "L_CommandGoTo.h"

L_CommandGoTo::L_CommandGoTo(std::string p_mark_to_go, L_ScriptSystem& p_script_system) {
	can_process_next = true;
	script_system = &p_script_system;
	mark_to_go = p_mark_to_go;
}

void L_CommandGoTo::Do(L_Scene& scene) {
	script_system->GoTo(mark_to_go, true);
}
