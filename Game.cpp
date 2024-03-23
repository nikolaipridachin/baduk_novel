#include "Game.h"
using namespace std;

void Game::InitVariables() {
	this->window = nullptr;

	texture = new sf::Texture();
	tex_background = new sf::Texture();
	tex_overlay = new sf::Texture();
	tex_mask = new sf::Texture();

	if (!texture->loadFromFile("Content/ui/menu_background.jpg")) {
		// Error loading texture
	}
	if (!tex_background->loadFromFile("Content/bg/camp_outside.jpg")) {
		// Error loading texture
	}
	if (!tex_overlay->loadFromFile("Content/bg/peacful_place.jpg")) {
		// Error loading texture
	}
	if (!tex_mask->loadFromFile("Content/ui/transition_effects/left_right.jpg")) {
		// Error loading texture
	}
	//font = make_shared<sf::Font>();
	//text = make_shared<sf::Text>();
	if (!font.loadFromFile("Content/ui/fonts/neucha.ttf"))
	{
		// Error loading font
	}
	else {
		is_font_loaded = true;
		text.setFont(font);
		text.setString(L"Ishi no Ki (»шиноки)");
		text.setCharacterSize(36);
		text.setFillColor(sf::Color::White);
		text.setPosition(500.0f, 10.0f);
	}

	if (!shader.loadFromFile("Content/ui/shaders/fragment_shader.frag", sf::Shader::Fragment)) {
		// error...
	}
}

void Game::InitWindow() {
	video_mode.width = 1600;
	video_mode.height = 900;
	window = make_unique<sf::RenderWindow>(video_mode, "Ishi no Ki", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(120);
	auto desktop = sf::VideoMode::getDesktopMode();
	window->setPosition(sf::Vector2i(desktop.width / 2 - window->getSize().x / 2, desktop.height / 2 - window->getSize().y / 2 - 37));
}

void Game::Init() {
	InitVariables();
	InitWindow();
	InitEnemies();
	;
	baduk_novel.Init(window.get());
	;
}

void Game::InitEnemies() {
	enemy.setPosition(0.0f, 0.0f);
	enemy.setSize(sf::Vector2f(800.0f, 450.0f));
	enemy.setTexture(texture);
	enemy.setFillColor(sf::Color::Cyan);

	test_sprite.setPosition(50.0f, 50.0f);
	test_sprite.setSize(sf::Vector2f(700.0f, 350.0f));
	test_sprite.setTexture(tex_background);
	shader.setUniform("main_texture", *tex_overlay);
	shader.setUniform("mask_texture", *tex_mask);
	shader.setUniform("cutoff", 0.5f);
	shader.setUniform("cutoff_range", 0.2f);
}

Game::Game() {
	Init();
}

Game::~Game() {

}

const bool Game::running() const {
	return window->isOpen();
}

void Game::PollEvents() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			baduk_novel.KeyDown(ev.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			baduk_novel.MouseDown(ev);
			break;
		case sf::Event::MouseButtonReleased:
			baduk_novel.MouseUp(ev);
			break;
		}
	}
}

void Game::UpdateMousePosition() {
	mouse_position = sf::Mouse::getPosition(*window);
}

void Game::Update() {
	PollEvents();
	UpdateMousePosition();
	baduk_novel.Update();
}

void Game::Render() {
	window->clear();
	baduk_novel.Render();
	window->display();
}
