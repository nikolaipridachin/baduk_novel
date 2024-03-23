#include "L_ScriptSystem.h"

#include "L_CommandSay.h"
#include "L_CommandName.h"
#include "L_CommandShow.h"
#include "L_CommandBackground.h"
#include "L_CommandHidecharacter.h"
#include "L_CommandGoTo.h"
#include "L_CommandQuestion.h"
#include "L_CommandLoad.h"
#include "L_CommandBreak.h"
#include "L_CommandShowBoard.h"
#include "L_CommandGoProblem.h"
#include "L_CommandHideBoard.h"

using namespace std;

void L_ScriptSystem::SetScene(L_Scene* p_scene) {
	scene = p_scene;
}

void L_ScriptSystem::Load(std::string filename, int p_current_step, bool can_process_next, bool step_back) {
	string xml_filename = "Content/story/" + filename + ".xml";
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError load_result = doc.LoadFile(xml_filename.c_str());
    if (load_result != tinyxml2::XML_SUCCESS) {
        // Error: Loading XML file failed
        cout << "Error: Failed to load " << xml_filename << "\n";
        return;
    }

    tinyxml2::XMLElement* story_element = doc.FirstChildElement("story");
    if (story_element == nullptr) {
        // Error: Can't fing story node
        cout << "Error: Can't find story node" << "\n";
        return;
    }
    
    commands.clear();
    marks.clear();
    current_command_id = 0;
    if (step_back) {
        current_command_id--;
    }
    tinyxml2::XMLElement* current_command = story_element->FirstChildElement();
    int processed_command_id = 0;
    while (current_command != nullptr) {
        if (strcmp(current_command->Value(), "s") == 0) {
            std::wstring message = bnu::convert_to_wstring(current_command->GetText());
            commands.push_back(make_unique<L_CommandSay>(message));
        }
        if (strcmp(current_command->Value(), "name") == 0) {
            if (current_command->GetText() == NULL) {
                commands.push_back(make_unique<L_CommandName>(std::wstring()));
            }
            else {
                std::wstring name_to_set = bnu::convert_to_wstring(current_command->GetText());
                commands.push_back(make_unique<L_CommandName>(name_to_set));
            }
        }
        if (strcmp(current_command->Value(), "show") == 0) {
            string name = bnu::extract_string_from_xmlelement(current_command, "name", "");
            string emotion = bnu::extract_string_from_xmlelement(current_command, "emotion", "");
            float pos_left = bnu::extract_float_from_xmlelement(current_command, "position_left", 0.5f);
            float pos_down = bnu::extract_float_from_xmlelement(current_command, "position_down", 0.0f);
            float scale = bnu::extract_float_from_xmlelement(current_command, "scale", 0.5f);
            std::string mode = bnu::extract_string_from_xmlelement(current_command, "mode", "");
            bool show_instantly;
            (strcmp(mode.c_str(), "instantly") == 0) ? show_instantly = true : show_instantly = false;
            commands.push_back(make_unique<L_CommandShow>(name, emotion, pos_left, pos_down, scale, show_instantly));
        }
        if (strcmp(current_command->Value(), "bg") == 0) {
            std::string background = current_command->GetText();
            std::string effect;
            if (current_command->Attribute("effect")) {
                auto attr = current_command->Attribute("effect");
                effect = std::string((current_command->Attribute("effect")));
            }
            commands.push_back(make_unique<L_CommandBackground>(background, effect));
        }
        if (strcmp(current_command->Value(), "hidecharacter") == 0) {
            commands.push_back(make_unique<L_CommandHidecharacter>());
        }
        if (strcmp(current_command->Value(), "mark") == 0) {
            std::string mark_value(current_command->GetText());
            marks[mark_value] = (int)commands.size();
        }
        if (strcmp(current_command->Value(), "load") == 0) {
            std::string filename(current_command->GetText());
            commands.push_back(make_unique<L_CommandLoad>(filename, *this));
        }
        if (strcmp(current_command->Value(), "showboard") == 0) {
            commands.push_back(make_unique<L_CommandShowBoard>());
        }
        if (strcmp(current_command->Value(), "hideboard") == 0) {
            commands.push_back(make_unique<L_CommandHideBoard>());
        }
        if (strcmp(current_command->Value(), "goto") == 0) {
            std::string mark_value(current_command->GetText());
            commands.push_back(make_unique<L_CommandGoTo>(mark_value, *this));
        }
        if (strcmp(current_command->Value(), "break") == 0) {
            commands.push_back(make_unique<L_CommandBreak>());
        }
        if (strcmp(current_command->Value(), "question") == 0) {
            std::unique_ptr<L_CommandQuestion> command_question = std::make_unique<L_CommandQuestion>();
            tinyxml2::XMLElement* cur_variant_element = current_command->FirstChildElement("variant");
            while(cur_variant_element) {
                tinyxml2::XMLElement* variant_text_element = cur_variant_element->FirstChildElement("text");
                tinyxml2::XMLElement* variant_mark_element = cur_variant_element->FirstChildElement("mark");
                if (variant_text_element && variant_mark_element) {
                    std::wstring variant_text = bnu::convert_to_wstring(variant_text_element->GetText());
                    std::string variant_mark = variant_mark_element->GetText();
                    if (!variant_text.empty() && !variant_mark.empty()) {
                        command_question->AddVariant({ variant_text , variant_mark });
                    }
                }
                cur_variant_element = cur_variant_element->NextSiblingElement("variant");
            }
            commands.push_back(std::move(command_question));
        }
        if (strcmp(current_command->Value(), "goproblem") == 0) {
            std::unique_ptr<L_CommandGoProblem> command_go_problem = std::make_unique<L_CommandGoProblem>();

            tinyxml2::XMLElement* internal_element = current_command->FirstChildElement();
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
                if (strcmp(internal_element->Name(), "task") == 0) {
                    std::wstring task_to_insert = bnu::convert_to_wstring(internal_element->GetText());
                    problem_to_insert.SetTask(task_to_insert);
                }
                if (strcmp(internal_element->Name(), "failcomment") == 0) {
                    std::wstring failcomment_to_insert = bnu::convert_to_wstring(internal_element->GetText());
                    problem_to_insert.SetFailComment(failcomment_to_insert);
                }
                internal_element = internal_element->NextSiblingElement();
            }
            command_go_problem->SetGoProblem(problem_to_insert);
            commands.push_back(std::move(command_go_problem));
        }

        processed_command_id++;
        current_command = current_command->NextSiblingElement();
    }
}

void L_ScriptSystem::ProcessNextCommand() {
    if (current_command_id < commands.size()) {
        bool can_process_next = commands[current_command_id]->can_process_next;
        commands[current_command_id]->Do(*scene);
        current_command_id++;
        if (can_process_next) {
            ProcessNextCommand();
        }
    }
}

bool L_ScriptSystem::GoTo(std::string mark_to_go, bool step_back) {
    for (auto it = marks.begin(); it != marks.end(); ++it) {
        if (it->first == mark_to_go) {
            current_command_id = it->second;
            if (step_back) {
                current_command_id--;
            }
            return true;
        }
    }
    return false;
}
