#pragma once
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "L_Block.h"

enum background_state {
	Normal, Animating
};

class L_BlockBackground : public L_Block {
public:
	background_state state = background_state::Normal;
	std::function<void()> action_animation_finished;

	void Init(sf::RenderWindow* p_window);
	void Render() override;
	void Update() override;
	void Resize() override;
	void Set(std::string param, std::string m_effect = "");
	void BreakAnimation();

	std::string GetBackgroundName() const { return background_texture_filename; };
private:
	float m_cutoff = 1.0f;
	sf::Shader m_shader_transition;
	std::unique_ptr<sf::Texture> tex_mask;

	std::string background_texture_filename;

	std::unique_ptr<sf::RectangleShape> sprite_background;
	std::unique_ptr<sf::Texture> tex_background;

	std::unique_ptr<sf::RectangleShape> sprite_overlay;
	std::unique_ptr<sf::Texture> tex_overlay;

};

