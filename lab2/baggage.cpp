#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include "HelpUtils.h"
#include "MyDate.h"
#include "baggage.h"

using namespace std;

//конструктор
baggage::baggage()
{
	Surname = "";
	FlightNum = 0;
	DepDate = "";
	Destination = "";
	NumPieces = 0;
	Weight = 0;
}

baggage::baggage(string name)
{
	Surname = name;
	FlightNum = 0;
	DepDate = "";
	Destination = "";
	NumPieces = 0;
	Weight = 0;
}

//изменение структуры
baggage baggage::ChangeBaggage(baggage &res)
{
	cout << "Какое поле вы хотите изменить?" << endl;
	cout << "1 - Фамилия пассажира" << endl;
	cout << "2 - Номер рейса" << endl;
	cout << "3 - Дата вылета" << endl;
	cout << "4 - Пункт назначения" << endl;
	cout << "5 - Количество мест багажа" << endl;
	cout << "6 - Вес багажа" << endl;
	cout << "0 - Отмена" << endl;
	int num = InputNumber(0, 6, "");
	MyDate d;
	switch (num)
	{
	case 1:
		res.SetSurname(InputInformation("Введите фамилию пассажира: "));
		break;
	case 2:
		res.SetFlightNum(InputNumber(0, 100, "Введите номер рейса (0 - 100): "));
		break;
	case 3:
		d.InputDate();
		res.SetDepDate(d.ToString());
		break;
	case 4:
		res.SetDestination(InputInformation("Введите пункт назначения: "));
		break;
	case 5:
		res.SetNumPieces(InputNumber(0, 200, "Введите количество мест для багажа (0 -200): "));
		break;
	case 6:
		res.SetWeight(InputNumber(0, 100, "Введите вес багажа (0 - 100): "));
		break;
	default:
		exit(0);
		break;
	}
	return res;
}

//переопределение оператора сравнения
bool baggage::operator== (baggage b)
{
	return ((Surname == b.GetSurname()) && (FlightNum == b.GetFlightNum()) && (DepDate == b.GetDepDate()) &&
		(Destination == b.GetDestination()) && (NumPieces == b.GetNumPieces()) && (Weight == b.GetWeight()));
}

//запись структуры в бинарный файл
void baggage::BagToBinFile(fstream *file)
{
	StrToBin(file, this->Surname);
	file->write(reinterpret_cast<char*>(&(this->FlightNum)), sizeof(this->FlightNum));
	StrToBin(file, this->DepDate);
	StrToBin(file, this->Destination);
	file->write(reinterpret_cast<char*>(&(this->NumPieces)), sizeof(this->NumPieces));
	file->write(reinterpret_cast<char*>(&(this->Weight)), sizeof(this->Weight));
}

//считывание структуры из бинарного файла
baggage BagFromBinFile(fstream *file, bool &ok)
{
	baggage b;
	b.SetSurname(StrFromBin(file));
	_int32 temp;
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	if (ok)
	{
		b.SetFlightNum(temp);
		b.SetDepDate(StrFromBin(file));
		b.SetDestination(StrFromBin(file));
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		b.SetNumPieces(temp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		b.SetWeight(temp);
	}
	return b;
}

//ввод с консоли
baggage InputBaggage()
{
	baggage b;
	b.SetSurname(InputInformation("Введите фамилию пассажира: "));
	b.SetFlightNum(InputNumber(0, 100, "Введите номер рейса (0 - 100): "));
	MyDate d;
	d.InputDate();
	b.SetDepDate(d.ToString());
	b.SetDestination(InputInformation("Введите пункт назначения: "));
	b.SetNumPieces(InputNumber(0, 200, "Введите количество мест для багажа (0 - 200): "));
	b.SetWeight(InputNumber(0, 100, "Введите вес багажа (0 - 100): "));
	return b;
}

//ввод с консоли в режиме "Владелец"
baggage InputOwnerBaggage(string name, _int32 nump)
{
	baggage b;
	b.SetSurname(name);
	b.SetFlightNum(InputNumber(0, 100, "Введите номер рейса (0 - 100): "));
	MyDate d;
	d.InputDate();
	b.SetDepDate(d.ToString());
	b.SetDestination(InputInformation("Введите пункт назначения: "));
	b.SetNumPieces(nump);
	b.SetWeight(InputNumber(0, 100, "Введите вес багажа (0 - 100): "));
	return b;
}

//вывод на консоль
void OutputBaggage(baggage b)
{
	cout << setw(1) << left << "|" << setw(15) << left << b.GetSurname() << "|" 
		<< setw(10) << left << b.GetFlightNum() << "|" << setw(15) << left << b.GetDepDate() << "|" <<
		setw(15) << left << b.GetDestination() << "|" << setw(10) << left <<
		b.GetNumPieces() << "|" << setw(10) << left << b.GetWeight() << "|";
}

//перевод структуры в строку
string ToString(baggage b, _int32 i)
{
	string result = "Запись № " + to_string(i) + "\n" + "Фамилия пассажира: " + b.GetSurname() + "\n" + "Номер рейса: " + to_string(b.GetFlightNum()) + "\n" + "Дата вылета: " + b.GetDepDate() + "\n" +
		"Пункт назначения: " + b.GetDestination() + "\n" + "Количество мест багажа: " + to_string(b.GetNumPieces()) + "\n" +
		"Вес багажа: " + to_string(b.GetWeight()) + "\n";
	return result;
}

//проверака на равенство
/*bool IsEqual(baggage b1, baggage b2)
{
	return ((b1.GetSurname() == b2.GetSurname()) && (b1.GetFlightNum() == b2.GetFlightNum()) && (b1.GetDepDate() == b2.GetDepDate()) &&
		(b1.GetDestination() == b2.GetDestination()) && (b1.GetNumPieces() == b2.GetNumPieces()) && (b1.GetWeight() == b2.GetWeight()));
}*/

//считываение структуры из строки
baggage ReadFromString(ifstream& input)
{
	baggage result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Фамилия пассажира: ";
			result.SetSurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Номер рейса: ";
			result.SetFlightNum(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Дата вылета: ";
			result.SetDepDate(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Пункт назначения: ";
			result.SetDestination(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Количество мест багажа: ";
			result.SetNumPieces(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Вес багажа: ";
			result.SetWeight(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "Ошибка записи в файл!" << endl;
	}
	return result;
}

/*поиск по критериям
1 - фамилия
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
bool SearchInfo(baggage b1, baggage b2, _int32 type_search)
{
	switch (type_search)
	{
	case 1:
		return (b1.GetSurname() == b2.GetSurname());
	case 2:
		return (b1.GetDepDate() == b2.GetDepDate());
	case 3:
		return (b1.GetDestination() == b2.GetDestination());
	case 4:
		return (b1.GetWeight() == b2.GetWeight());
	default:
		break;
	}
}

/*ввод критерия поиска
1 - фамилия
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
baggage InputForSearchInfo(_int32 type_search)
{
	baggage bag;
	MyDate d;
	switch (type_search)
	{
	case 1:
		bag.SetSurname(InputInformation("Введите фамилию: "));
		return bag;
	case 2:
		d.InputDate();
		bag.SetDepDate(d.ToString());
		return bag;
	case 3:
		bag.SetDestination(InputInformation("Введите пункт назначения: "));
		return bag;
	case 4:
		bag.SetWeight(InputNumber(0, 100, "Введите вес багажа (0 - 100): "));
	default:
		return bag;
	}
}

/*сравнение структур по заданному полю
1 - фамилия
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
_int32 Сomparison(baggage b1, baggage b2, _int32 type_search)
{
	switch (type_search)
	{
	case 1:
		if (b1.GetSurname() > b2.GetSurname())
			return 1;
		else
			if (b1.GetSurname() < b2.GetSurname())
				return -1;
			else
				return 0;
	case 2:
		if (b1.GetDepDate() > b2.GetDepDate())
			return 1;
		else
			if (b1.GetDepDate() < b2.GetDepDate())
				return -1;
			else
				return 0;
	case 3:
		if (b1.GetDestination() > b2.GetDestination())
			return 1;
		else
			if (b1.GetDestination() < b2.GetDestination())
				return -1;
			else
				return 0;
	case 4:
		if (b1.GetWeight() > b2.GetWeight())
			return 1;
		else
			if (b1.GetWeight() < b2.GetWeight())
				return -1;
			else
				return 0;
	default:
		return -2;
	}
}