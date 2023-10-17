#include "Input_From_File.h"

std::string Read_String_Without_Whitespace() {
	std::string input; //переменная для хранения пользовательского ввода
	while (true) {
		std::getline(std::cin, input); //ввод строки
		std::istringstream iss(input); //копирование строки в input в переменную iss, в которой хранится строка без пробелов
									   //будут введены все символы до первого пробела.
		if (iss >> input && !isspace(input[0])) { //перемещаем значение iss в input и проверяем не идёт ли первым символом
			return input;                         //в input пробел. Если пробела нет, то возвращаем input, завершаем работу фукнции
		} 
		else {
			std::cout << "Ошибка: входные данные не должны содержать пробелов. Повторите попытку ввода." << std::endl; //если пробел есть,
		} //возвращаем сообщение об ошибке.
	}
}

int Check_Int() {
	int tmp = 0;
	std::cin >> tmp; //Ввод значения в целочисленную переменную
	while (std::cin.fail() || tmp < 0) { //Если будет введено не целочисленное значение, то поток ввода проставит
		std::cout << "Введено некорректное значение, попробуйте еще раз: "; //флаг ошибки как 1, по которому проверяется 
		std::cin.clear(); //Правильность типа введённого значения. Затем мы снимаем флаг
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //очищаем буфер
		std::cin >> tmp; //вновь вводим значение
	}
	std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n'); //очищаем буфер
	return tmp;
}

bool File_Exists(std::string FileName) //Функция возвращает true или false в зависимости от того
{									   //существует файл или нет.
	const char* path = FileName.c_str(); //присваиваем значение переменной нуль-терминированной строки
										 //Для того, чтобы избежать непредвиденного чтения другой памяти.
	if (!_access(path, 0)) //проверяем режим доступа к файлу. Функция возвращает -1, если у файла другой режим.  
		return true;

	else
		return false;
}

bool Only_Read(std::string FileName) { //Функция возвращает true или false в зависимости от того
	const char* path = FileName.c_str();//Доступен ли файл только для чтения.
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
	//Зарезервированные имена используются системой для названия портов или контроллеров, их нельзя использовать
	//Как названия файлов.
	size_t pos = FileName.find_first_of("."); //Находим положение точки в названии файла
	if (pos != std::string::npos) { //Если в имени файла есть точка
		FileName = FileName.substr(0, pos); //То мы отбрасываем формат файла, чтоб оставить только название
	}

	for (int i = 0; i < Quantity_Reserved_Names; i++) { //В цикле проверяем название файла
		if (_stricmp(FileName.c_str(), Reserved_Names[i].c_str()) == 0) { //со списком запрещённых названий
			return true; //Если названия совпадают, то возвращается ноль, а функция возвращает true
		} //что значит, что название файла - зарезервированное
	}
	return false; //Если название незарезервированное, то возвращается false
}

bool Txt_Check(const std::string& filename) {
	std::string extension = ".txt";
	size_t strLength = filename.length(); //длина передаваемого названия файла
	size_t extLength = extension.length(); //длина .txt

	if (strLength < extLength) { //если длина названия файла меньше, чем .txt
		std::cout << "Файл должен быть текстового расширения." << std::endl; //то можно предположить, что
		return false; //файл не текстового расширения.
	}
	if (strLength == extLength) { //Если длины равны, то можно предположить,
		std::cout << "Пустой формат файла!" << std::endl; //что пользователь ввёл только название.
		return false;
	}

	std::string end = filename.substr(strLength - extLength, extLength); //возвращаем концовку названия файла,
	//которая начинается с позиции длина строки минус длина формата,
	//и берём столько символов на концовку, сколько требует длина .txt

	return end.compare(extension) == 0; //возвращаем значение сравнения .txt и концовки файла. Когда они идентичны
	//функция возвращает 0.
	//сравнение значения 0 с 0 вернёт 1
}

bool Filename_Forbidden_Characters_Check(const std::string& filename) {//проверка названия на запрещённые символы
	const int Quantity_Forbidden_Characters = 9;
	std::string Reserved_Characters[Quantity_Forbidden_Characters] = { "/", "\\", "|", ":", "*", "?", "\"", "<", ">" };

	for (int i = 0; i < Quantity_Forbidden_Characters; i++) { //в цикле находим позицию запрещённого символа в переданном параметре
		if (filename.find(Reserved_Characters[i]) != std::string::npos) { //Если позиция будет найдена
			return true; //возвращаем true
		}
	}
	return false; //если запрещённых символов не найдено в названии файла возвращаем false
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
	bool Path_Is_Correct = false; //флаг проверки корректности введённого пути
	bool File_Is_Correct = true; //флаг проверки корректности файла
	int elements = 0; //кол-во элементов, которые будут переданы в вектор
	int intTmp; //переменная для временного хранения элемента из файла
	std::string path; 
	std::string filename;
	std::ifstream file; //переменная для открытия файла и записи из него
	do{
	std::cout << "Введите путь файла:" << std::endl << "> ";
	path = Read_String_Without_Whitespace(); //читаем введённый путь без пробелов.
	while (!Path_Is_Correct) {
		//проверяем существует ли файл, введено ли имя с запрещёнными символами или введён ли формат пустой или отличный от .txt
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
	file.open(path); //открываем файл
	std::cout << "Файл успешно открыт!" << std::endl;
	if (file.peek() == std::ifstream::traits_type::eof()) { //peek() возвращает либо следующий символ в файловом потоке
															//либо EOF. Если следующий символ сразу после открытия файла
															//является EOF, то можно заключить, что файл пуст
															//и начать цикл заново после сообщения об ошибке.
		std::cout << "Файл пуст. Заполните файл и попробуйте еще раз." << std::endl;
	}
	else {
		while (!file.eof()) { //Проверяем тип значений в файле, пока не дойдём до EOF.
			file >> intTmp;
			if (file.fail()) { //Если тип переданного значения не соответсвует типу переменной, то
				file.clear(); //будет проставлен флаг ошибки как 1. Очищаем все флаги
				File_Is_Correct = false; //И проставляем свой собственный флаг проверки корректности файла как false
				break;
			}
		}
		file.clear();
		file.seekg(0); //Переставляем курсор в начало файла после проверки всех значений.

		if (File_Is_Correct) { //Заполняем вектор значениями, если файл корректный.

			file >> elements; //Берём кол-во элементов из файла.
		
			for (int i = 0; i < elements; i++) {
				file >> intTmp;
				vect.push_back(intTmp);
			}
		
		}

		if (!File_Is_Correct) { //Если файл некорректный, то возвращаем сообщение об ошибке и закрываем файл.
			std::cout << "В файле содержится некорректно заполненный массив. Исправьте файл и попробуйте еще раз." << std::endl;
			file.close();
		}
	}
	file.close();
	} while (!File_Is_Correct); //В цикле вводится путь файла до тех пор, пока введённый файл не окажется корректно заполненным
}