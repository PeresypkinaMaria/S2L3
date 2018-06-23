#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "HelpUtils.h"

using namespace std;

//ввод числа
int InputNumber(int min, int max, string message)
{
	int n;
	while (true) {
		cout << message;
		cin >> n;
		if (!cin) {
			cout << "Неверный ввод! Попробуйте снова\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else {
			if (n >= min && n <= max) {
				break;
			}
			else {
				cout << "Некорректно, введите значение в диапазоне от " << min << " до " << max << endl;
				continue;
			}
		}
	}
	return n;
}

// ввод информации
string InputInformation(string messge)
{
	string a;
	cout << messge;
	cin >> a;
	return a;
}

// проверка символа на корректность в имени файла
bool CorrectSymbol(char c)
{
	switch (c)
	{
	case '.':
	case '*':
	case '?':
	case '<':
	case '>':
	case ':':
	case '|':
	case '/':
		return false;
	default:
		return true;
	}
}


// проверка имени файла на коректность
bool CorrectName(string name)
{
	int i = 0;
	bool goodsm = true;
	for (int i = 0; (i < name.length() && goodsm); i++)
		goodsm = CorrectSymbol(name[i]);
	return goodsm;
}

// ввод имени файла
string InputFileName()
{

	string filename;
	do
	{
		cout << "Введите имя файла:  ";
		cin >> filename;
		if (filename.length() > 35)
			filename.erase(filename.begin(), filename.begin() + 35);
		if (CorrectName(filename))
		{
			filename = filename + ".txt";
			break;
		}
		else
			cout << "Неверное имя файла\n";
	} while (true);

	return filename;
}

//запись строки в бинарный файл
void StrToBin(fstream *f, string str)
{
	_int32 len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}

//считывание строки из бинарного файла
string StrFromBin(fstream *f) 
{
	string result;
	_int32 len;
	if (!f->read(reinterpret_cast<char*>(&len), sizeof(len))) {
		return "";
	}
	char *buf = new char[len];
	if (!f->read(buf, len)) {
		return "";
	}
	result = buf;
	delete[] buf;
	return result;
}

//печать шапки таблицы владельца багажа
void PrintHeadOwners()
{
	cout << setw(1) << left << "|" << setw(6) << left << "Запись" << "|" << setw(7) << left << "Фамилия" << "|" <<
		setw(10) << left << "Багаж (шт.)" << "|" << endl;
}

//печать шапки таблицы информации о багаже
void PrintHeadBag()
{
	cout << setw(1) << left << "|" << setw(6) << left << "Запись" << "|" << setw(15) << left << "Фамилия" << "|" <<
		setw(10) << left << "Номер рейса" << "|" << setw(15) << left << "Дата вылета" << "|" <<
		setw(15) << left << "Пункт назначения" << "|" << setw(10) << left << "Количество мест багажа" << "|" <<
		setw(10) << left << "Вес багажа" << "|" << endl;
}