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

//�����������
Owner::Owner()
{
	OwnerSurname = "";
	NumOfBag = 0;
}

//��������� ���������
Owner Owner::ChangeOwner(Owner &res)
{
	cout << "����� ���� �� ������ ��������?" << endl;
	cout << "1 - �������" << endl;
	cout << "2 - ���������� ������" << endl;
	cout << "0 - ������" << endl;
	_int32 num = InputNumber(0, 2, "");
	switch (num)
	{
	case 1:
		res.SetOwnerSurname(InputInformation("������� �������: "));
		break;
	case 2:
		res.SetNumOfBag(InputNumber(0, 300, "������� ���������� ������ (0 - 200): "));
		break;
	default:
		exit(0);
		break;
	}
	return res;
}

//������������� �������� ������������
Owner& Owner::operator = (Owner ow)
{
	OwnerSurname = ow.GetOwnerSurname();
	NumOfBag = ow.GetNumOfBag();
	return (*this);
}

//������ ��������� � �������� ����
void Owner::OwnerToBinFile(fstream * file)
{
	StrToBin(file, this->OwnerSurname);
	file->write(reinterpret_cast<char*>(&(this->NumOfBag)), sizeof(this->NumOfBag));
}

//���������� ��������� �� ��������� �����
Owner OwnerFromBinFile(fstream *file, bool &ok)
{
	Owner ow;
	_int32 temp;
	ow.SetOwnerSurname(StrFromBin(file));
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	ow.SetNumOfBag(temp);
	return ow;
}

//���� � �������
Owner InputOwner()
{
	Owner ow;
	ow.SetOwnerSurname(InputInformation("������� �������: "));
	ow.SetNumOfBag(InputNumber(0, 200, "������� ���������� ������ (0 - 200): "));
	return ow;
}

//����� �� �������
void OutputOwner(Owner ow)
{
	cout << setw(1) << left << "|" << setw(7) << left << ow.GetOwnerSurname() << "|" << setw(10) << left << ow.GetNumOfBag() << "|";
}

//������� ��������� � ������
string ToString(Owner ow, _int32 i)
{
	string res = "������ � " + to_string(i) + "\n" + "�������: " + ow.GetOwnerSurname() + "\n" + "���������� ������: " + to_string(ow.GetNumOfBag()) + "\n";
	return res;
}

//��������� �� ���������
bool IsEqual(Owner ow1, Owner ow2)
{
	return ((ow1.GetOwnerSurname() == ow2.GetOwnerSurname()) &&
		(ow1.GetNumOfBag() == ow2.GetNumOfBag()));
}

//���������� ��������� �� ������
Owner ReadFromStringOwner(ifstream& input)
{
	Owner res;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "�������: ";
			res.SetOwnerSurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "���������� ������: ";
			res.SetNumOfBag(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "������!" << endl;
	}
	return res;
}