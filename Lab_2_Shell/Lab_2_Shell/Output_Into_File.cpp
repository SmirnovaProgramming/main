#include "Output_Into_File.h"
#include "Input_From_File.h"

void Output_Into_File(std::vector<int>& vect, std::vector<int>& vect2)
{
	std::string FileName;
	std::ofstream file;
	int SaveChoise = 0;
	int SaveMethod = 0;
	int FileMethod = 0;
	int SaveData = 0;
	do {
		std::cout << "1 - Сохранить в файл." << std::endl << "2 - Продолжить без сохранения." << std::endl << "> ";
		SaveChoise = Check_Int();
		switch (SaveChoise) {
		case Save:
			while (true) {
				std::cout << "Выберите данные для сохранения:" << std::endl << "1 - Сохранить результат выполнения программы." << std::endl << "2 - Сохранить исходные данные." << std::endl << "> ";
				SaveData = Check_Int();
				while (SaveData != 1 && SaveData != 2) {
					std::cout << "Такого пункта меню нету, попробуйте ввести другое число." << std::endl << "> ";
					SaveData = Check_Int();
				}
				std::cout << "Введите путь к файлу для сохранения:" << std::endl << "> ";
				FileName = Read_String_Without_Whitespace();
				while (Is_Reserved_Filename(Get_Filename(FileName)) || Filename_Forbidden_Characters_Check(Get_Filename(FileName)) || !Txt_Check(Get_Filename(FileName))) {
					std::cout << "Недопустимое название или формат файла. Попробуйте еще раз." << std::endl << "> ";
					FileName = Read_String_Without_Whitespace();
				}
				if (File_Exists(FileName)) {
					do {
						std::cout << "Файл уже существует. Выберите режим ввода: " << std::endl << "1 - Перезаписать файл" << std::endl << "2 - Записать в конец файла" << std::endl << "3 - Выбрать другой файл" << std::endl << "> ";
						SaveMethod = Check_Int();
						switch (SaveMethod) {
						case RewriteFile:
							file.open(FileName, std::ios::trunc);
							break;
						case WriteToTheEndOfTheFile:
							file.open(FileName, std::ios::app);
							file << '\n';
							break;
						case SelectAnotherFile:
							break;
						default:
							std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
							break;
						}
					} while (SaveMethod != RewriteFile && SaveMethod != WriteToTheEndOfTheFile && SaveMethod != SelectAnotherFile);
				}
				if (SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || !File_Exists(FileName)) {
					break;
				}
			}
			if (!File_Exists(FileName)) {
				do {
					std::cout << "Файла по данному пути не найдено, хотите создать его?" << std::endl
						<< "1 - Создать файл." << std::endl << "2 - Продолжить без сохранения." << std::endl << "> ";
					FileMethod = Check_Int();
					switch (FileMethod) {
					case CreateFile:
						file.open(FileName);
						break;
					case ContunueWithoutCreatingFile:
						break;
					default:
						std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
						break;
					}
				} while (FileMethod != CreateFile && FileMethod != ContunueWithoutCreatingFile);
			}
			else if (Only_Read(FileName)) {
				std::cout << "Ошибка доступа к файлу. Файл доступен только для чтения." << std::endl;
				break;
			}
			if ((SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || FileMethod == CreateFile) && SaveData == 1) {
				file << "Исходный вектор: " << '\n';
				for (int i = 0; i < vect.size(); i++) {
					file << vect[i] << ' ';
					if (i == vect.size() - 1) file << '\n';
				}
				file << '\n' << "Сортированный вектор:" << '\n';
				for (int i = 0; i < vect2.size(); i++) {
					file << vect2[i] << ' ';
				}
				}
			else if ((SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || FileMethod == CreateFile) && SaveData == 2) {
				file << vect.size() << '\n';
				for (int i = 0; i < vect.size(); i++) {
					for (int i = 0; i < vect.size(); i++) {
						file << vect[i] << ' ';
						if (i == vect.size() - 1) file << '\n';
					}
				}
			}
			file.close();
			break;
		case ContinueWithoutSaving:
			break;
		default:
			std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
			break;
		}
	} while (SaveChoise != Save && SaveChoise != ContinueWithoutSaving);


}
