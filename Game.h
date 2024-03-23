#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <windows.h>

#include "L_BadukNovel.h"

class Game {
private:
	//Variables
	//Window
	std::unique_ptr<sf::RenderWindow> window;
	sf::VideoMode video_mode;
	sf::Event ev;

	sf::Vector2i mouse_position;
	L_BadukNovel baduk_novel;

	sf::RectangleShape enemy;
	sf::Texture* texture;

	//Shader test
	sf::Shader shader;
	sf::Texture* tex_background;
	sf::Texture* tex_overlay;
	sf::Texture* tex_mask;
	sf::RectangleShape test_sprite;

	sf::Music music;
	sf::Font font;
	sf::Text text;
	bool is_font_loaded = false;

	void InitVariables();
	void InitWindow();
	void Init();
	void InitEnemies();
public:
	Game();
	virtual ~Game();

	const bool running() const;

	void PollEvents();
	void UpdateMousePosition();
	void Update();
	void Render();
};