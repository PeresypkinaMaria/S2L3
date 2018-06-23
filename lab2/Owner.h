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
	string OwnerSurname; //������� ��������� ������
	_int32 NumOfBag; //���������� ������
public:
	//�������� �������
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

	//�����������
	Owner();

	//��������� ���������
	Owner ChangeOwner(Owner &res);

	//������������� �������� ������������
	Owner& operator = (Owner ow);

	//������ ��������� � �������� ����
	void OwnerToBinFile(fstream *file);
};

//���������� ��������� �� ��������� �����
Owner OwnerFromBinFile(fstream *file, bool &ok);

//���� � �������
Owner InputOwner();

//����� �� �������
void OutputOwner(Owner ow);

//������� ��������� � ������
string ToString(Owner ow, _int32 i);

//��������� �� ���������
bool IsEqual(Owner ow1, Owner ow2);

//���������� ��������� �� ������
Owner ReadFromStringOwner(ifstream& input);