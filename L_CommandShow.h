#pragma once
#include "L_Command.h"

class L_CommandShow : public L_Command {
public:
	L_CommandShow(std::string p_name, std::string p_emotion, float p_pos_left, float p_pos_down, float p_scale, bool p_show_instantly);
	void virtual Do(L_Scene& scene) override;
private:
    std::string name;
    std::string emotion;
    float position_left;
    float position_down;
    float scale;
    bool show_instantly;
};

