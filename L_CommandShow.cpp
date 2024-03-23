#include "L_CommandShow.h"
using namespace std;

L_CommandShow::L_CommandShow(string p_name, string p_emotion, float p_pos_left, float p_pos_down, float p_scale, bool p_show_instantly) {
	can_process_next = true;
	name = p_name;
	emotion = p_emotion;
	position_left = p_pos_left;
	position_down = p_pos_down;
	scale = p_scale;
	show_instantly = p_show_instantly;
}

void L_CommandShow::Do(L_Scene& scene) {
	scene.characters.ShowCharacter(name, emotion, position_left, position_down, scale, show_instantly);
}
