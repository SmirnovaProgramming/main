#pragma once

enum PrintMenu {
	StartProgramm = 1,
	StartModuleTests = 2,
	StopProgramm = 3
};

enum InputMethod {
	FromFile = 1,
	ManualMethod = 2,
	RandomMethod = 3,
	ReturnMenu = 4
};

void Print_Menu();
void Main_Menu();
void Module_Tests();