#include "L_SaveLoadElement.h"

#include "tinyxml2.h"
#include "bnu.h"

bool L_SaveLoadElement::LoadFromFile(std::string filename) {
    std::string xml_filename = "saves/" + filename;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError load_result = doc.LoadFile(xml_filename.c_str());
    if (load_result != tinyxml2::XML_SUCCESS) {
        std::cout << "Error: Failed to load " << xml_filename << std::endl;
        return false;
    }

    tinyxml2::XMLElement* savedata_element = doc.FirstChildElement("savedata");

    tinyxml2::XMLElement* element_common = savedata_element->FirstChildElement("common");
    tinyxml2::XMLElement* element_scene = savedata_element->FirstChildElement("scene");
    tinyxml2::XMLElement* element_preview = savedata_element->FirstChildElement("preview");

    if (element_common == nullptr || element_scene == nullptr || element_preview == nullptr) {
        std::cout << "Error: One of base elements not found" << std::endl;
        return false;
    }

    tinyxml2::XMLElement* element_timestamp = element_common->FirstChildElement("timestamp");
    timestamp = bnu::extract_int_from_xmlelement(element_common, "timestamp", 0);
    if (timestamp == 0) {
        std::cout << "Error: Timestamp not found" << std::endl;
        return false;
    }
    preview_data = bnu::extract_string_from_xmlelement(element_preview, "base64", std::string());
    if (preview_data.empty()) {
        std::cout << "Error: Preview data not found" << std::endl;
        return false;
    }
    state = bnu::extract_string_from_xmlelement(element_scene, "state", std::string());
    background = bnu::extract_string_from_xmlelement(element_scene, "background", std::string());
    name = bnu::extract_wstring_from_xmlelement(element_scene, "name", std::wstring());
    message = bnu::extract_wstring_from_xmlelement(element_scene, "message", std::wstring());

    return true;
}
