/**
* \file DiplomTest.cpp
* Файл тестовой программы для ВКР. Здесь пробую работать с файлами, разбивать на шинглы, сравнивать хэш шинглов
* \date 14.09.2023
*/

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "Shingles.h"


using namespace std;
int main()
{
	setlocale(NULL, "rus");
	wstring file1name, file2name;
	int mode = 1; /// режим ввода имен файлов. Если выбрать 1 путь можно будет ввести в консоли
	switch (mode)
	{
	case 0:
	{
		/// Если выбран этот режим поменяйте путь к файлу
		file1name = L"text1.txt";
		file2name = L"text2.txt";
		break;
	}
	case 1:
	{
		cout << "Укажите путь к первому файлу: " << endl;
		wcin >> file1name;
		cout << "Укажите путь ко второму файлу: " << endl;
		wcin >> file2name;
	}
	}
		
	

	Shingles firstfile(file1name, 3); // Передаем имя первого файла в конструктор класса
	Shingles secondfile(file2name, 3); // Передаем имя второго файла в конструктор класса
	int NumberCommonShingles=0; /// В эту переменную будем складывать число совпадающих шинглов
	cout << "Совпадающие шинглы:" << endl;
	for (auto& element : firstfile.shingles) /// element  {std::pair} - пара значений key-value словаря shingles
	{
		if (secondfile.shingles.contains(element.first)) /// contains - метод словаря, проверяющий наличие ключа
		{
			NumberCommonShingles++; /// Если один из ключей совпал - увеличиваем счетчик
			cout << element.first << endl; /// Совпавший ключ выводитяс на экран
		}
	}
	cout << "Совпавших шинглов: "<<NumberCommonShingles<<endl;

	system("pause");
	return 0;
}



