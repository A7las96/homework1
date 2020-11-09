
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
using namespace std;


int main(int argc, const char* argv[]) {
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	if (argc != 3) {
		cerr << "Error: Use three parameters\n";
		return 5;
	}
	const string mode(argv[1]); // Режим работы
	const string file_name(argv[2]); // Имя файла
	unsigned int seed;
	string line;
	cout << "Введите ключ" << endl;
	cin >> seed;
	srand(seed);
	short gamma = rand();
	string symbols = {};
	unsigned short str;
	unsigned short bit;
	string code = {};
	if (mode == "encryption")
	{	// Режим шифрование
		cin.get();
		cout << "Введите строку для шифрования\n";
		getline(cin, line);
		if (line.length() % 2 != 0)
			line.push_back(' ');
		for (unsigned int i = 0; i < line.length(); i += 2)
		{
			symbols.clear();
			symbols.push_back(line[i]);
			symbols.push_back(line[i + 1]);
			memcpy(&str, &symbols[0], 2);
			str = str ^ gamma;
			for (int j = 0; j < 4; j++)
			{
				bit = str & 0x0001;
				str >>= 1;
				str |= bit << 15;
			}
			memcpy(&symbols[0], &str, 2);
			code.push_back(symbols[0]);
			code.push_back(symbols[1]);
		}
		ofstream fout; 
		fout.open(file_name);
		if (fout.is_open())
			for (unsigned int i = 0; i < code.size(); i++)
				fout << code[i];
		fout.close();
		system("pause");
	}
	else if (mode == "decryption")
	{	// Режим расшифрования
		ifstream fin;
		fin.open(file_name);
		if (fin.is_open())
			(getline(fin, line));
		fin.close();
		for (unsigned int i = 0; i < line.length(); i += 2)
		{
			symbols.clear();
			symbols.push_back(line[i]);
			symbols.push_back(line[i + 1]);
			memcpy(&str, &symbols[0], 2);
			for (int j = 0; j < 4; j++)
			{
				bit = str & 0x8000 ? 1 : 0;
				str <<= 1;
				str |= bit;
			}
			str = str ^ gamma;
			memcpy(&symbols[0], &str, 2);
			code.push_back(symbols[0]);
			code.push_back(symbols[1]);
		}
		cout << code<<endl;
		system("pause");
	}
}
