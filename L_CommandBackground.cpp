#include "L_CommandBackground.h"

L_CommandBackground::L_CommandBackground(std::string p_background, std::string p_effect) {
	m_background = p_background;
	m_effect = p_effect;
	if (m_effect.empty()) {
		can_process_next = true;
	}
	else {
		can_process_next = false;
	}
}

void L_CommandBackground::Do(L_Scene& scene) {
		scene.background.Set("Content/bg/" + m_background + ".jpg", m_effect);
}
