#pragma once
#include "stdafx.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include "HelpUtils.h"
#include "MyDate.h"

using namespace std;

class baggage {
private:
	string Surname; //фамилия пассажира
	_int32 FlightNum; //номер рейса
	string DepDate; //дата вылета
	string Destination; //пунк назначения
	_int32 NumPieces; //количество мест багажа
	_int32 Weight; //вес багажа

public:
	//свойства доступа к полям
	string GetSurname()
	{
		return Surname;
	}

	string SetSurname(string value)
	{
		return Surname = value;
	}

	_int32 GetFlightNum()
	{
		return FlightNum;
	}

	_int32 SetFlightNum(_int32 value)
	{
		return FlightNum = value;
	}

	string GetDepDate()
	{
		return DepDate;
	}

	string SetDepDate(string value)
	{
		return DepDate = value;
	}

	string GetDestination()
	{
		return Destination;
	}

	string SetDestination(string value)
	{
		return Destination = value;
	}

	_int32 GetNumPieces()
	{
		return NumPieces;
	}

	_int32 SetNumPieces(_int32 value)
	{
		return NumPieces = value;
	}

	_int32 GetWeight()
	{
		return Weight;
	}

	_int32 SetWeight(_int32 value)
	{
		return Weight = value;
	}

	//конструктор
	baggage();

	baggage(string name);

	//изменение структуры
	baggage ChangeBaggage(baggage &res);

	//перегруженный оператор равенства
	bool operator== (baggage b);

	//запись структуры в бинарный файл
	void BagToBinFile(fstream *file);
};

//считывание структуры из бинарного файла
baggage BagFromBinFile(fstream *file, bool &ok);

//ввод с консоли
baggage InputBaggage();

//ввод с консоли в режиме "Владелец"
baggage InputOwnerBaggage(string name, _int32 nump);

//вывод на консоль
void OutputBaggage(baggage b);

//перевод структуры в строку
string ToString(baggage b, _int32 i);

//проверака на равенство
bool IsEqual(baggage b1, baggage b2);

//считывание структуры из строки
baggage ReadFromString(ifstream& input);

/*поиск по критериям
1 - номер рейса
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
bool SearchInfo(baggage b1, baggage b2, _int32 type_search);

/*ввод критерия поиска
1 - номер рейса
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
baggage InputForSearchInfo(_int32 type_search);

/*сравнение структур по заданному полю
1 - номер рейса
2 - дата вылета
3 - пункт назначения
4 - вес багажа*/
_int32 Сomparison(baggage b1, baggage b2, _int32 type_search);