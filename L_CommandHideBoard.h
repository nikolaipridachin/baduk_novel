#pragma once
#include "L_Command.h"

class L_CommandHideBoard : public L_Command {
public:
	L_CommandHideBoard();
	virtual void Do(L_Scene& scene) override;
};

