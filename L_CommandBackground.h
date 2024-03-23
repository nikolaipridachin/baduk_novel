#pragma once
#include "L_Command.h"
#include "L_Scene.h"

class L_CommandBackground : public L_Command{
public:
	L_CommandBackground(std::string p_background, std::string p_effect = "");
	void virtual Do(L_Scene& scene) override;
private:
	std::string m_background;
	std::string m_effect;
};

