#pragma once
#include "L_Command.h"
#include "L_Scene.h"

class L_CommandHidecharacter : public L_Command{
public:
	L_CommandHidecharacter();
	void virtual Do(L_Scene& scene) override;
};

