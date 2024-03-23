#include "L_Scene.h"
using namespace std;

void L_Scene::Init(sf::RenderWindow* p_window, L_Localization* p_loc) {
	window = p_window;
	loc = p_loc;
	InitFonts();
	InitCursor();

	blocks.clear();

	background.Init(window);
	blocks.push_back(&background);

	main_menu.Init(window, loc);
	main_menu.SetFont(menu_font);
	main_menu.button_exit->action_click = [&] {
		window->close();
		};
	main_menu.button_settings->action_click = [&] {
		SetState(game_state::Settings);
		};
	blocks.push_back(&main_menu);

	characters.SetWindow(window);
	blocks.push_back(&characters);

	board.Init(window, loc);
	blocks.push_back(&board);

	messagebox.Init(window);
	messagebox.SetName(L"");
	messagebox.Say(L"");
	messagebox.SetNameFont(character_name_font);
	messagebox.SetMessageBoxFont(messagebox_font);
	blocks.push_back(&messagebox);

	settings.Init(window, loc);
	settings.SetFont(menu_font);
	settings.button_back->action_click = [&] {
		SetState(settings.state_from);
		};
	blocks.push_back(&settings);

	dark_layer.Init(window);
	blocks.push_back(&dark_layer);

	context_menu.Init(window, loc);
	context_menu.SetFont(menu_font);
	blocks.push_back(&context_menu);

	smartphone.Init(window, loc);
	blocks.push_back(&smartphone);

	baduktop.Init(window, loc);
	baduktop.SetFont(menu_font);
	baduktop.action_close = [&] {
		SetState(game_state::Smartphone);
		};
	blocks.push_back(&baduktop);

	question.Init(window, loc);
	question.SetFont(menu_font);
	blocks.push_back(&question);

	saveload_screen.Init(window, loc);
	saveload_screen.SetFont(menu_font);
	blocks.push_back(&saveload_screen);

	Resize();
}

void L_Scene::InitCursor() {
	cursor_loaded = true;
	if (!tex_cursor.loadFromFile("Content/ui/cursors/default.png")) {
		cursor_loaded = false;
	}
	if (cursor_loaded) {
		sprite_cursor.setTexture(&tex_cursor);
		sprite_cursor.setSize(sf::Vector2f((float)tex_cursor.getSize().x, (float)tex_cursor.getSize().y));
		sprite_cursor.setPosition(0.0f, 0.0f);
		window->setMouseCursorVisible(false);
	}
	else {
		window->setMouseCursorVisible(true);
	}
}

void L_Scene::InitFonts() {
	if (!menu_font.loadFromFile("Content/ui/fonts/neucha.ttf")) {
		// Error loading font
	}
	if (!character_name_font.loadFromFile("Content/ui/fonts/noto_serif.ttf")) {
		// Error loading font
	}
	if (!messagebox_font.loadFromFile("Content/ui/fonts/noto_serif.ttf")) {
		// Error loading font
	}
}

void L_Scene::Render() {
	for (L_Block* current_block : blocks) {
		if (current_block->active) {
			current_block->Render();
		}
	}
	if (cursor_loaded) {
		window->draw(sprite_cursor);
	}
}

void L_Scene::SetState(game_state p_state) {
	game_state from = state;
	DisableAllBlocks();
	if (p_state == game_state::MainMenu) {
		state = p_state;
		background.BreakAnimation();
		background.Set("Content/ui/menu_background.jpg");
		background.SetActive(true);
		main_menu.SetActive(true);
		if (from != game_state::Settings) {
			sound.PlayMusic("menu_theme");
		}
		return;
	}
	if (p_state == game_state::Gameplay) {
		state = p_state;
		background.SetActive(true);
		messagebox.SetActive(true);
		characters.SetActive(true);
		sound.StopMusic();
		return;
	}
	if (p_state == game_state::Question) {
		state = p_state;
		background.SetActive(true);
		messagebox.SetActive(true);
		characters.SetActive(true);
		dark_layer.SetActive(true);
		question.SetActive(true);
		return;
	}
	if (p_state == game_state::Settings) {
		state = p_state;
		settings.SetActive(true);
		return;
	}
	if (p_state == game_state::Board) {
		state = p_state;
		messagebox.SetActive(true);
		board.SetActive(true);
		return;
	}
	if (p_state == game_state::ContextMenu) {
		if (from == game_state::Gameplay || from == game_state::Settings) {
			state = p_state;
			state_before_context_menu = game_state::Gameplay;
			background.SetActive(true);
			messagebox.SetActive(true);
			characters.SetActive(true);
			dark_layer.SetActive(true);
			context_menu.SetActive(true);
		}
		return;
	}
	if (p_state == game_state::Smartphone) {
		if (from == game_state::Gameplay || from == game_state::BadukTop) {
			state = p_state;
			background.SetActive(true);
			messagebox.SetActive(true);
			characters.SetActive(true);
			dark_layer.SetActive(true);
			smartphone.SetActive(true);
		}
		return;
	}
	if (p_state == game_state::BadukTop) {
		state = p_state;
		background.SetActive(true);
		messagebox.SetActive(true);
		characters.SetActive(true);
		dark_layer.SetActive(true);
		baduktop.SetActive(true);
		baduktop.SetState(baduktop_state::MainScreen);
		return;
	}
	if (p_state == game_state::SaveGame) {
		state = p_state;
		saveload_screen.SetMode("save");
		saveload_screen.SetActive(true);
		return;
	}
	if (p_state == game_state::LoadGame) {
		state = p_state;
		saveload_screen.SetMode("load");
		saveload_screen.SetActive(true);
		return;
	}
}

void L_Scene::DisableAllBlocks() {
	for (L_Block* current_block : blocks) {
		current_block->SetActive(false);
	}
}

void L_Scene::MouseDown(sf::Event p_event) {
	game_state clicked_state = state;
	for (L_Block* current_block : blocks) {
		if (current_block->active) {
			current_block->MouseDown(p_event, clicked_state);
		}
	}
}

void L_Scene::MouseUp(sf::Event p_event) {
	game_state clicked_state = state;
	for (L_Block* current_block : blocks) {
		if (current_block->active) {
			current_block->MouseUp(p_event, clicked_state);
		}
	}
}

void L_Scene::UpdateLanguage() {
	for (L_Block* current_block : blocks) {
		current_block->UpdateLanguage();
	}
}

void L_Scene::CloseContextMenu() {
	if (state_before_context_menu == game_state::Gameplay) {
		SetState(game_state::Gameplay);
	}
}

void L_Scene::RememberState() {
	state_record.SetState(state);
	state_record.SetBackground(background.GetBackgroundName());
	state_record.SetName(messagebox.GetName());
	state_record.SetMessage(messagebox.GetMessage());
}

void L_Scene::RecoverState(L_StateRecord record) {
	if (state_record.GetState() == game_state::None) {
		return;
	}
	SetState(state_record.GetState());
	background.Set(state_record.GetBackground());
	messagebox.SetName(state_record.GetName());
	messagebox.Say(state_record.GetMessage(), true);
}

bool L_Scene::GetPreventOtherActions() {
	bool result = false;
	for (L_Block* current_block : blocks) {
		if (current_block->prevent_other_actions == true) {
			current_block->prevent_other_actions = false;
			result = true;
		}
	}
	return result;
}

bool L_Scene::Busy() {
	if (background.state == background_state::Animating) {
		return true;
	}
	return false;
}

void L_Scene::Update() {
	// Check window size changed
	sf::Vector2u window_size = window->getSize();
	if (window_width != window_size.x || window_height != window_size.y) {
		window_width = window_size.x;
		window_height = window_size.y;
		Resize();
	}

	//Update scale
	scale_x = window->getSize().x / 1920.0f;
	scale_y = window->getSize().y / 1080.0f;

	//Update mouse coordinates
	mouse_position = sf::Mouse::getPosition(*window);
	for (L_Block* current_block : blocks) {
		current_block->MouseMove((float)mouse_position.x, (float)mouse_position.y);
	}
	//cout << mouse_world.x << " - " << mouse_world.y << "\n";

	//Update cursor position
	sprite_cursor.setPosition((float)mouse_position.x, (float)mouse_position.y);

	for (L_Block* current_block : blocks) {
		current_block->Update();
	}
}

void L_Scene::Resize() {
	for (L_Block* current_block : blocks) {
		current_block->Resize();
	}
}