#pragma once
#include <iostream>
#include <tgmath.h>
#include <chrono>
#include <ctime>
#include <Windows.h>
#include <stdlib.h>
#include <string>


class SmartChar
{
private:
	char* m_array = nullptr;
	char* test = new char[10];
public:
	int lenght = 0;

public:
	SmartChar(const int& size)
	{
		m_array = new char[size];
		lenght = size;

		test[9] = '\0';
	}

	~SmartChar()
	{
		//delete[] m_array;
		delete[] test;
	}

	void SetAt(const int& index,const char& value)
	{
		m_array[index] = value;
	}

	char GetAt(const int& index)
	{
		return m_array[index];
	}

	const char* GetArray()
	{
		return m_array;
	}
};



class ConsoleRenderer
{
public:
	int width = 256;
	int heigth = 80;

private:
	int pixelCount = 0;
	char* screenBuffer = nullptr;
	int* pixelBuffer = nullptr;

	SmartChar sc_screenBuffer;

	float ratio = 0;

	const std::string grayRamp;

	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	float lifeTime = 0;
	float fixedRandA;
	float fixedRandB;
	float fizedRandC; 

public:
	ConsoleRenderer(int w, int h);
	void Draw(float dt);
	~ConsoleRenderer();

private:
	void CleanScreen();
	char GetCharCodeFromColor(const int& r, const int& g, const int& b);
};