#pragma once
#include <memory>
#include <iostream>
#include "L_Scene.h"
#include "L_ScriptSystem.h"
#include "L_SaveLoadSystem.h"
#include "L_Localization.h"
#include "L_GoProblemManager.h"

class L_BadukNovel
{
public:
	sf::RenderWindow* window = nullptr;
	sf::VideoMode* video_mode = nullptr;
	L_Scene scene;
	L_SaveLoadSystem saveload_system;
	L_ScriptSystem script;
	L_Localization loc;
	L_GoProblemManager goproblem_manager;

	bool is_fullscreen = false;

	void Init(sf::RenderWindow* p_window);
	void Render();
	void Update();
	void KeyDown(sf::Keyboard::Key p_key);
	void MouseDown(sf::Event p_event);
	void MouseUp(sf::Event p_event);
	void ChangeLanguage(std::string param);
	void SetFullscreen(bool param);
private:
};

