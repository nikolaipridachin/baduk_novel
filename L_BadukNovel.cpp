#include "L_BadukNovel.h"
using namespace std;

void L_BadukNovel::Init(sf::RenderWindow* p_window) {
	window = p_window;
	setlocale(LC_ALL, "RU");
	loc.Init("ru");

	scene.Init(window, &loc);
	goproblem_manager.ReadAllFiles();
	scene.baduktop.SetGoProblems(goproblem_manager);
	scene.SetState(game_state::MainMenu);

	script.SetScene(&scene);

	scene.main_menu.button_new_game->action_click = [&] {
		scene.SetState(game_state::Gameplay);
		scene.messagebox.prevent_other_actions = true;
		try {
			script.Load("start");
		}
		catch (range_error) {
			cout << "Error: Range error. Possible non UTF8 file encoding";
		}
		script.ProcessNextCommand();
		};
	scene.main_menu.button_continue->action_click = [&] {
		scene.RecoverState(scene.state_record);
		};
	scene.settings.button_russian->action_click = [&] {
		ChangeLanguage("ru");
		};
	scene.settings.button_english->action_click = [&] {
		ChangeLanguage("en");
		};
	scene.settings.button_fullscreen->action_click = [&] {
		SetFullscreen(true);
		};
	scene.settings.button_windowed->action_click = [&] {
		SetFullscreen(false);
		};
	scene.context_menu.button_back->action_click = [&] {
		scene.CloseContextMenu();
		};
	scene.background.action_animation_finished = [&] {
		script.ProcessNextCommand();
		};
	scene.context_menu.button_main_menu->action_click = [&] {
		scene.SetState(game_state::MainMenu);
		};
	scene.context_menu.button_exit->action_click = [&] {
		window->close();
		};
	scene.context_menu.button_settings->action_click = [&] {
		scene.settings.state_from = game_state::ContextMenu;
		scene.SetState(game_state::Settings);
		};
	scene.messagebox.action_icon_smartphone_clicked = [&] {
		scene.SetState(game_state::Smartphone);
		};
	scene.smartphone.action_clicked_outside = [&] {
		scene.SetState(game_state::Gameplay);
		};
	scene.smartphone.button_baduktop->action_click = [&] {
		scene.SetState(game_state::BadukTop);
		};
	scene.baduktop.action_clicked_outside = [&] {
		scene.SetState(game_state::Gameplay);
		};
	scene.question.action_go_forward = [&] {
		if (script.GoTo(scene.question.clicked_mark)) {
			scene.SetState(game_state::Gameplay);
		}
		};
	scene.board.action_say = [&](std::wstring message) {
		scene.messagebox.Say(message);
		};
	scene.board.action_problem_completed = [&] {
		script.ProcessNextCommand();
		};
	scene.board.action_take_stone = [&] {
		scene.sound.PlayTakeStoneSound();
		};
	scene.board.action_place_stone = [&] {
		scene.sound.PlayPlaceStoneSound();
		};
}

void L_BadukNovel::Render() {
	scene.Render();
}

void L_BadukNovel::Update() {
	scene.Update();
}

void L_BadukNovel::KeyDown(sf::Keyboard::Key p_key) {
	if (p_key == sf::Keyboard::Q) {
		scene.SetState(game_state::SaveGame);
		return;
	}
	if (p_key == sf::Keyboard::E) {
		scene.SetState(game_state::LoadGame);
		//saveload_system.ReadSavesFolder();
		//scene.saveload_screen.test_saveload_element.LoadFromFile("14_02_2024_22_31_08");
		//scene.RecoverState(scene.state_record);
		return;
	}
	if (p_key == sf::Keyboard::Escape) {
		if (scene.state == game_state::Gameplay ||
			scene.state == game_state::Settings ||
			scene.state == game_state::Board) {
			scene.RememberState();
			scene.SetState(game_state::MainMenu);
			return;
		}
		if (scene.state == game_state::BadukTop) {
			if (scene.baduktop.state == baduktop_state::SelectProblem ||
				scene.baduktop.state == baduktop_state::Solving) {
				scene.baduktop.GoBack();
			}
			else {
				scene.SetState(game_state::Smartphone);
			}
			return;
		}
		if (scene.state == game_state::Smartphone) {
			scene.SetState(game_state::Gameplay);
			return;
		}
		if (scene.state == game_state::MainMenu) {
			window->close();
			return;
		}
		return;
	}
}

void L_BadukNovel::MouseDown(sf::Event p_event) {
	scene.MouseDown(p_event);
	bool prevent_other_actions = scene.GetPreventOtherActions();
	if (prevent_other_actions) {
		return;
	}
	
	if (p_event.mouseButton.button == sf::Mouse::Left) {
		if (scene.state == game_state::Gameplay && !scene.Busy()) {
			script.ProcessNextCommand();
			return;
		}
		if (scene.state == game_state::Board && scene.board.CanProcessNextCommand()) {
			script.ProcessNextCommand();
			return;
		}
	}
	if (p_event.mouseButton.button == sf::Mouse::Right) {
		if (scene.state == game_state::Gameplay) {
			scene.SetState(game_state::ContextMenu);
			return;
		}
		if (scene.state == game_state::ContextMenu) {
			scene.CloseContextMenu();
			return;
		}
		if (scene.state == game_state::BadukTop) {
			if (scene.baduktop.state == baduktop_state::SelectProblem ||
				scene.baduktop.state == baduktop_state::Solving) {
				scene.baduktop.GoBack();
			}
			else {
				scene.SetState(game_state::Smartphone);
			}
			return;
		}
	}
}

void L_BadukNovel::MouseUp(sf::Event p_event) {
	scene.MouseUp(p_event);
}

void L_BadukNovel::ChangeLanguage(std::string param) {
	loc.Init(param);
	if (strcmp(loc.lang.c_str(), param.c_str()) == 0) {
		scene.UpdateLanguage();
	}
}

void L_BadukNovel::SetFullscreen(bool param) {
	if (param) {
		is_fullscreen = true;
		window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Ishi no Ki", sf::Style::Fullscreen);
		window->setMouseCursorVisible(false);
		window->setFramerateLimit(120);
	}
	else {
		is_fullscreen = false;
		window->create(sf::VideoMode(1600, 900), "Ishi no Ki", sf::Style::Titlebar | sf::Style::Close);
		window->setMouseCursorVisible(false);
		window->setFramerateLimit(120);
		auto desktop = sf::VideoMode::getDesktopMode();
		window->setPosition(sf::Vector2i(desktop.width / 2 - window->getSize().x / 2, desktop.height / 2 - window->getSize().y / 2 - 37));
	}
}