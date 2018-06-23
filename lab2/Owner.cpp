#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "Owner.h"

using namespace std;

//конструктор
Owner::Owner()
{
	OwnerSurname = "";
	NumOfBag = 0;
}

//изменение структуры
Owner Owner::ChangeOwner(Owner &res)
{
	cout << "Какое поле вы хотите изменить?" << endl;
	cout << "1 - Фамилия" << endl;
	cout << "2 - Количество багажа" << endl;
	cout << "0 - Отмена" << endl;
	_int32 num = InputNumber(0, 2, "");
	switch (num)
	{
	case 1:
		res.SetOwnerSurname(InputInformation("Введите фамилию: "));
		break;
	case 2:
		res.SetNumOfBag(InputNumber(0, 300, "Введите количество багажа (0 - 200): "));
		break;
	default:
		exit(0);
		break;
	}
	return res;
}

//перегруженный оператор присваивания
Owner& Owner::operator = (Owner ow)
{
	OwnerSurname = ow.GetOwnerSurname();
	NumOfBag = ow.GetNumOfBag();
	return (*this);
}

//запись структуры в бинарный файл
void Owner::OwnerToBinFile(fstream * file)
{
	StrToBin(file, this->OwnerSurname);
	file->write(reinterpret_cast<char*>(&(this->NumOfBag)), sizeof(this->NumOfBag));
}

//считывание структуры из бинарного файла
Owner OwnerFromBinFile(fstream *file, bool &ok)
{
	Owner ow;
	_int32 temp;
	ow.SetOwnerSurname(StrFromBin(file));
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	ow.SetNumOfBag(temp);
	return ow;
}

//ввод с консоли
Owner InputOwner()
{
	Owner ow;
	ow.SetOwnerSurname(InputInformation("Введите фамилию: "));
	ow.SetNumOfBag(InputNumber(0, 200, "Введите количество багажа (0 - 200): "));
	return ow;
}

//вывод на консоль
void OutputOwner(Owner ow)
{
	cout << setw(1) << left << "|" << setw(7) << left << ow.GetOwnerSurname() << "|" << setw(10) << left << ow.GetNumOfBag() << "|";
}

//перевод структуры в строку
string ToString(Owner ow, _int32 i)
{
	string res = "Запись № " + to_string(i) + "\n" + "Фамилия: " + ow.GetOwnerSurname() + "\n" + "Количество багажа: " + to_string(ow.GetNumOfBag()) + "\n";
	return res;
}

//проверака на равенство
bool IsEqual(Owner ow1, Owner ow2)
{
	return ((ow1.GetOwnerSurname() == ow2.GetOwnerSurname()) &&
		(ow1.GetNumOfBag() == ow2.GetNumOfBag()));
}

//считывание структуры из строки
Owner ReadFromStringOwner(ifstream& input)
{
	Owner res;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Фамилия: ";
			res.SetOwnerSurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Количество багажа: ";
			res.SetNumOfBag(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "Ошибка!" << endl;
	}
	return res;
}