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

//�����������
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

//��������� ���������
baggage baggage::ChangeBaggage(baggage &res)
{
	cout << "����� ���� �� ������ ��������?" << endl;
	cout << "1 - ������� ���������" << endl;
	cout << "2 - ����� �����" << endl;
	cout << "3 - ���� ������" << endl;
	cout << "4 - ����� ����������" << endl;
	cout << "5 - ���������� ���� ������" << endl;
	cout << "6 - ��� ������" << endl;
	cout << "0 - ������" << endl;
	int num = InputNumber(0, 6, "");
	MyDate d;
	switch (num)
	{
	case 1:
		res.SetSurname(InputInformation("������� ������� ���������: "));
		break;
	case 2:
		res.SetFlightNum(InputNumber(0, 100, "������� ����� ����� (0 - 100): "));
		break;
	case 3:
		d.InputDate();
		res.SetDepDate(d.ToString());
		break;
	case 4:
		res.SetDestination(InputInformation("������� ����� ����������: "));
		break;
	case 5:
		res.SetNumPieces(InputNumber(0, 200, "������� ���������� ���� ��� ������ (0 -200): "));
		break;
	case 6:
		res.SetWeight(InputNumber(0, 100, "������� ��� ������ (0 - 100): "));
		break;
	default:
		exit(0);
		break;
	}
	return res;
}

//��������������� ��������� ���������
bool baggage::operator== (baggage b)
{
	return ((Surname == b.GetSurname()) && (FlightNum == b.GetFlightNum()) && (DepDate == b.GetDepDate()) &&
		(Destination == b.GetDestination()) && (NumPieces == b.GetNumPieces()) && (Weight == b.GetWeight()));
}

//������ ��������� � �������� ����
void baggage::BagToBinFile(fstream *file)
{
	StrToBin(file, this->Surname);
	file->write(reinterpret_cast<char*>(&(this->FlightNum)), sizeof(this->FlightNum));
	StrToBin(file, this->DepDate);
	StrToBin(file, this->Destination);
	file->write(reinterpret_cast<char*>(&(this->NumPieces)), sizeof(this->NumPieces));
	file->write(reinterpret_cast<char*>(&(this->Weight)), sizeof(this->Weight));
}

//���������� ��������� �� ��������� �����
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

//���� � �������
baggage InputBaggage()
{
	baggage b;
	b.SetSurname(InputInformation("������� ������� ���������: "));
	b.SetFlightNum(InputNumber(0, 100, "������� ����� ����� (0 - 100): "));
	MyDate d;
	d.InputDate();
	b.SetDepDate(d.ToString());
	b.SetDestination(InputInformation("������� ����� ����������: "));
	b.SetNumPieces(InputNumber(0, 200, "������� ���������� ���� ��� ������ (0 - 200): "));
	b.SetWeight(InputNumber(0, 100, "������� ��� ������ (0 - 100): "));
	return b;
}

//���� � ������� � ������ "��������"
baggage InputOwnerBaggage(string name, _int32 nump)
{
	baggage b;
	b.SetSurname(name);
	b.SetFlightNum(InputNumber(0, 100, "������� ����� ����� (0 - 100): "));
	MyDate d;
	d.InputDate();
	b.SetDepDate(d.ToString());
	b.SetDestination(InputInformation("������� ����� ����������: "));
	b.SetNumPieces(nump);
	b.SetWeight(InputNumber(0, 100, "������� ��� ������ (0 - 100): "));
	return b;
}

//����� �� �������
void OutputBaggage(baggage b)
{
	cout << setw(1) << left << "|" << setw(15) << left << b.GetSurname() << "|" 
		<< setw(10) << left << b.GetFlightNum() << "|" << setw(15) << left << b.GetDepDate() << "|" <<
		setw(15) << left << b.GetDestination() << "|" << setw(10) << left <<
		b.GetNumPieces() << "|" << setw(10) << left << b.GetWeight() << "|";
}

//������� ��������� � ������
string ToString(baggage b, _int32 i)
{
	string result = "������ � " + to_string(i) + "\n" + "������� ���������: " + b.GetSurname() + "\n" + "����� �����: " + to_string(b.GetFlightNum()) + "\n" + "���� ������: " + b.GetDepDate() + "\n" +
		"����� ����������: " + b.GetDestination() + "\n" + "���������� ���� ������: " + to_string(b.GetNumPieces()) + "\n" +
		"��� ������: " + to_string(b.GetWeight()) + "\n";
	return result;
}

//��������� �� ���������
/*bool IsEqual(baggage b1, baggage b2)
{
	return ((b1.GetSurname() == b2.GetSurname()) && (b1.GetFlightNum() == b2.GetFlightNum()) && (b1.GetDepDate() == b2.GetDepDate()) &&
		(b1.GetDestination() == b2.GetDestination()) && (b1.GetNumPieces() == b2.GetNumPieces()) && (b1.GetWeight() == b2.GetWeight()));
}*/

//����������� ��������� �� ������
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
			string wrd = "������� ���������: ";
			result.SetSurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� �����: ";
			result.SetFlightNum(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "���� ������: ";
			result.SetDepDate(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� ����������: ";
			result.SetDestination(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "���������� ���� ������: ";
			result.SetNumPieces(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��� ������: ";
			result.SetWeight(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "������ ������ � ����!" << endl;
	}
	return result;
}

/*����� �� ���������
1 - �������
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
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

/*���� �������� ������
1 - �������
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
baggage InputForSearchInfo(_int32 type_search)
{
	baggage bag;
	MyDate d;
	switch (type_search)
	{
	case 1:
		bag.SetSurname(InputInformation("������� �������: "));
		return bag;
	case 2:
		d.InputDate();
		bag.SetDepDate(d.ToString());
		return bag;
	case 3:
		bag.SetDestination(InputInformation("������� ����� ����������: "));
		return bag;
	case 4:
		bag.SetWeight(InputNumber(0, 100, "������� ��� ������ (0 - 100): "));
	default:
		return bag;
	}
}

/*��������� �������� �� ��������� ����
1 - �������
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
_int32 �omparison(baggage b1, baggage b2, _int32 type_search)
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