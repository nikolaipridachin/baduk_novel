#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <codecvt>
#include <cstdint> 
#include <iostream>
#include <algorithm>
#include <vector>
#include "tinyxml2.h"
#include <SFML/Graphics.hpp>
#include "baduk_structs.h"

class bnu {
public:
	static bool is_point_in_rect(float mouse_x, float mouse_y, sf::RectangleShape rect);
	static std::wstring convert_to_wstring(const char* source);
	static std::string extract_string_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, std::string default_value);
	static std::wstring extract_wstring_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, std::wstring default_value);
	static float extract_float_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, float default_value);
	static int extract_int_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, int default_value);
	static void place_text_in_rect(sf::RectangleShape bounding_rect, sf::Text& inside_text);
	static std::vector<std::string> split_string(std::string str, char separator);
	static void extract_coords(std::string source, int& coord_x, int& coord_y);
	static bool extract_coords(std::string source, BadukCoords& coords);
	static bool coords_to_string(BadukCoords coords, std::string& result);
};

