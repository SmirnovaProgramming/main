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

	//�������� ������������� ������ �������� ������ � ����� ���������.

	for (int i = 0; i < endpaths.size(); i++) {
		if (!File_Exists(stpaths[i]) || !File_Exists(endpaths[i])) {
			Files_Exists = false;
			std::cout << "HELP GURL" << std::endl;
		}
	}
	//��������� ����� ����������� ������ � ������ ������������� ������.
	if (Files_Exists) {

		for (int i = 0; i < endpaths.size(); i++)
		{
			//����������� ���� ��������� ������.
			//�� ����� ��������� ������ ������ ���-�� �����
			//� ����� ���� ����� ������������ � ����� ���������� �������
			//����� ���� �����������

			file.open(stpaths[i]);
			file >> numofelementsfromfile;
			for (int j = 0; j < numofelementsfromfile; j++) {
				file >> numberfromfile;
				vect.push_back(numberfromfile);
			}
			file.close();

			

			//����������� ���� �������� ������.
			//�� ����� �������� ������ ������ ���-�� �����
			//� ����� ���� ����� ������������ � ����� ����������������� �������
			//����� ���� �����������

			file.open(endpaths[i]);

			file >> numofelementsfromfile;
			for (int f = 0; f < numofelementsfromfile; f++) {
				file >> numberfromfile;
				resvect.push_back(numberfromfile);
			}
			file.close();

			//������ ������ ����������� ����������� �����
			//����� ���������� ������ � ������ ������ ������ ���� �����������

			ShellSort(vect);

			//�������� �������� � ������ � ������ �������. ������ ������ � ����������� �������� ������ ���������.

			for (int c = 0; c < vect.size(); c++) {
				if (vect[c] != resvect[c]) Is_Sorting_Correct = false;
			}
			//������� ������� ����� ��������� ���������
			vect.clear();
			resvect.clear();

		}
		if (!Is_Sorting_Correct) { std::cout << "���������� �������� �����������. ��������� ���� ��������." << std::endl; }
		if (Is_Sorting_Correct) { std::cout << "������� �������� ���������. ���� ��������." << std::endl;}

	}
	else {

		std::cout << "�� ���������� ������ ��� ���������� ��������� ������! ����� ������ ����������: ��������� ������ - A-E, �������� - A1-E1 " << std::endl;

	}
}

void Print_Menu()
{
	//������� ������� ��������� ����.
	system("cls");
	std::cout << "�������� �������� 425 ������." << std::endl << "������������ ������ �2. ������� 7." << std::endl;
	std::cout << "���������� �����/Shellsort." << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "�������� ������ ����� ����:" << std::endl << "1 - ������ ������ ���������." << std::endl << "2 - ��������� ��������� �����." << std::endl
		<< "3 - ��������� ������ ���������" << std::endl << "> ";
}

void Main_Menu()
{
	//������� ��������� ������� ����������� ����
	std::vector <int> vect;
	std::vector <int> copyvect;
	setlocale(LC_ALL, "RU");
	int UserChoise = 0;
	do {
		system("cls"); //�������� �������
		Print_Menu();
		UserChoise = Check_Int();
		switch (UserChoise) {
		case StartProgramm:
			Input_From_File(vect);
			copyvect = vect; //�������� ������
			ShellSort(copyvect); //��������� �����

			std::cout << "�������� ������: " << std::endl;
			for (int i = 0; i < vect.size(); i++) {
				std::cout << vect[i] << ' ';
			}
			std::cout << std::endl;
			std::cout << "������������� ������: " << std::endl;
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
			std::cout << "������ ������ ��� � ����, ���������� ��� ���" << std::endl;
			break;
		}
		if (UserChoise != StopProgramm)	system("pause");
	} while (UserChoise != StopProgramm);
}
