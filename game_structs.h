#pragma once

enum game_state {
	None, MainMenu, Settings, Gameplay, Question,
	Smartphone, BadukTop, ContextMenu, Board, ViewBackground, SaveGame,
	LoadGame
};

enum baduktop_state {
	MainScreen, SelectProblem, Solving
};

enum problem_state {
	NotInProblem, MakingMove, WaitingForAnswer, WatchingCorrectSolution, WatchingWrongSolution
};

struct character_info {
	std::string name;
	std::string emotion; 
	float pos_left; 
	float pos_down; 
	float scale; 
};