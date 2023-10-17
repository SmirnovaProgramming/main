#include "User_Interface.h"
#include "Input_From_File.h"
#include "Output_Into_File.h"
#include "Sort.h"

void Module_Tests() {

	std::vector<int> vect;
	std::vector<int> resvect;
	bool Is_Sorting_Correct = true;
	bool Files_Exists = true;
	int numberfromfile = 0;
	int numofelementsfromfile = 0;
	std::string path;
	std::string filename;
	std::ifstream file;
	std::vector<std::string> stpaths{ "A.txt", "B.txt", "C.txt", "D.txt", "E.txt" };
	std::vector<std::string> endpaths{ "A1.txt", "B1.txt", "C1.txt", "D1.txt", "E1.txt" };

	//Проверка существования файлов тестовых данных в папке программы.

	for (int i = 0; i < endpaths.size(); i++) {
		if (!File_Exists(stpaths[i]) || !File_Exists(endpaths[i])) {
			Files_Exists = false;
			std::cout << "HELP GURL" << std::endl;
		}
	}
	//Модульные тесты выполняются только в случае существования файлов.
	if (Files_Exists) {

		for (int i = 0; i < endpaths.size(); i++)
		{
			//Открывается файл начальных данных.
			//Из файла начальных данных берётся кол-во чисел
			//А затем сами числа записываются в конец начального вектора
			//Затем файл закрывается

			file.open(stpaths[i]);
			file >> numofelementsfromfile;
			for (int j = 0; j < numofelementsfromfile; j++) {
				file >> numberfromfile;
				vect.push_back(numberfromfile);
			}
			file.close();

			

			//Открывается файл конечных данных.
			//Из файла конечных данных берётся кол-во чисел
			//А затем сами числа записываются в конец результатирующего вектора
			//Затем файл закрывается

			file.open(endpaths[i]);

			file >> numofelementsfromfile;
			for (int f = 0; f < numofelementsfromfile; f++) {
				file >> numberfromfile;
				resvect.push_back(numberfromfile);
			}
			file.close();

			//Первый вектор сортируется сортировкой Шелла
			//После сортировки первый и второй вектор должны быть идентичными

			ShellSort(vect);

			//Проверка значений в первом и втором векторе. Каждое первое и последующее значения должны совпадать.

			for (int c = 0; c < vect.size(); c++) {
				if (vect[c] != resvect[c]) Is_Sorting_Correct = false;
			}
			//Очищаем векторы перед следующей итерацией
			vect.clear();
			resvect.clear();

		}
		if (!Is_Sorting_Correct) { std::cout << "Сортировка работает некорректно. Модульный тест завершён." << std::endl; }
		if (Is_Sorting_Correct) { std::cout << "Задание работает корректно. Тест завершён." << std::endl;}

	}
	else {

		std::cout << "Не обнаружено файлов для проведения модульных тестов! Файлы должны называться: начальные данные - A-E, конечные - A1-E1 " << std::endl;

	}
}

void Print_Menu()
{
	//Функция выводит начальное меню.
	system("cls");
	std::cout << "Смирнова Светлана 425 группа." << std::endl << "Лабораторная работа №2. Вариант 7." << std::endl;
	std::cout << "Сортировка Шелла/Shellsort." << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Выберите нужный пункт меню:" << std::endl << "1 - Начать работу программы." << std::endl << "2 - Выполнить модульные тесты." << std::endl
		<< "3 - Завершить работу программы" << std::endl << "> ";
}

void Main_Menu()
{
	//Функция реализует главное зацикленное меню
	std::vector <int> vect;
	std::vector <int> copyvect;
	setlocale(LC_ALL, "RU");
	int UserChoise = 0;
	do {
		system("cls"); //очищение консоли
		Print_Menu();
		UserChoise = Check_Int();
		switch (UserChoise) {
		case StartProgramm:
			Input_From_File(vect);
			copyvect = vect; //копируем вектор
			ShellSort(copyvect); //сортируем копию

			std::cout << "Исходный вектор: " << std::endl;
			for (int i = 0; i < vect.size(); i++) {
				std::cout << vect[i] << ' ';
			}
			std::cout << std::endl;
			std::cout << "Сортированный вектор: " << std::endl;
			for (int i = 0; i < copyvect.size(); i++) {
				std::cout << copyvect[i] << ' ';
			}
			std::cout << std::endl;

			Output_Into_File(vect, copyvect);
			break;
		case StartModuleTests:
			Module_Tests();
			break;
		case StopProgramm:
			break;
		default:
			std::cout << "Такого пункта нет в меню, попробуйте еще раз" << std::endl;
			break;
		}
		if (UserChoise != StopProgramm)	system("pause");
	} while (UserChoise != StopProgramm);
}
