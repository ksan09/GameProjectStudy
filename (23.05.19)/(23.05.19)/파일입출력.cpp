#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	// ���� ����, �б�
	// open, is_open(), close(), write()
	//std::ofstream writeFile("test2.txt", std::ios_base::out);		// of: output file
	//writeFile.open("test.txt");
	// 
	//std::ofstream writeFile("test2.txt");
	//char arr[8] = "GangSan";
	//
	//if (writeFile.is_open())
	//{
	//	writeFile.write(arr, 7);
	//	writeFile << "����" << std::endl;
	//	writeFile << "����";
	//}

	//std::ofstream writeFile("test3.txt");
	//std::string str;
	//for (int i = 0; i < 5; i++)
	//{
	//	std::cin >> str;
	//	writeFile << str << std::endl;
	//}
	
	//writeFile.close();

	//���� �б�
	std::ifstream readFile("test2.txt"); // input
	// open, is_open(), close(), read, eof, get, getline
	//if (readFile.is_open())
	//{
	//	while(!readFile.eof())
	//		std::cout << (char)readFile.get() << std::endl;
	//
	//}

	// string getline
	//string str;
	//while(getline(readFile, str))
	//	cout << str << endl;
	
	// ifstream getline ------------- Stage���鶧 �����
	char buf[1024];
	while (!readFile.eof())
	{
		readFile.getline(buf, 12);		// char& buf, ���� ũ��
		cout << buf << endl;
	}
}