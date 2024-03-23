#pragma once
#include "L_Scene.h"
#include "L_SaveLoadElement.h"
#include <vector>

class L_SaveLoadSystem {
public:

	void SaveGame(L_Scene& scene);
	void ReadSavesFolder();
private:
	std::vector<L_SaveLoadElement> saves;
};

