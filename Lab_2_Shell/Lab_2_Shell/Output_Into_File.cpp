#include "Output_Into_File.h"
#include "Input_From_File.h"

void Output_Into_File(std::vector<int>& vect, std::vector<int>& vect2)
{
	std::string FileName;
	std::ofstream file;
	int SaveChoise = 0; //����������, �������� ����� '��������� ��� ���' ������������
	int SaveMethod = 0; //����� ���������� (���������� � �����, ����������, ����� ������� �����) ����� ����� ����
	int FileMethod = 0; //����������, �������� ����� "������� �� ���� ��� ���", ���� ��������� ����� �� ����������.
	do {
		std::cout << "1 - ��������� � ����." << std::endl << "2 - ���������� ��� ����������." << std::endl << "> ";
		SaveChoise = Check_Int();
		switch (SaveChoise) {
		case Save:
			while (true) {
				std::cout << "������� ���� � ����� ��� ����������:" << std::endl << "> ";
				FileName = Read_String_Without_Whitespace();
				//������ ������� ����� ��� ����� ����������� �� ������� ���������� .txt, �������� �� ��� ����� ����������������� � ���� �� � ����� ����� ������������ �������
				while (Is_Reserved_Filename(Get_Filename(FileName)) || Filename_Forbidden_Characters_Check(Get_Filename(FileName)) || !Txt_Check(Get_Filename(FileName))) {
					std::cout << "������������ �������� ��� ������ �����. ���������� ��� ���." << std::endl << "> ";
					FileName = Read_String_Without_Whitespace();
				}
				//�������� ������������� �����. ���� ���� ����������, ��� ������������ ��������� � ����� �� ���� �������, ���� ������� ������ ����.
				if (File_Exists(FileName)) {
					do {
						std::cout << "���� ��� ����������. �������� ����� �����: " << std::endl << "1 - ������������ ����" << std::endl << "2 - �������� � ����� �����" << std::endl << "3 - ������� ������ ����" << std::endl << "> ";
						SaveMethod = Check_Int();
						switch (SaveMethod) {
						//� ����������� �� ������ ������������, ���� �����������, � ���������� ���������, ���� �����������,
						//� � ����������� � ����� ����������� ���������� ������
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
							std::cout << "������ ������ ��� � ����, ���������� ��� ���" << std::endl;
							break;
						}
					} while (SaveMethod != RewriteFile && SaveMethod != WriteToTheEndOfTheFile && SaveMethod != SelectAnotherFile);
				}
				else if (Only_Read(FileName)) {
					std::cout << "������ ������� � �����. ���� �������� ������ ��� ������." << std::endl;
					break;
				} //���� ����� �� ����������, ������� �� �������.
				if (SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || !File_Exists(FileName)) {
					break;
				}
			}
			if (!File_Exists(FileName)) { //���� ����� �� ����������, ���������� ������� ��� ��� ���������� ��� ����������
				do {
					std::cout << "����� �� ������� ���� �� �������, ������ ������� ���?" << std::endl
						<< "1 - ������� ����." << std::endl << "2 - ���������� ��� ����������." << std::endl << "> ";
					FileMethod = Check_Int();
					switch (FileMethod) {
					case CreateFile:
						file.open(FileName);
						break;
					case ContunueWithoutCreatingFile:
						break;
					default:
						std::cout << "������ ������ ��� � ����, ���������� ��� ���" << std::endl;
						break;
					}
				} while (FileMethod != CreateFile && FileMethod != ContunueWithoutCreatingFile);
			}
			//��������� ����������� �� ��������� ������ ���������� (���������� ��� ����������) 
			// � ������� �� ����� ���������� � ���� ��� ����������� ��� ���������� 
			//����� ������� ������� � ����.
			if (SaveMethod == RewriteFile || SaveMethod == WriteToTheEndOfTheFile || FileMethod == CreateFile ) {
				file << "�������� ������: " << '\n';
				for (int i = 0; i < vect.size(); i++) {
					file << vect[i] << ' ';
					if (i == vect.size() - 1) file << '\n';
				}
				file << '\n' << "������������� ������:" << '\n';
				for (int i = 0; i < vect2.size(); i++) {
					file << vect2[i] << ' ';
				}
			}
			file.close();
			break;
		case ContinueWithoutSaving:
			break;
		default:
			std::cout << "������ ������ ��� � ����, ���������� ��� ���" << std::endl;
			break;
		}
	} while (SaveChoise != Save && SaveChoise != ContinueWithoutSaving);


}
