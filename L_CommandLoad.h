#pragma once
#include "L_Command.h"
#include "L_ScriptSystem.h"

class L_CommandLoad : public L_Command {
public:
	L_CommandLoad(std::string filename, L_ScriptSystem& p_script_system);
	void virtual Do(L_Scene& scene) override;
private:
	L_ScriptSystem* script_system = nullptr;
	std::string m_Filename;
};

