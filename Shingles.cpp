/**
* \file Shingles.cpp
* ���� ���������� ������� ������ Shingles. ����������� ������ ��. Shingles.h
* \date 14.09.2023
* 
*/

#include "Shingles.h"
#include <iostream>


Shingles::Shingles(wstring filename, int shinglesize)
{

	FileHandle = CreateFileW(filename.c_str(), /// ������� HANDLE ��� ������ � ������
		GENERIC_READ, /// ����� ������
		FILE_SHARE_READ | FILE_SHARE_WRITE, /// ����� ����������� ������\������
		NULL,
		OPEN_EXISTING, /// ����� �������� �����
		FILE_ATTRIBUTE_NORMAL, /// �������� �����
		NULL);
	FileSizeLOPART = GetFileSize(FileHandle, &FileSizeHIPART); /// �������� ������ �����
	ShingleSize = shinglesize; /// ����������� �������� ���� ShingleSize 
	if (FileSizeHIPART != 0) { BigFileSize = FileSizeHIPART; BigFileSize = BigFileSize << 32 + FileSizeLOPART; } /// ���� ������ ������ 2�� - BigFileSize ����������� ��� 
	else BigFileSize = FileSizeLOPART; /// ���� ������ 2�� - ��� ���
	Data = new BYTE[BigFileSize]{ 0 }; /// ������� ������ ��� ������ �����

	/// ������ ����� 
	DWORD BytesRead; /// ��������� ���������� 
	BOOL checkread = ReadFile(FileHandle, Data, BigFileSize, &BytesRead, NULL);/// ������ ����� 
	if (checkread != TRUE || BytesRead != BigFileSize) /// �������� ������������ �������� ������
	{
		std::cout << "Error of read file" << std::endl;
		return;
	}
	string TextData(reinterpret_cast<const char*>(Data)); /// ���� ������� ������ � ASCII, ������� char �������� � std::string
	TextData[BigFileSize] = '\0';/// ���������� ������ ������������� ����� ����� ������ ����� � �����
	string ClearTextData; /// ������ ������ ��� ����������������� ������
	for (int i = 0;i < TextData.size() - 1;i++) /// � ���� ����� ������ ������ �������, ����� ���������� � ������� ��� ������� � ������� ��������
	{
		if ((isspace(TextData[i]) && isspace(TextData[i + 1])) || ispunct(TextData[i])) /// ������ ������������ ���� ��� ������ ������ � ����� ��� ���� ����������
			continue;
		else if (isalpha(TextData[i])) ClearTextData.push_back(tolower(TextData[i])); /// ���� ��������� ����� - ������ ��������
		else ClearTextData.push_back(TextData[i]); /// �� ���� ��������� ������� ������ ������������ ������ � ������ ����������������� ������
	}
	string word = ""; /// ������ ��� ������������ �����
	for (int i = 0;i < ClearTextData.size();i++) /// � ���� ����� �������� ����� �� ������ � ��������� � ������� ����(���� ������)
	{
		if (isspace(ClearTextData[i]) || ClearTextData[i] == '\0' || ClearTextData[i] == '\n') // ������, ������� ������ ��� ������������� ���� - �����������
		{
			words.push_back(word); /// ���� �������� �����������, ��� ��� ������ ���������� � ������ word ������������ � �������
			word.clear();/// ����� ����� ������ ���������
		}
		else word.push_back(ClearTextData[i]); /// ���� ������ �� �������� ������������ - ������ word ����������� ���� �������� 
	}
	string shingle = ""; /// ��� ������ ��� ������������ ������ �� �����
	for (int i = 0;i < words.size()-ShingleSize+1;i++) /// ����������� �� ������� ���� 
	{
		shingle.clear(); /// ������� ������� ���� ������� ���������� ������ shingle
		for (int j = 0;j < ShingleSize;j++) /// � ����������� �� ������� ������ ��������� ����� �� ������� 
			shingle += words[i + j]+' '; /// ����� ������� ��������� ������
		shingles[shingle] = shingle_hash(shingle); /// ��������� ������� ������� �������(�������) � ��� ���-���������, ����������� � ������� boost::hash
	}

 }

Shingles::~Shingles()
{
	
	delete[] Data; /// � ����������� ������� ������ � ��������� ����� �����
	CloseHandle(FileHandle);
}