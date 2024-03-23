#pragma once
#include "L_Command.h"
#include "L_Scene.h"

class L_CommandSay : public L_Command{
public:
	L_CommandSay(std::wstring p_message, bool p_show_instantly = false);
	void virtual Do(L_Scene& scene) override;
private:
	std::wstring message;
	bool show_instantly;
};

