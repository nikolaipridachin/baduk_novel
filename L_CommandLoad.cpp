#include "L_CommandLoad.h"

L_CommandLoad::L_CommandLoad(std::string filename, L_ScriptSystem& p_script_system) {
	m_Filename = filename;
	can_process_next = true;
	script_system = &p_script_system;
}

void L_CommandLoad::Do(L_Scene& scene) {
	if (!m_Filename.empty()) {
		script_system->Load(m_Filename, 0, can_process_next, true);
	}
}
