#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <string>
#include <iostream>
#include "HelpUtils.h"


//������ ����
class MyDate {
public:
	// �������� �������� �� ��� ����������
	bool IsLeap(int year);

	// �������� ���� �� ������������
	bool CorrectDate(int day, int month, int year, string &message);

	// ����
	int day;
	// �����
	int month;
	// ���
	int year;
	int hours;
	int minutes;

	// ����������� �� ���������
	MyDate();

	// ���� ���� � �������
	void InputDate();

	// ������� ���� � ������ (��� ����������� ������ � ����)
	string ToString();

	// ������������� �������� ���������
	bool operator == (const MyDate &c);

	// ����������� �����������
	MyDate& operator = (MyDate c);

	// ������������� �������� ������
	bool operator > (const MyDate &c);

	// ������������� �������� ������
	bool operator < (const MyDate &c);

	//���������� ��������� "����" �� ������ 
	// ������:
	// ���� ����� ���
	static MyDate FromString(string str);

};