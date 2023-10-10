#include "Input_From_File.h"

std::string Read_String_Without_Whitespace() {
	std::string input;
	while (true) {
		std::getline(std::cin, input);
		std::istringstream iss(input);
		if (iss >> input && !isspace(input[0])) {
			return input;
		}
		else {
			std::cout << "Ошибка: входные данные не должны содержать пробелов. Повторите попытку ввода." << std::endl;
		}
	}
}

int Check_Int() {
	int tmp = 0;
	std::cin >> tmp;
	while (std::cin.fail() || tmp < 0) {
		std::cout << "Введено некорректное значение, попробуйте еще раз: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> tmp;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
	return tmp;
}

bool File_Exists(std::string FileName)
{
	const char* path = FileName.c_str();
	if (!_access(path, 0))
		return true;

	else
		return false;
}

bool Only_Read(std::string FileName) {
	const char* path = FileName.c_str();
	if (_access(path, 2) == -1) {
		return true;
	}
	else
		return false;
}

bool Is_Reserved_Filename(std::string FileName) {
	const int Quantity_Reserved_Names = 22;
	std::string Reserved_Names[Quantity_Reserved_Names] = { "con", "prn" , "aux" , "nul" , "com1" , "com2" , "com3" , "com4" , "com5" , "com6" , "com7" , "com8" , "com9" ,
	"lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9" };

	size_t pos = FileName.find_first_of(".");
	if (pos != std::string::npos) {
		FileName = FileName.substr(0, pos);
	}

	for (int i = 0; i < Quantity_Reserved_Names; i++) {
		if (_stricmp(FileName.c_str(), Reserved_Names[i].c_str()) == 0) {
			return true;
		}
	}
	return false;
}

bool Txt_Check(const std::string& filename) {
	std::string extension = ".txt";
	size_t strLength = filename.length();
	size_t extLength = extension.length();

	if (strLength < extLength) {
		std::cout << "Файл должен быть текстового расширения." << std::endl;
		return false;
	}
	if (strLength == extLength) {
		std::cout << "Пустой формат файла!" << std::endl;
		return false;
	}

	std::string end = filename.substr(strLength - extLength, extLength);

	return end.compare(extension) == 0;
}

bool Filename_Forbidden_Characters_Check(const std::string& filename) {
	const int Quantity_Forbidden_Characters = 9;
	std::string Reserved_Characters[Quantity_Forbidden_Characters] = { "/", "\\", "|", ":", "*", "?", "\"", "<", ">" };

	for (int i = 0; i < Quantity_Forbidden_Characters; i++) {
		if (filename.find(Reserved_Characters[i]) != std::string::npos) {
			return true;
		}
	}
	return false;
}


std::string Get_Filename(const std::string& path) {
	size_t pos = path.find_last_of("\\"); // Ищем последний символ '/' или '\'
	if (pos != std::string::npos) { // Если символ найден
		return path.substr(pos + 1); // Возвращаем имя файла после найденного символа
	}
	return path; // Если символ не найден, возвращаем исходный путь
}

void Input_From_File(std::vector<int>& vect)
{
	bool Path_Is_Correct = false;
	bool File_Is_Correct = true;
	int elements = 0;
	int input = 0;
	int intTmp;
	std::string temp;
	std::string path;
	std::string filename;
	int* tmp = nullptr;
	std::ifstream file;
	do{
	std::cout << "Введите путь файла:" << std::endl << "> ";
	path = Read_String_Without_Whitespace();
	while (!Path_Is_Correct) {
		if (!File_Exists(path)) {
			std::cout << "Файл не существует, попробуйте ввести другой путь." << std::endl;
			std::cout << "Введите путь:";
			path = Read_String_Without_Whitespace();
			continue;
		}
		filename = Get_Filename(path);
		if (!Txt_Check(filename)) {
			std::cout << "Введите другой путь:";
			std::cin >> path;
			continue;
		};
		if (Filename_Forbidden_Characters_Check(filename)) {
			std::cout << "В имени файла не должно содержаться недопустимых символов." << std::endl;
			std::cout << "Введите другой путь:";
			std::cin >> path;
			continue;
		};
		Path_Is_Correct = true;
	}
	filename = Get_Filename(path);
	file.open(path);
	std::cout << "Файл успешно открыт!" << std::endl;
	if (file.peek() == std::ifstream::traits_type::eof()) {
		std::cout << "Файл пуст. Заполните файл и попробуйте еще раз." << std::endl;
	}
	else {
		while (!file.eof()) {
			file >> intTmp;
			if (file.fail()) {
				file.clear();
				File_Is_Correct = false;
				break;
			}
		}
		file.clear();
		file.seekg(0);

		if (File_Is_Correct) {

			file >> elements;
		
			for (int i = 0; i < elements; i++) {
				file >> intTmp;
				vect.push_back(intTmp);
			}
		
		}

		if (!File_Is_Correct) {
			std::cout << "В файле содержится некорректно заполненный массив. Исправьте файл и попробуйте еще раз." << std::endl;
			file.close();
		}
	}
	file.close();
	} while (!File_Is_Correct);
}