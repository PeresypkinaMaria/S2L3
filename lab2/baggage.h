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
	string Surname; //������� ���������
	_int32 FlightNum; //����� �����
	string DepDate; //���� ������
	string Destination; //���� ����������
	_int32 NumPieces; //���������� ���� ������
	_int32 Weight; //��� ������

public:
	//�������� ������� � �����
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

	//�����������
	baggage();

	baggage(string name);

	//��������� ���������
	baggage ChangeBaggage(baggage &res);

	//������������� �������� ���������
	bool operator== (baggage b);

	//������ ��������� � �������� ����
	void BagToBinFile(fstream *file);
};

//���������� ��������� �� ��������� �����
baggage BagFromBinFile(fstream *file, bool &ok);

//���� � �������
baggage InputBaggage();

//���� � ������� � ������ "��������"
baggage InputOwnerBaggage(string name, _int32 nump);

//����� �� �������
void OutputBaggage(baggage b);

//������� ��������� � ������
string ToString(baggage b, _int32 i);

//��������� �� ���������
bool IsEqual(baggage b1, baggage b2);

//���������� ��������� �� ������
baggage ReadFromString(ifstream& input);

/*����� �� ���������
1 - ����� �����
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
bool SearchInfo(baggage b1, baggage b2, _int32 type_search);

/*���� �������� ������
1 - ����� �����
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
baggage InputForSearchInfo(_int32 type_search);

/*��������� �������� �� ��������� ����
1 - ����� �����
2 - ���� ������
3 - ����� ����������
4 - ��� ������*/
_int32 �omparison(baggage b1, baggage b2, _int32 type_search);