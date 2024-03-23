#pragma once
#include "L_Scene.h"

class L_Command {
public:
	bool can_process_next = false;
	virtual ~L_Command() = default;
	virtual void Do(L_Scene& scene) = 0;
};

