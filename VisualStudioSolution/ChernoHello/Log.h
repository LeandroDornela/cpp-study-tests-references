#pragma once

#include <iostream>

class Log
{
public:
	enum Level
	{
		LevelError = 0,
		LevelWarning = 1,
		LevelInfo = 2
	};

private:
	Level _level = LevelError;

private:
	

public:

	Log();
	~Log();

	void SetLevel(Level logLevel);
	void Error(const char* message);
	void Warning(const char* message);
	void Info(const char* message);
};