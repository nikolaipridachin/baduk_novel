#include "L_CommandSay.h"

L_CommandSay::L_CommandSay(std::wstring p_message, bool p_show_instantly) {
	message = p_message;
	show_instantly = p_show_instantly;
}

void L_CommandSay::Do(L_Scene& scene) {
	scene.messagebox.Say(message, show_instantly);
}
