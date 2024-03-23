#include "L_Localization.h"
using namespace std;

void L_Localization::Init(std::string p_lang) {
    string xml_filename = "Content/ui/localization/" + p_lang + ".xml";
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError load_result = doc.LoadFile(xml_filename.c_str());
    if (load_result != tinyxml2::XML_SUCCESS) {
        // Error: Loading XML file failed
        cout << "Error: Failed to load " << xml_filename << "\n";
        return;
    }

    tinyxml2::XMLElement* story_element = doc.FirstChildElement("localization");
    if (story_element == nullptr) {
        // Error: Can't fing localization node
        cout << "Error: Can't find story node" << "\n";
        return;
    }

    lang = p_lang;
    data.clear();
    tinyxml2::XMLElement* current_row = story_element->FirstChildElement();
    int while_counter = 0;
    while (current_row != nullptr && while_counter < 10000) {
        while_counter++;
        const tinyxml2::XMLAttribute* name_attribute = current_row->FindAttribute("name");
        if (name_attribute != nullptr) {
            string index = name_attribute->Value();
            string value = current_row->GetText();
            data[index] = value;
        }
        current_row = current_row->NextSiblingElement();
    }
}

std::string L_Localization::Get(std::string param) {
    if (data.find(param) == data.end()) {
        return data[param];
    }
    else {
        return "";
    }
}

std::wstring L_Localization::GetW(std::string param)
{
    if (data.find(param) == data.end()) {
        return L"";
    }
    else {
        string value = data[param];
        wstring result = bnu::convert_to_wstring(value.c_str());
        return result;
    }
}
