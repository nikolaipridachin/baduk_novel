#pragma once
#include <memory>
#include <iostream>
#include <list>
#include "game_structs.h"
#include "L_AudioSystem.h"
#include "L_BlockMainMenu.h"
#include "L_BlockBackground.h"
#include "L_BlockMessageBox.h"
#include "L_BlockCharacters.h"
#include "L_BlockSettings.h"
#include "L_BlockDarkLayer.h"
#include "L_BlockContextMenu.h"
#include "L_BlockSmartphone.h"
#include "L_BlockBadukTop.h"
#include "L_BLockQuestion.h"
#include "L_BlockBoard.h"
#include "L_BlockSaveLoadScreen.h"
#include "L_StateRecord.h"

class L_Scene {
public:
	game_state state = None;
	L_StateRecord state_record;

	L_BlockMainMenu main_menu;
	L_BlockBackground background;
	L_BlockMessageBox messagebox;
	L_BlockCharacters characters;
	L_BlockSettings settings;
	L_BlockDarkLayer dark_layer;
	L_BlockContextMenu context_menu;
	L_BlockSmartphone smartphone;
	L_BlockBadukTop baduktop;
	L_BlockQuestion question;
	L_BlockBoard board;
	L_BlockSaveLoadScreen saveload_screen;

	L_AudioSystem sound;

	void Init(sf::RenderWindow* p_window, L_Localization* p_loc);
	void Update();
	void Render();
	void SetState(game_state p_state);
	void DisableAllBlocks();
	void MouseDown(sf::Event p_event);
	void MouseUp(sf::Event p_event);
	void UpdateLanguage();
	void CloseContextMenu();
	void RememberState();
	void RecoverState(L_StateRecord record);

	bool GetPreventOtherActions();
	bool Busy();
private:
	unsigned int window_width = 1600, window_height = 900;
	float scale_x = 1.0f, scale_y = 1.0f;
	sf::Vector2i mouse_position;
	sf::Vector2f mouse_world;
	bool cursor_loaded = false;
	sf::RectangleShape sprite_cursor;
	sf::Texture tex_cursor;

	L_Localization* loc;

	game_state state_before_context_menu;
	
	sf::RenderWindow* window = nullptr;
	std::vector<L_Block*> blocks;

	sf::Font menu_font;
	sf::Font character_name_font;
	sf::Font messagebox_font;

	void InitCursor();
	void InitFonts();
	void Resize();
};

