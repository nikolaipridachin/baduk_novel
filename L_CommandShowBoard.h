#pragma once
#include "L_Command.h"

class L_CommandShowBoard : public L_Command {
public:
	L_CommandShowBoard();
	void virtual Do(L_Scene& scene) override;
};

