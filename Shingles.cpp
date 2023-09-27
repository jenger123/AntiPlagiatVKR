/**
* \file Shingles.cpp
* Файл реализации методов класса Shingles. Определение класса см. Shingles.h
* \date 14.09.2023
* 
*/

#include "Shingles.h"
#include <iostream>


Shingles::Shingles(wstring filename, int shinglesize)
{

	FileHandle = CreateFileW(filename.c_str(), /// Создаем HANDLE для работы с файлом
		GENERIC_READ, /// Режим чтения
		FILE_SHARE_READ | FILE_SHARE_WRITE, /// Режим совместного чтения\записи
		NULL,
		OPEN_EXISTING, /// Режим открытия файла
		FILE_ATTRIBUTE_NORMAL, /// атрибуты файла
		NULL);
	FileSizeLOPART = GetFileSize(FileHandle, &FileSizeHIPART); /// Получаем размер файла
	ShingleSize = shinglesize; /// Присваиваем значение полю ShingleSize 
	if (FileSizeHIPART != 0) { BigFileSize = FileSizeHIPART; BigFileSize = BigFileSize << 32 + FileSizeLOPART; } /// Если размер больше 2Гб - BigFileSize заполняется так 
	else BigFileSize = FileSizeLOPART; /// Если меньше 2Гб - вот так
	Data = new BYTE[BigFileSize]{ 0 }; /// Выделяю память под данные файла

	/// Чтение файла 
	DWORD BytesRead; /// служебная переменная 
	BOOL checkread = ReadFile(FileHandle, Data, BigFileSize, &BytesRead, NULL);/// Чтение файла 
	if (checkread != TRUE || BytesRead != BigFileSize) /// Проверка корректности операции чтения
	{
		std::cout << "Error of read file" << std::endl;
		return;
	}
	string TextData(reinterpret_cast<const char*>(Data)); /// Пока работаю только с ASCII, поэтому char перевожу в std::string
	TextData[BigFileSize] = '\0';/// Заканчиваю строку терминирующим нулем чтобы убрать мусор в конце
	string ClearTextData; /// завожу строку для канонизированного текста
	for (int i = 0;i < TextData.size() - 1;i++) /// в этом цикле убираю лишние пробелы, знаки препинания и привожу все символы к нижнему регистру
	{
		if ((isspace(TextData[i]) && isspace(TextData[i + 1])) || ispunct(TextData[i])) /// символ игнорируется если это первый пробел в серии или знак препинания
			continue;
		else if (isalpha(TextData[i])) ClearTextData.push_back(tolower(TextData[i])); /// Если заглавная буква - делаем строчной
		else ClearTextData.push_back(TextData[i]); /// во всех остальных случаях просто переписываем символ в строку канонизированного текста
	}
	string word = ""; /// строка для формирования слова
	for (int i = 0;i < ClearTextData.size();i++) /// в этом цикле разбиваю текст по словам и записываю в словарь слов(поле класса)
	{
		if (isspace(ClearTextData[i]) || ClearTextData[i] == '\0' || ClearTextData[i] == '\n') // пробел, перенос строки или терминирующий нуль - разделители
		{
			words.push_back(word); /// если встречен разделитель, все что успело накопиться в строке word записывается в словарь
			word.clear();/// после этого строка очищается
		}
		else word.push_back(ClearTextData[i]); /// Если символ не явялется разделителем - строка word пополняется этим символом 
	}
	string shingle = ""; /// эта строка для формирования шингла из строк
	for (int i = 0;i < words.size()-ShingleSize+1;i++) /// пробегаемся по словарю слов 
	{
		shingle.clear(); /// вначале каждого шага очищаем переменную строку shingle
		for (int j = 0;j < ShingleSize;j++) /// В зависимости от размера шингла добавляем слова из словаря 
			shingle += words[i + j]+' '; /// между словами добавляем пробел
		shingles[shingle] = shingle_hash(shingle); /// пополняем словарь шинглов строкой(шинглом) и его хэш-значением, вычисленным с помощью boost::hash
	}

 }

Shingles::~Shingles()
{
	
	delete[] Data; /// В деструкторе очищаем память и закрываем хэндл файла
	CloseHandle(FileHandle);
}