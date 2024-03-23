#include "L_Block.h"
using namespace std;

void L_Block::SetWindow(sf::RenderWindow* p_window) {
	window = p_window;
}

void L_Block::Click() { 
	
}

void L_Block::MouseMove(float mouse_world_x, float mouse_world_y) {

}

void L_Block::MouseDown(sf::Event p_event, game_state clicked_state) {

}

void L_Block::MouseUp(sf::Event p_event, game_state clicked_state) 
{
}

void L_Block::SetActive(bool p_active) {
	active = p_active;
}

void L_Block::Update() {

}

void L_Block::UpdateLanguage() {

}

void L_Block::UpdateScale() {
	if (window != nullptr) {
		scale_x = window->getSize().x / 1920.0f;
		scale_y = window->getSize().y / 1080.0f;
	}
}

void L_Block::Render() {

}

void L_Block::Resize() {

}