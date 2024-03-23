#pragma once
#include <iostream>

class L_SaveLoadElement {
public:
	bool LoadFromFile(std::string filename);

	std::string GetState() const { return state; };
	int GetTimestamp() const { return timestamp; };
	std::wstring GetName() const { return name; };
	std::wstring GetMessage() const { return message; };
	std::string GetBackground() const { return background; };
	std::string GetPreviewData() const { return preview_data; };
private:
	std::string state;
	int timestamp = 0;
	std::wstring name;
	std::wstring message;
	std::string background;
	std::string preview_data;
};

