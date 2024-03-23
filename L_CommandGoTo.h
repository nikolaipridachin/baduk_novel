#pragma once
#include "L_Command.h"
#include "L_Scene.h"
#include "L_ScriptSystem.h"

class L_CommandGoTo : public L_Command {
public:
	L_ScriptSystem* script_system;
	L_CommandGoTo(std::string p_mark_to_go, L_ScriptSystem& p_script_system);
	void virtual Do(L_Scene& scene) override;
	std::string mark_to_go;
};