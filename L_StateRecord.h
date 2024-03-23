#pragma once
#include <string>
#include "game_structs.h"

class L_StateRecord {
public:
	void SetState(game_state state);
	void SetName(std::wstring name);
	void SetMessage(std::wstring message);
	void SetBackground(std::string background);
	void SetCharacterInfo(character_info char_info);

	game_state GetState() const { return m_state; };
	std::wstring GetName() const { return m_name; };
	std::wstring GetMessage() const { return m_message; };
	std::string GetBackground() const { return m_background; };
	character_info GetCharacterInfo() const { return m_char_info; };
private:
	game_state m_state;

	std::wstring m_name;
	std::wstring m_message;
	std::string m_background;
	character_info m_char_info;
};

