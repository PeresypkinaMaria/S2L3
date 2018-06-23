#pragma once
#include "stdafx.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include "HelpUtils.h"

class Owner
{
private:
	string OwnerSurname; //фамилия владельца багажа
	_int32 NumOfBag; //количество багажа
public:
	//свойства доступа
	string GetOwnerSurname()
	{
		return OwnerSurname;
	}

	string SetOwnerSurname(string value)
	{
		return OwnerSurname = value;
	}

	_int32 GetNumOfBag()
	{
		return NumOfBag;
	}

	_int32 SetNumOfBag(_int32 value)
	{
		return NumOfBag = value;
	}

	//конструктор
	Owner();

	//изменение структуры
	Owner ChangeOwner(Owner &res);

	//перегруженный оператор присваивания
	Owner& operator = (Owner ow);

	//запись структуры в бинарный файл
	void OwnerToBinFile(fstream *file);
};

//считывание структуры из бинарного файла
Owner OwnerFromBinFile(fstream *file, bool &ok);

//ввод с консоли
Owner InputOwner();

//вывод на консоль
void OutputOwner(Owner ow);

//перевод структуры в строку
string ToString(Owner ow, _int32 i);

//проверака на равенство
bool IsEqual(Owner ow1, Owner ow2);

//считывание структуры из строки
Owner ReadFromStringOwner(ifstream& input);