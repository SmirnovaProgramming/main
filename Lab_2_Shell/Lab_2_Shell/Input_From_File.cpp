#include "Input_From_File.h"
#include "Algorithms_For_Filework.h"
/// <summary>
/// ������� ��� ����� �������� ������� �� �����
/// </summary>
/// <param name="vect"> ������, ����������� ���������� �� ����� </param>
void Input_From_File(std::vector<int>& vect)
{
	bool Path_Is_Correct = false; //���� �������� ������������ ��������� ���� 
	bool File_Is_Correct = true; //���� �������� ������������ �����
	int elements = 0; //���-�� ���������, ������� ����� �������� � ������
	int intTmp; //���������� ��� ���������� �������� �������� �� �����
	std::string path; 
	std::string filename;
	std::ifstream file; //���������� ��� �������� ����� � ������ �� ����
	
	do{
	std::cout << "������� ���� �����:" << std::endl << "> ";
	path = Read_String_Without_Whitespace(); //������ �������� ���� ��� ��������.

	while (!Path_Is_Correct) {

		//��������� ���������� �� ����, ������� �� ��� � ������������ ��������� ��� ����� �� ������ ������ ��� �������� �� .txt
		if (!File_Exists(path)) {
			std::cout << "���� �� ����������, ���������� ������ ������ ����." << std::endl;
			std::cout << "������� ����:";
			path = Read_String_Without_Whitespace();
			continue;
		}

		filename = Get_File_Name(path);
		
		if (!Txt_Check(filename)) {
			std::cout << "������� ������ ����:";
			std::cin >> path;
			continue;
		};

		if (Filename_Forbidden_Characters_Check(filename)) {
			std::cout << "� ����� ����� �� ������ ����������� ������������ ��������." << std::endl;
			std::cout << "������� ������ ����:";
			std::cin >> path;
			continue;
		};

		Path_Is_Correct = true;
	}
	filename = Get_File_Name(path); 
	file.open(path); //��������� ����
	std::cout << "���� ������� ������!" << std::endl;
	
	if (file.peek() == std::ifstream::traits_type::eof()) { //peek() ���������� ���� ��������� ������ � �������� ������
															//���� EOF. ���� ��������� ������ ����� ����� �������� �����
															//�������� EOF, �� ����� ���������, ��� ���� ����
															//� ������ ���� ������ ����� ��������� �� ������.
		std::cout << "���� ����. ��������� ���� � ���������� ��� ���." << std::endl;
	}
	
	else {
		
		while (!file.eof()) { //��������� ��� �������� � �����, ���� �� ����� �� EOF.
			file >> intTmp;
			
			if (file.fail()) { //���� ��� ����������� �������� �� ������������ ���� ����������, ��
				file.clear(); //����� ���������� ���� ������ ��� 1. ������� ��� �����
				File_Is_Correct = false; //� ����������� ���� ����������� ���� �������� ������������ ����� ��� false
				break;
			}
		}

		file.clear();
		file.seekg(0); //������������ ������ � ������ ����� ����� �������� ���� ��������.

		if (File_Is_Correct) { //��������� ������ ����������, ���� ���� ����������.

			file >> elements; //���� ���-�� ��������� �� �����.
		
			for (int i = 0; i < elements; i++) {
				file >> intTmp;
				vect.push_back(intTmp);
			}
		
		}

		if (!File_Is_Correct) { //���� ���� ������������, �� ���������� ��������� �� ������ � ��������� ����.
			std::cout << "� ����� ���������� ����������� ����������� ������. ��������� ���� � ���������� ��� ���." << std::endl;
			file.close();
		}
	}
	file.close();
	} while (!File_Is_Correct); //� ����� �������� ���� ����� �� ��� ���, ���� �������� ���� �� �������� ��������� �����������
}