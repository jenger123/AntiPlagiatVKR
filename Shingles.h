/** \file Shingles.h
* ���� ��������� ������ Shingles. �������� ����������� ������� � ����� ������
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
* \brief ����� Shingles �������� ������ ��������� ������� �� ������ � �������� � ����
* 
*/
class Shingles
{
public:
	/**
	* \brief ����������� ������. ������� ��� ����������� ��� ������ ���������� 
	* \param [in] {std::wstring} filename - ���� � ���������� �����
	* \param [in] {int} shinglesize - ������ ������ � ������
	*/
	Shingles(wstring filename, int shinglesize);
	map<string,int> shingles;
	
	~Shingles();
protected:
private:
	int ShingleSize{ 0 }; /// ���� ��� �������� �������� ������� ������
	DWORDLONG BigFileSize{ 0 }; /// ���� ��� �������� ������� �����
	HANDLE FileHandle{NULL}; /// ���� ��� �������� ��������� �� HANDLE �����
	DWORD FileSizeLOPART{ 0 }, FileSizeHIPART{ 0 }; /// ���� ���� ������ 2�� ��� �������� ������� ����������� ������ FileSizeLOPART
	BYTE* Data; /// ������ �����
	int errornum = 0;/// ����� ������
	vector<string> words;/// ������� ���� ������. ����� ��� ����������� �������
	boost::hash<std::string> shingle_hash; /// ������ ������ boost::hash
	
};

