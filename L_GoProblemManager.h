#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include "tinyxml2.h"
#include "L_GoProblemCollection.h"
#include "bnu.h"

class L_GoProblemManager {
public:
	std::vector<L_GoProblemCollection> collections;

	void ReadAllFiles();
	L_GoProblemCollection GetCollection(std::string p_collection_name);
	std::vector<std::string> GetCollectionNames(int level, int collection_per_page, int page);
	bool HaveCollectionsWithLevel(int level);
	int GetNumCollectionOfLevel(int level);
private:
	void ProcessFile(std::string p_path);
};

