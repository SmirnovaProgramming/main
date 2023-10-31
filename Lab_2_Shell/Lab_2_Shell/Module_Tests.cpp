#include "Module_Tests.h"
#include "Sort.h"
#include "Algorithms_For_Filework.h"

/// <summary>
/// Функция для тестирования корректности сортировки Шелла
/// </summary>
void Module_Tests() {

	std::vector<int> vect;
	std::vector<int> resvect;
	bool isSortingCorrect = true;
	bool doFilesExist = true;
	int numberfromfile = 0;
	int numofelementsfromfile = 0;
	std::string path;
	std::string filename;
	std::ifstream file;
	std::vector<std::string> stpaths{ "..\\Lab_2_Shell\\test_files\\A.txt", "..\\Lab_2_Shell\\test_files\\B.txt", "..\\Lab_2_Shell\\test_files\\C.txt", 
									"..\\Lab_2_Shell\\test_files\\D.txt", "..\\Lab_2_Shell\\test_files\\E.txt" };
	
	std::vector<std::string> endpaths{ "..\\Lab_2_Shell\\test_files\\A1.txt", "..\\Lab_2_Shell\\test_files\\B1.txt", "..\\Lab_2_Shell\\test_files\\C1.txt",
									"..\\Lab_2_Shell\\test_files\\D1.txt", "..\\Lab_2_Shell\\test_files\\E1.txt" };

	//Проверка существования файлов тестовых данных в папке программы.

	for (int i = 0; i < endpaths.size(); i++) {

		if (!File_Exists(stpaths[i]) || !File_Exists(endpaths[i])) {
			doFilesExist = false;
		}

	}
	//Модульные тесты выполняются только в случае существования файлов.
	if (doFilesExist) {

		for (int i = 0; i < endpaths.size(); i++)
		{
			//Открывается файл начальных данных.
			//Из файла начальных данных берётся кол-во чисел
			//А затем сами числа записываются в конец начального вектора
			//Затем файл закрывается

			file.open(stpaths[i]);
			file >> numofelementsfromfile;

			for (int j = 0; j < numofelementsfromfile; j++) 
			{
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

			for (int f = 0; f < numofelementsfromfile; f++) 
			{
				file >> numberfromfile;
				resvect.push_back(numberfromfile);
			}
			file.close();

			//Первый вектор сортируется сортировкой Шелла
			//После сортировки первый и второй вектор должны быть идентичными

			ShellSort(vect);

			//Проверка значений в первом и втором векторе. Каждое первое и последующее значения должны совпадать.
			for (int c = 0; c < vect.size(); c++) {
				if (vect[c] != resvect[c]) isSortingCorrect = false;
			}

			//Очищаем векторы перед следующей итерацией
			vect.clear();
			resvect.clear();

		}
		
		if (!isSortingCorrect) { std::cout << "Сортировка работает некорректно. Модульный тест завершён." << std::endl; }

		if (isSortingCorrect) { std::cout << "Задание работает корректно. Тест завершён." << std::endl; }

	}

	else {std::cout << "Не обнаружено файлов для проведения модульных тестов! Файлы должны называться: начальные данные - A-E, конечные - A1-E1 " << std::endl;}
}
