#pragma once
#include <iostream>
#include <map>
#include "tinyxml2.h"
#include "bnu.h"

class L_Localization {
public:
	std::string lang;
	void Init(std::string p_lang);
	std::string Get(std::string param);
	std::wstring GetW(std::string param);
private:
	std::map<std::string, std::string> data;
};

