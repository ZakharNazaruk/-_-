#pragma once


#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "interface.h"
#include <chrono>
#include <thread>

using namespace std;



struct User {
	string login;
	string password;
	bool isAdmin;
	bool isBanned;
	struct Info {
		string FIO;
		int age;
	}info;

};



struct Toy {
	string name;
	float price;
	string manufacturer;
	int quantity;
	int minAge;

};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость
	structCursorInfo.dwSize = size; // изменяем размер
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void Cyan() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void Green() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}
void Purpule() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_BLUE);
}
void Red() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

