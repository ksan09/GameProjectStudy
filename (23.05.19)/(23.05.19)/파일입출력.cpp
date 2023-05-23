#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	// 파일 쓰기, 읽기
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
	//	writeFile << "겜프" << std::endl;
	//	writeFile << "재희";
	//}

	//std::ofstream writeFile("test3.txt");
	//std::string str;
	//for (int i = 0; i < 5; i++)
	//{
	//	std::cin >> str;
	//	writeFile << str << std::endl;
	//}
	
	//writeFile.close();

	//파일 읽기
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
	
	// ifstream getline ------------- Stage만들때 사용함
	char buf[1024];
	while (!readFile.eof())
	{
		readFile.getline(buf, 12);		// char& buf, 버퍼 크기
		cout << buf << endl;
	}
}