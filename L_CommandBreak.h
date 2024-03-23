#pragma once
#include "L_Command.h"

class L_CommandBreak : public L_Command {
public:
	L_CommandBreak();
	void virtual Do(L_Scene& scene) override;
};

