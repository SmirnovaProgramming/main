#include "Module_Tests.h"
#include "Sort.h"
#include "Algorithms_For_Filework.h"

/// <summary>
/// Функция для тестирования корректности сортировки Шелла
/// </summary>
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
				if (vect[c] != resvect[c]) Is_Sorting_Correct = false;
			}

			//Очищаем векторы перед следующей итерацией
			vect.clear();
			resvect.clear();

		}
		
		if (!Is_Sorting_Correct) { std::cout << "Сортировка работает некорректно. Модульный тест завершён." << std::endl; }

		if (Is_Sorting_Correct) { std::cout << "Задание работает корректно. Тест завершён." << std::endl; }

	}

	else {std::cout << "Не обнаружено файлов для проведения модульных тестов! Файлы должны называться: начальные данные - A-E, конечные - A1-E1 " << std::endl;}
}
