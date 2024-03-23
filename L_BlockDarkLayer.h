#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "L_Block.h"

class L_BlockDarkLayer : public L_Block {
public:
	std::unique_ptr<sf::RectangleShape> sprite_background;
	std::unique_ptr<sf::Texture> tex_background;
	sf::Image image_background;
	sf::Color main_color;

	void Init(sf::RenderWindow* p_window);
	void Render() override;
	void Update() override;
	void Resize() override;
	void SetOpacity(float param);
private:
	float opacity;
	void UpdateOpacity();
};

