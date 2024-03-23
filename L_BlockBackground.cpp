#include "L_BlockBackground.h"
using namespace std;

void L_BlockBackground::Init(sf::RenderWindow* p_window) {
	window = p_window;

	tex_background.reset();
	tex_background = make_unique<sf::Texture>();
	if (!tex_background->loadFromFile("Content/ui/black.jpg")) {
		cout << "Error loading background black texture";
	}

	sprite_background = make_unique<sf::RectangleShape>();
	sprite_background->setTexture(tex_background.get());
	sprite_background->setPosition(0.0f, 0.0f);

	tex_overlay = make_unique<sf::Texture>();
	if (!tex_overlay->loadFromFile("Content/bg/dzen.jpg")) {
		cout << "Error loading overlay background black texture";
	}

	sprite_overlay = make_unique<sf::RectangleShape>();
	sprite_overlay->setTexture(tex_overlay.get());
	sprite_overlay->setPosition(0.0f, 0.0f);

	if (!m_shader_transition.loadFromFile("Content/ui/shaders/fragment_shader.frag", sf::Shader::Fragment)) {
		std::cout << "Error liading transition shader" << std::endl;
	}

	tex_mask = make_unique<sf::Texture>();
	if (!tex_mask->loadFromFile("Content/ui/transition_effects/left_right.jpg")) {
		std::cout << "Error liading mask texture" << std::endl;
	}

	m_shader_transition.setUniform("main_texture", *tex_overlay);
	m_shader_transition.setUniform("mask_texture", *tex_mask);
	m_shader_transition.setUniform("cutoff", m_cutoff);
	m_shader_transition.setUniform("cutoff_range", 0.2f);

	Resize();
}

void L_BlockBackground::Render() {
	window->draw(*sprite_background);
	window->draw(*sprite_overlay, &m_shader_transition);
}

void L_BlockBackground::Update() {
	if (state == background_state::Animating) {
		m_cutoff -= 0.01f;
		m_shader_transition.setUniform("cutoff", m_cutoff);
		if (m_cutoff < 0.0f) {
			tex_background = std::make_unique<sf::Texture>();
			if (!tex_background->loadFromFile(background_texture_filename)) {
				cout << "Error loading overlay background black texture:" << background_texture_filename << "\n";
			}
			sprite_background = make_unique<sf::RectangleShape>();
			sprite_background->setTexture(tex_background.get());
			state = background_state::Normal;
			Resize();
			action_animation_finished();
		}
		return;
	}
}

void L_BlockBackground::Resize() {
	UpdateScale();
	sprite_background->setPosition(0.0f, 0.0f);
	sprite_background->setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	sprite_overlay->setPosition(0.0f, 0.0f);
	sprite_overlay->setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
}

void L_BlockBackground::Set(std::string param, std::string m_effect) {
	if (m_effect.empty()) {
		background_texture_filename = param;
		tex_background.reset();
		tex_background = make_unique<sf::Texture>();
		if (!tex_background->loadFromFile(background_texture_filename)) {
			// Error loading new texture
			cout << "Error: failed to load background texture - " << param << "\n";
		}
		sprite_background.reset();
		sprite_background = make_unique<sf::RectangleShape>();
		sprite_background->setTexture(tex_background.get());

		tex_overlay = make_unique<sf::Texture>();
		if (!tex_overlay->loadFromFile(background_texture_filename)) {
			cout << "Error loading overlay background black texture";
		}

		m_cutoff = 1.0f;
		m_shader_transition.setUniform("cutoff", m_cutoff);

		Resize();
	}
	else {
		background_texture_filename = param;
		tex_mask = make_unique<sf::Texture>();
		if (!tex_mask->loadFromFile("Content/ui/transition_effects/" + m_effect + ".jpg")) {
			std::cout << "Error loading mask texture" << std::endl;
		}
		tex_mask->setSmooth(true);
		tex_overlay = make_unique<sf::Texture>();
		if (!tex_overlay->loadFromFile(background_texture_filename)) {
			cout << "Error loading overlay background black texture";
		}
		
		m_shader_transition.setUniform("main_texture", *tex_overlay);
		m_shader_transition.setUniform("mask_texture", *tex_mask);
		m_cutoff = 1.0f;
		m_shader_transition.setUniform("cutoff", m_cutoff);

		sprite_overlay = make_unique<sf::RectangleShape>();
		sprite_overlay->setTexture(tex_overlay.get());
		Resize();

		state = background_state::Animating;
	}
}

void L_BlockBackground::BreakAnimation() {
	state = background_state::Normal;
}
