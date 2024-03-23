#pragma once
#include "L_Command.h"

class L_CommandName : public L_Command {
public:
	L_CommandName(std::wstring p_name);
	void virtual Do(L_Scene& scene) override;
private:
	std::wstring name;
};

