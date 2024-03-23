#include "L_StateRecord.h"

void L_StateRecord::SetState(game_state state) {
	m_state = state;
}

void L_StateRecord::SetName(std::wstring name) {
	m_name = name;
}

void L_StateRecord::SetMessage(std::wstring message) {
	m_message = message;
}

void L_StateRecord::SetBackground(std::string background) {
	m_background = background;
}

void L_StateRecord::SetCharacterInfo(character_info char_info) {
	m_char_info = char_info;
}
