#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//ввод числа
int InputNumber(int min, int max, string message);
//ввод строки
string InputInformation(string messge);
//проверки на корректность введенных символов
bool CorrectSymbol(char c);
bool CorrectName(string name);
//ввод имени файла
string InputFileName();
//запись строки в бинарный файл
void StrToBin(fstream *f, string str);
//считывание строки из бинарного файла
string StrFromBin(fstream *f);

//печать шапки таблицы владельца багажа
void PrintHeadOwners();
//печать шапки таблицы информации о багаже
void PrintHeadBag();