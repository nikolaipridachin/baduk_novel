#include "bnu.h"
using namespace std;

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

bool bnu::is_point_in_rect(float mouse_x, float mouse_y, sf::RectangleShape rect) {
    if (mouse_x >= rect.getPosition().x &&
        mouse_y >= rect.getPosition().y &&
        mouse_x <= rect.getPosition().x + rect.getSize().x &&
        mouse_y <= rect.getPosition().y + rect.getSize().y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::wstring bnu::convert_to_wstring(const char* string) {
    std::setlocale(LC_ALL, "en_US.utf8");
    size_t newsize = strlen(string) + 1;
    wchar_t* wcstring = new wchar_t[newsize];

    // Convert char* string to a wchar_t* string.
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, string, _TRUNCATE);
    return wcstring;
}

std::string bnu::extract_string_from_xmlelement(tinyxml2::XMLElement* parent_element, string field_name, string default_value) {
    tinyxml2::XMLElement* target_element = parent_element->FirstChildElement(field_name.c_str());
    if (target_element == nullptr) {
        return default_value;
    }
    else {
        if (target_element->GetText()) {
            return target_element->GetText();
        }
        else {
            return default_value;
        }
    }
}

std::wstring bnu::extract_wstring_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, std::wstring default_value) {
    tinyxml2::XMLElement* target_element = parent_element->FirstChildElement(field_name.c_str());
    if (target_element == nullptr) {
        return default_value;
    }
    else {
        return bnu::convert_to_wstring(target_element->GetText());
    }
}

float bnu::extract_float_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, float default_value) {
    tinyxml2::XMLElement* target_element = parent_element->FirstChildElement(field_name.c_str());
    if (target_element == nullptr) {
        return default_value;
    }
    else {
        float result;
        string data = target_element->GetText();
        std::replace(data.begin(), data.end(), ',', '.');
        try {
            result = stof(data);
        }
        catch (invalid_argument) {
            return default_value;
        }
        catch (out_of_range) {
            return default_value;
        }
        return result;
    }
}

int bnu::extract_int_from_xmlelement(tinyxml2::XMLElement* parent_element, std::string field_name, int default_value) {
    tinyxml2::XMLElement* target_element = parent_element->FirstChildElement(field_name.c_str());
    if (target_element == nullptr) {
        return default_value;
    }
    else {
        int result;
        string data = target_element->GetText();
        std::replace(data.begin(), data.end(), '.', ',');
        try {
            result = stoi(data);
        }
        catch (invalid_argument) {
            return default_value;
        }
        catch (out_of_range) {
            return default_value;
        }
        return result;
    }
}

void bnu::place_text_in_rect(sf::RectangleShape bounding_rect, sf::Text& inside_text) {
    sf::FloatRect text_rect = inside_text.getLocalBounds();
    sf::Vector2f bounding_size = bounding_rect.getSize();
    sf::Vector2f bounding_position = bounding_rect.getPosition();
    float character_size = (float)inside_text.getCharacterSize();
    float pos_x = bounding_position.x + bounding_size.x / 2 - text_rect.width / 2;
    float pos_y = bounding_position.y + bounding_size.y / 2 - character_size * 0.7f;
    inside_text.setOrigin(0.0f, 0.0f);
    inside_text.setPosition(pos_x, pos_y);
}

vector<string> bnu::split_string(string str, char separator) {
    int startIndex = 0, endIndex = 0;
    vector<std::string> result_strings;
    for (int i = 0; i <= str.size(); i++) {
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            result_strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return result_strings;
}

void bnu::extract_coords(string source, int& coord_x, int& coord_y) {
    if (source.empty()) {
        coord_x = -1;
        coord_y = -1;
        return;
    }
    string first = source.substr(0, 1);
    string second = source.substr(1, source.size() - 1);
    coord_x = (int)first[0] - 97;
    coord_y = stoi(second) - 1;
}

bool bnu::extract_coords(std::string source, BadukCoords& coords) {
    string first = source.substr(0, 1);
    string second = source.substr(1, source.size() - 1);
    int coord_x = (int)first[0] - 97;
    int coord_y = stoi(second) - 1;
    if (coord_x < 0 || coord_y < 0) {
        return false;
    }
    else {
        coords.x = coord_x;
        coords.y = coord_y;
        return true;
    }
}

bool bnu::coords_to_string(BadukCoords coords, std::string& result)
{
    if (coords.x < 0 || coords.y < 0) {
        return false;
    }
    char first_character = coords.x + 97;
    std::string first_part;
    first_part += first_character;
    std::string second_part = std::to_string(coords.y + 1);
    result = first_part + second_part;
    return true;
}
