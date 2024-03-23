#pragma once
#include <memory>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "bnu.h"
#include "tinyxml2.h"
#include "SFML/Graphics.hpp"
#include "L_Scene.h"
#include "L_Command.h"

class L_ScriptSystem {
public:
	void SetScene(L_Scene* p_scene);
	void Load(std::string filename, int p_current_step = 0, bool can_process_next = false, bool step_back = false);
	void ProcessNextCommand();
	bool GoTo(std::string mark_to_go, bool step_back = false);
private:
	int current_command_id = 0;
	L_Scene* scene;
	std::vector<std::unique_ptr<L_Command>> commands;
	std::map<std::string, int> marks;
};

