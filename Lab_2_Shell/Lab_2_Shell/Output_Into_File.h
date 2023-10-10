#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <io.h>
#include <limits>
#include <vector>

enum SaveListMenu {
	Save = 1,
	ContinueWithoutSaving = 2
};

enum SaveMethod {
	RewriteFile = 1,
	WriteToTheEndOfTheFile = 2,
	SelectAnotherFile = 3
};

enum CreatingAFile {
	CreateFile = 1,
	ContunueWithoutCreatingFile = 2
};

void Output_Into_File(std::vector<int>& vect, std::vector<int>& vect2);