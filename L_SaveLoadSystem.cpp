#include "L_SaveLoadSystem.h"

void L_SaveLoadSystem::SaveGame(L_Scene& scene)
{
}

void L_SaveLoadSystem::ReadSavesFolder() {
	saves.clear();

	std::string path = "saves/";
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (!entry.is_directory()) {
			if (entry.path().extension().string() == ".xml") {
				saves.push_back({});
				auto& new_element = saves.back();
				if (!new_element.LoadFromFile(entry.path().filename().string())) {
					saves.pop_back();
				}
			}
		}
	}
	return;
}
