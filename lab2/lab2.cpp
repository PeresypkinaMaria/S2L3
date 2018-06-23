#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include "baggage.h"
#include "Owner.h"
#include "Search.h"
#include "HelpUtils.h"

using namespace std;

Task<baggage> Bag;
Task<Owner> Owners;

//сохранение багажа в бинарный файл
void SaveBagToBinFile(string FileName, Task<baggage> bag)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("Файл не открыт!");
	_int32 i;
	for (i = 0; i < bag.size(); i++)
	{
		bag.GetVect()[i].BagToBinFile(&file);
	}
	file.close();
}

//сохранение владельцев багажа в бинарный файл
void SaveOwnersToBinFile(string FileName, Task<Owner> owners)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("Файл не открыт!");
	_int32 i;
	for (i = 0; i < owners.size(); i++)
	{
		owners.GetVect()[i].OwnerToBinFile(&file);
	}
	file.close();
}

//загрузка багажа из бинарного файла
void LoadBagFromBinFile(string FileName, Task<baggage> &bag)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
		return;
		//throw("Не удалось загрузить данные!");
	bool ok;
	while (!file.eof())
	{
		baggage bagg = BagFromBinFile(&file, ok);
		if (ok)
			bag.Add(bagg);
	}
	file.close();
}

//загрузка владельцев из файла
void LoadOwnersFromBinFile(string FileName, Task<Owner> &owners)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
		return;
		//throw("Не удалось загрузить данные!")
	bool ok;
	while (!file.eof())
	{
		Owner ow = OwnerFromBinFile(&file, ok);
		if (ok)
			owners.Add(ow);
	}
	file.close();
}

//главное меню программы
_int32 MainMenu()
{
	cout << "Аэропорт «Домодедово»" << endl;
	cout << "Войти как:" << endl;
	cout << "1 - Владелец багажа" << endl;
	cout << "2 - Администратор" << endl;
	cout << "0 - Выход" << endl;
	return InputNumber(0, 2, "Ваш выбор: ");
	cout << endl;
}

//меню в режиме "Владелец багажа"
_int32 MenuForOwners()
{
	cout << endl;
	cout << "Режим «Владелец багажа»" << endl;
	cout << "Выберете номер:" << endl;
	cout << endl;
	PrintHeadOwners();
	Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
	cout << endl;
	cout << "0 - Назад" << endl;
	return InputNumber(0, Owners.size(), "Ваш выбор: ");
}

//меню доступных действий для владельца багажа
_int32 MenuOwners(_int32 i)
{
	cout << endl;
	PrintHeadOwners();
	vector<Owner> tmp;
	tmp.push_back(Owners.GetVect()[i - 1]);
	Owners.OutputScreenOw(tmp, OutputOwner);
	cout << endl;
	cout << "Доступные действия" << endl;
	cout << "1 - Добавить новый багаж" << endl;
	cout << "2 - Посмотреть данные о своем багаже" << endl;
	cout << "0 - Назад" << endl;
	return InputNumber(0, 2, "Ваш выбор: ");
}

//главное меню для режима «Администратор»
_int32 MenuForAdmin()
{
	cout << endl;
	cout << "Режим «Администратор»" << endl;
	cout << "Доступные действия" << endl;
	cout << "1 - Редактирование багажа" << endl;
	cout << "2 - Просмотр информации о всём багаже" << endl;
	cout << "3 - Редактирование информации о владельцах багажа" << endl;
	cout << "0 - Назад" << endl;
	return InputNumber(0, 3, "Ваш выбор: ");
}

//меню для редактирования багажа администратором
_int32 MenuAdminEditBag()
{
	cout << endl;
	cout << "Доступные изменения:" << endl;
	cout << "1 - Добавить багаж" << endl;
	cout << "2 - Выдать багаж" << endl;
	cout << "3 - Изменить информацию" << endl;
	cout << "0 - Отмена" << endl;
	return InputNumber(0, 3, "Ваш выбор: ");
}

//редактирование багажа администратором
void AdminEditBag()
{
	baggage bag;
	vector<baggage> subset;
	_int32 num = MenuAdminEditBag();
	_int32 n;
	switch (num)
	{
	case 1:
		Bag.Add(InputBaggage());
		cout << "Информация о багаже добавлена." << endl;
		break;
	case 2:
		PrintHeadBag();
		Bag.OutputScreenBag(Bag.GetVect(), OutputBaggage);
		Bag.Remove(InputNumber(1, Bag.size(), "Введите номер багажа, который необходимо выдать: "));
		cout << "Багаж выдан." << endl;
		break;
	case 3:
		PrintHeadBag();
		Bag.OutputScreenBag(Bag.GetVect(), OutputBaggage);
		n = (InputNumber(1, Bag.size(), "Введите номер багажа, информацию о котором необходимо изменить: "));
		subset = Bag.GetVect();
		subset[n - 1] = bag.ChangeBaggage(Bag.GetVect()[n - 1]);
		Bag.SetVect(subset)[n - 1];
		cout << "Информация о багаже изменена." << endl;
		break;
	default:
		break;
	}
}

//меню для редактирования владельца багажа администратором
_int32 MenuAdminEditOwner()
{
	cout << endl;
	cout << "Доступные изменения:" << endl;
	cout << "1 - Добавить владельца" << endl;
	cout << "2 - Удалить владельца" << endl;
	cout << "3 - Изменить информацию о владельце" << endl;
	cout << "0 - Отмена" << endl;
	return InputNumber(0, 3, "Ваш выбор: ");
}

//редактирование владельца багажа администратором
void AdminEditOwner()
{
	Owner ow;
	vector<Owner> owset;
	_int32 num = MenuAdminEditOwner();
	_int32 n;
	switch (num)
	{
	case 1:
		Owners.Add(InputOwner());
		cout << "Информация о владельце багажа добавлена." << endl;
		break;
	case 2:
		PrintHeadOwners();
		Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
		Owners.Remove(InputNumber(1, Owners.size(), "Введите номер владельца, которого необходимо удалить: "));
		cout << "Владелец удалён." << endl;
		break;
	case 3:
		PrintHeadOwners();
		Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
		n = (InputNumber(1, Bag.size(), "Введите номер владельца, информацию о котором необходимо изменить: "));
		owset = Owners.GetVect();
		owset[n - 1] = ow.ChangeOwner(Owners.GetVect()[n - 1]);
		Owners.SetVect(owset)[n - 1];
		cout << "Информация о владельце багажа изменена." << endl;
		break;
	default:
		break;
	}
}

_int32 main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	LoadBagFromBinFile("Baggage.dat", Bag);
	LoadOwnersFromBinFile("Owners.dat", Owners);

	_int32 i, it, mode;
	baggage bag;
	vector<baggage> subset;
	do
	{
		mode = MainMenu();
		switch (mode)
		{
		case 1:
			do
			{
				i = MenuForOwners();
				cout << endl;
				if (i != 0)
				{
					_int32 num = MenuOwners(i);
					switch (num)
					{
					case 1:
						bag = InputOwnerBaggage(Owners.GetVect()[i - 1].GetOwnerSurname(), Owners.GetVect()[i - 1].GetNumOfBag());
						Bag.Add(bag);
						break;
					case 2:
						//PrintHeadBag();
						//bag = InputForSearchInfo(1);
						/*if (bag.GetSurname() != Owners.GetVect()[i - 1].GetOwnerSurname())
							cout << "Вы ввели не свою фамилию!" << endl;
						else*/
						{
						baggage bag1(Owners.GetVect()[i - 1].GetOwnerSurname());
							subset = Bag.LinearySearch(bag1, SearchInfo, 1);
							if (subset.size() != 0)
							{
								PrintHeadBag();
								for (_int32 i = 0; i < subset.size(); i++)
								{
									cout << "|" << setw(6) << left << to_string(i + 1);
									OutputBaggage(subset[i]);
									cout << endl;
								}
							}
							else
								cout << "Элементы не найдены" << endl;
							break;
						}
					default:
						break;
					}
				}
				SaveBagToBinFile("Baggage.dat", Bag);
				SaveOwnersToBinFile("Owners.dat", Owners);
			} while (i != 0);
			break;
		case 2:
			do
			{ 
				it = MenuForAdmin();
				cout << endl;
				switch (it)
				{
				case 1:
					AdminEditBag();
					cout << endl;
					break;
				case 2:
					Bag.OutputScreenBag(Bag.GetVect(), OutputBaggage);
					cout << endl;
					break;
				case 3:
					AdminEditOwner();
					cout << endl;
					break;
				default:
					break;
				}
				SaveBagToBinFile("Baggage.dat", Bag);
				SaveOwnersToBinFile("Owners.dat", Owners);
			} while (it != 0);
			break;
		default:
			SaveBagToBinFile("Baggage.dat", Bag);
			SaveOwnersToBinFile("Owners.dat", Owners);
			exit(0);
		}
	} while (mode != 0);
	return 0;
}