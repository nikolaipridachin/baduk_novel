#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "L_Localization.h"
#include "game_structs.h"

class L_Block {
public:
	bool active = false;
	sf::RenderWindow* window;
	L_Localization* loc;
	float scale_x = 1.0f, scale_y = 1.0f;
	bool prevent_other_actions = false;

	void SetWindow(sf::RenderWindow* p_window);
	virtual void Click();
	virtual void MouseMove(float mouse_x, float mouse_y);
	virtual void MouseDown(sf::Event p_event, game_state clicked_state);
	virtual void MouseUp(sf::Event p_event, game_state clicked_state);
	virtual void SetActive(bool p_active);
	virtual void Render();
	virtual void Resize();
	virtual void Update();
	virtual void UpdateLanguage();

	void UpdateScale();
};

