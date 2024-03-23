#include "L_GoProblemManager.h"
using namespace std;
using namespace std::filesystem;

void L_GoProblemManager::ReadAllFiles() {
    string path = "Content\\goproblems";
    for (const auto& entry : directory_iterator(path)) {
        if (!entry.is_directory()) {
            string current_extension = entry.path().extension().string();
            if (current_extension == ".xml") {
                ProcessFile(entry.path().string());
            }
        }
    }
}

L_GoProblemCollection L_GoProblemManager::GetCollection(std::string p_collection_name) {
    for (L_GoProblemCollection cur_collection : collections) {
        if (strcmp(cur_collection.name.c_str(), p_collection_name.c_str()) == 0) {
            return cur_collection;
        }
    }
    return L_GoProblemCollection();
}

vector<string> L_GoProblemManager::GetCollectionNames(int level, int collection_per_page, int page)
{
    vector<string> result;
    int start = (page - 1) * collection_per_page;
    for (int i = start; i < (int)collections.size();i++) {
        if (i > (int)collections.size()) {
            break;
        }
        if (collections[i].level == level && result.size() < collection_per_page) {
            result.push_back(collections[i].name);
            if (result.size() >= collection_per_page) {
                return result;
            }
        }
    }
    return result;
}

bool L_GoProblemManager::HaveCollectionsWithLevel(int level) {
    for (L_GoProblemCollection cur_collection : collections) {
        if (cur_collection.level == level) {
            return true;
        }
    }
    return false;
}

int L_GoProblemManager::GetNumCollectionOfLevel(int level) {
    int counter = 0;
    for (L_GoProblemCollection cur_collection : collections) {
        if (cur_collection.level == level) {
            counter++;
        }
    }
    return counter;
}

void L_GoProblemManager::ProcessFile(std::string p_path) {
    string xml_filename = p_path;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError load_result = doc.LoadFile(xml_filename.c_str());
    if (load_result != tinyxml2::XML_SUCCESS) {
        cout << "Error: Failed to load " << xml_filename << "\n";
        return;
    }

    tinyxml2::XMLElement* gpcollection_element = doc.FirstChildElement("gpcollection");
    if (gpcollection_element == nullptr) {
        cout << "Error: Can't find gpcollection node" << "\n";
        return;
    }

    tinyxml2::XMLElement* current_element = gpcollection_element->FirstChildElement();
    L_GoProblemCollection collection_to_insert;
    while (current_element != nullptr) {
        if (strcmp(current_element->Name(), "metadata") == 0) {
            string name = bnu::extract_string_from_xmlelement(current_element, "name", "");
            int level = bnu::extract_int_from_xmlelement(current_element, "level", 0);
            collection_to_insert.SetName(name);
            collection_to_insert.SetLevel(level);
        }
        if (strcmp(current_element->Name(), "goproblem") == 0) {
            tinyxml2::XMLElement* internal_element = current_element->FirstChildElement();
            L_GoProblem problem_to_insert;
            while (internal_element != nullptr) {
                if (strcmp(internal_element->Name(), "diagram") == 0) {
                    string black_stones = bnu::extract_string_from_xmlelement(internal_element, "black", "");
                    string white_stones = bnu::extract_string_from_xmlelement(internal_element, "white", "");
                    problem_to_insert.SetBlackStones(black_stones);
                    problem_to_insert.SetWhiteStones(white_stones);
                }
                if (strcmp(internal_element->Name(), "branch") == 0) {
                    string moves = bnu::extract_string_from_xmlelement(internal_element, "moves", "");
                    string result = bnu::extract_string_from_xmlelement(internal_element, "result", "");
                    problem_to_insert.AddBranch(moves, result);
                }
                internal_element = internal_element->NextSiblingElement();
            }
            collection_to_insert.AddGoProblem(problem_to_insert);
        }
        current_element = current_element->NextSiblingElement();
    }
    collections.push_back(collection_to_insert);
}
