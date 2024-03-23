#include "L_BlockDarkLayer.h"
using namespace std;

void L_BlockDarkLayer::Init(sf::RenderWindow* p_window) {
	window = p_window;
	SetOpacity(0.4f);
	tex_background.reset();
	tex_background = make_unique<sf::Texture>();
	if (!tex_background->loadFromFile("Content/ui/black.jpg")) {
		cout << "Error loading dark layer texture";
	}
	sprite_background = make_unique<sf::RectangleShape>();
	sprite_background->setTexture(tex_background.get());
	sprite_background->setPosition(0.0f, 0.0f);
}

void L_BlockDarkLayer::Render() {
	window->draw(*sprite_background);
}

void L_BlockDarkLayer::Update() {

}

void L_BlockDarkLayer::Resize() {
	sprite_background->setPosition(0.0f, 0.0f);
	sprite_background->setSize(sf::Vector2f(1920.0f * scale_x, 1080.0f * scale_y));
	UpdateOpacity();
}

void L_BlockDarkLayer::SetOpacity(float param) {
	opacity = param;
	if(opacity < 0.0f) {
		opacity = 0.0f;
	}
	if (opacity > 1.0f) {
		opacity = 1.0f;
	}
	main_color = sf::Color(255, 255, 255, (int)(opacity * 255));
	if (sprite_background != nullptr) {
		sprite_background->setFillColor(main_color);
	}
}

void L_BlockDarkLayer::UpdateOpacity() {
	SetOpacity(opacity);
}
