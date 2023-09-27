/** \file Shingles.h
* Файл заголовка класса Shingles. Содержит определения методов и полей класса
* \date 14.09.2023
*/

#pragma once
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <boost/functional/hash.hpp>
using namespace std;

/**
* \class Shingles
* \brief Класс Shingles содержит методы разбиения текстов на шинглы и операции с ними
* 
*/
class Shingles
{
public:
	/**
	* \brief Конструктор класса. Создает все необходимые для работы переменные 
	* \param [in] {std::wstring} filename - путь к текстовому файлу
	* \param [in] {int} shinglesize - размер шингла в словах
	*/
	Shingles(wstring filename, int shinglesize);
	map<string,int> shingles;
	
	~Shingles();
protected:
private:
	int ShingleSize{ 0 }; /// Поле для хранение значения размера шингла
	DWORDLONG BigFileSize{ 0 }; /// поле для хранения размера файла
	HANDLE FileHandle{NULL}; /// Поле для хранения указателя на HANDLE файла
	DWORD FileSizeLOPART{ 0 }, FileSizeHIPART{ 0 }; /// Если файл меньше 2Гб для хранения размера понадобится только FileSizeLOPART
	BYTE* Data; /// Данные файла
	int errornum = 0;/// номер ошибки
	vector<string> words;/// словарь слов текста. нужен для составления шинглов
	boost::hash<std::string> shingle_hash; /// Объект класса boost::hash
	
};

