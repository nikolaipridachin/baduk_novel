#pragma once
#include <vector>
#include "L_Command.h"
#include "baduk_structs.h"

class L_CommandQuestion : public L_Command {
public:
	L_CommandQuestion();
	void AddVariant(QuestionVariant variant_to_add);
	void virtual Do(L_Scene& scene) override;
private:
	std::vector<QuestionVariant> variants;
};

