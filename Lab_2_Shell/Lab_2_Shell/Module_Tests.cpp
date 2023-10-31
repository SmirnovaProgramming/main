#include "Module_Tests.h"
#include "Sort.h"
#include "Algorithms_For_Filework.h"

/// <summary>
/// ������� ��� ������������ ������������ ���������� �����
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

	//�������� ������������� ������ �������� ������ � ����� ���������.

	for (int i = 0; i < endpaths.size(); i++) {

		if (!File_Exists(stpaths[i]) || !File_Exists(endpaths[i])) {
			doFilesExist = false;
		}

	}
	//��������� ����� ����������� ������ � ������ ������������� ������.
	if (doFilesExist) {

		for (int i = 0; i < endpaths.size(); i++)
		{
			//����������� ���� ��������� ������.
			//�� ����� ��������� ������ ������ ���-�� �����
			//� ����� ���� ����� ������������ � ����� ���������� �������
			//����� ���� �����������

			file.open(stpaths[i]);
			file >> numofelementsfromfile;

			for (int j = 0; j < numofelementsfromfile; j++) 
			{
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

			for (int f = 0; f < numofelementsfromfile; f++) 
			{
				file >> numberfromfile;
				resvect.push_back(numberfromfile);
			}
			file.close();

			//������ ������ ����������� ����������� �����
			//����� ���������� ������ � ������ ������ ������ ���� �����������

			ShellSort(vect);

			//�������� �������� � ������ � ������ �������. ������ ������ � ����������� �������� ������ ���������.
			for (int c = 0; c < vect.size(); c++) {
				if (vect[c] != resvect[c]) isSortingCorrect = false;
			}

			//������� ������� ����� ��������� ���������
			vect.clear();
			resvect.clear();

		}
		
		if (!isSortingCorrect) { std::cout << "���������� �������� �����������. ��������� ���� ��������." << std::endl; }

		if (isSortingCorrect) { std::cout << "������� �������� ���������. ���� ��������." << std::endl; }

	}

	else {std::cout << "�� ���������� ������ ��� ���������� ��������� ������! ����� ������ ����������: ��������� ������ - A-E, �������� - A1-E1 " << std::endl;}
}
