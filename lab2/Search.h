//������ � ��������� � �������� ��� ����
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "baggage.h"
#include "Owner.h"
#include "HelpUtils.h"
#include "MyDate.h"

using namespace std;


template <class Type>
class Task {
private:
	vector<Type> vect; //���������

	// ���������� �� ��������� �������� 
	void ShellSort(_int32 n, _int32 typ, _int32(*Compare)(Type, Type, _int32))
	{
		_int32 i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], typ) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}
	// �������� �����
	_int32 BinarySearchElement(_int32 left, _int32 right, _int32 typesearch, Type d, _int32(*Compare)(Type, Type, _int32))
	{
		_int32 midd = 0;
		while (1)
		{
			midd = (left + right) / 2;

			if (Compare(d, vect[midd], typesearch) == -1)// ���� ������� ������ �������� � ������
				right = midd - 1;				// ������� ������ ������� ������
			else if (Compare(d, vect[midd], typesearch) == 1)  // ���� ������� ������ �������� � ������
				left = midd + 1;					// ������� ����� ������� ������
			else                       // ����� (�������� �����)
				return midd;           // ������� ���������� ������ ������

			if (left > right)          // ���� ������� ���������� 
				return -1;
		}
	}
public:
	//�������� �������
	vector<Type> GetVect()
	{
		return vect;
	}

	vector<Type> SetVect(vector<Type> value)
	{
		return vect = value;
	}

	// �������� ��������
	void Remove(_int32 numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb - 1);
	}

	// ���������� ��������
	void Add(Type &elem)
	{
		vect.push_back(elem);
	}

	//������ �������
	_int32 size()
	{
		return vect.size();
	}

	// �������� �� �������
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	// ����� � ����
	// void(*f) (Type) - ��������� �� �������, ������� ���������� ���� ��������� � ����  
	void OutputFile(vector<Type> items, string(*f)(Type, int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Type>::const_iterator pos;
			int count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count) << ' ';
				count++;
			}
			cout << endl << "���� ��������!" << endl;
			fout.close();
		}
		else
		{
			cout << "���� �� ��������!" << endl;
		}
	}

	//����� �� �����, f - �������, ������� ������� ���� ��������� �� �����  
	void OutputScreenBag(vector<baggage> items, void(*f) (baggage))
	{
		vector<baggage>::const_iterator pos;
		_int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(6) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "������ ����" << endl;
	}

	// ����� �� �����
	// void(*f) (Type) - ��������� �� �������, ������� ��������� ���� ��������� �� �����  
	void OutputScreenOw(vector<Owner> items, void(*f) (Owner))
	{
		vector<Owner>::const_iterator pos;
		_int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(6) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "������ ����!" << endl;
	}

	// ���� �� �����
	// Type(*f)(ifstream&) - ��������� �� �������, ������� ��������� ���� ��������� �� ����� 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "�� ������� ������� ����" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	// ���� � ������
	//Type(*f)() - ��������� �� �������, ������� ������ ���� ��������� � �������
	void ReadFromScreen(Type(*f)())
	{
		int n;
		Type elem;
		do
		{
			vect.push_back(f());
			n = InputNumber(0, 1, "�� ������ �������� �������? (1 - ��, 0 - ���)\n��� �����: ");
		} while (n != 0);
	}

	// �������� �����
	// bool(*Equal)(Type, Type, int) - ��������� �� �������, ������� ��������� ��������� �������� ��-�� � ������� �� typesearch
	vector<Type> LinearySearch(Type search_elem, bool(*Equal)(Type, Type, _int32), _int32 typesearch)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem, *iter, typesearch))
				NewVect.push_back(*iter);

		}

		return NewVect;
	}
};