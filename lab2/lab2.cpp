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

//���������� ������ � �������� ����
void SaveBagToBinFile(string FileName, Task<baggage> bag)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("���� �� ������!");
	_int32 i;
	for (i = 0; i < bag.size(); i++)
	{
		bag.GetVect()[i].BagToBinFile(&file);
	}
	file.close();
}

//���������� ���������� ������ � �������� ����
void SaveOwnersToBinFile(string FileName, Task<Owner> owners)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("���� �� ������!");
	_int32 i;
	for (i = 0; i < owners.size(); i++)
	{
		owners.GetVect()[i].OwnerToBinFile(&file);
	}
	file.close();
}

//�������� ������ �� ��������� �����
void LoadBagFromBinFile(string FileName, Task<baggage> &bag)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
		return;
		//throw("�� ������� ��������� ������!");
	bool ok;
	while (!file.eof())
	{
		baggage bagg = BagFromBinFile(&file, ok);
		if (ok)
			bag.Add(bagg);
	}
	file.close();
}

//�������� ���������� �� �����
void LoadOwnersFromBinFile(string FileName, Task<Owner> &owners)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
		return;
		//throw("�� ������� ��������� ������!")
	bool ok;
	while (!file.eof())
	{
		Owner ow = OwnerFromBinFile(&file, ok);
		if (ok)
			owners.Add(ow);
	}
	file.close();
}

//������� ���� ���������
_int32 MainMenu()
{
	cout << "�������� �����������" << endl;
	cout << "����� ���:" << endl;
	cout << "1 - �������� ������" << endl;
	cout << "2 - �������������" << endl;
	cout << "0 - �����" << endl;
	return InputNumber(0, 2, "��� �����: ");
	cout << endl;
}

//���� � ������ "�������� ������"
_int32 MenuForOwners()
{
	cout << endl;
	cout << "����� ��������� ������" << endl;
	cout << "�������� �����:" << endl;
	cout << endl;
	PrintHeadOwners();
	Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
	cout << endl;
	cout << "0 - �����" << endl;
	return InputNumber(0, Owners.size(), "��� �����: ");
}

//���� ��������� �������� ��� ��������� ������
_int32 MenuOwners(_int32 i)
{
	cout << endl;
	PrintHeadOwners();
	vector<Owner> tmp;
	tmp.push_back(Owners.GetVect()[i - 1]);
	Owners.OutputScreenOw(tmp, OutputOwner);
	cout << endl;
	cout << "��������� ��������" << endl;
	cout << "1 - �������� ����� �����" << endl;
	cout << "2 - ���������� ������ � ����� ������" << endl;
	cout << "0 - �����" << endl;
	return InputNumber(0, 2, "��� �����: ");
}

//������� ���� ��� ������ ��������������
_int32 MenuForAdmin()
{
	cout << endl;
	cout << "����� ��������������" << endl;
	cout << "��������� ��������" << endl;
	cout << "1 - �������������� ������" << endl;
	cout << "2 - �������� ���������� � ��� ������" << endl;
	cout << "3 - �������������� ���������� � ���������� ������" << endl;
	cout << "0 - �����" << endl;
	return InputNumber(0, 3, "��� �����: ");
}

//���� ��� �������������� ������ ���������������
_int32 MenuAdminEditBag()
{
	cout << endl;
	cout << "��������� ���������:" << endl;
	cout << "1 - �������� �����" << endl;
	cout << "2 - ������ �����" << endl;
	cout << "3 - �������� ����������" << endl;
	cout << "0 - ������" << endl;
	return InputNumber(0, 3, "��� �����: ");
}

//�������������� ������ ���������������
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
		cout << "���������� � ������ ���������." << endl;
		break;
	case 2:
		PrintHeadBag();
		Bag.OutputScreenBag(Bag.GetVect(), OutputBaggage);
		Bag.Remove(InputNumber(1, Bag.size(), "������� ����� ������, ������� ���������� ������: "));
		cout << "����� �����." << endl;
		break;
	case 3:
		PrintHeadBag();
		Bag.OutputScreenBag(Bag.GetVect(), OutputBaggage);
		n = (InputNumber(1, Bag.size(), "������� ����� ������, ���������� � ������� ���������� ��������: "));
		subset = Bag.GetVect();
		subset[n - 1] = bag.ChangeBaggage(Bag.GetVect()[n - 1]);
		Bag.SetVect(subset)[n - 1];
		cout << "���������� � ������ ��������." << endl;
		break;
	default:
		break;
	}
}

//���� ��� �������������� ��������� ������ ���������������
_int32 MenuAdminEditOwner()
{
	cout << endl;
	cout << "��������� ���������:" << endl;
	cout << "1 - �������� ���������" << endl;
	cout << "2 - ������� ���������" << endl;
	cout << "3 - �������� ���������� � ���������" << endl;
	cout << "0 - ������" << endl;
	return InputNumber(0, 3, "��� �����: ");
}

//�������������� ��������� ������ ���������������
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
		cout << "���������� � ��������� ������ ���������." << endl;
		break;
	case 2:
		PrintHeadOwners();
		Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
		Owners.Remove(InputNumber(1, Owners.size(), "������� ����� ���������, �������� ���������� �������: "));
		cout << "�������� �����." << endl;
		break;
	case 3:
		PrintHeadOwners();
		Owners.OutputScreenOw(Owners.GetVect(), OutputOwner);
		n = (InputNumber(1, Bag.size(), "������� ����� ���������, ���������� � ������� ���������� ��������: "));
		owset = Owners.GetVect();
		owset[n - 1] = ow.ChangeOwner(Owners.GetVect()[n - 1]);
		Owners.SetVect(owset)[n - 1];
		cout << "���������� � ��������� ������ ��������." << endl;
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
							cout << "�� ����� �� ���� �������!" << endl;
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
								cout << "�������� �� �������" << endl;
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