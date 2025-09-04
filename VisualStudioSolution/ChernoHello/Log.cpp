#include "Log.h"

Log::Log()
{
	SetLevel(LevelInfo);
}

Log::~Log()
{

}

void Log::SetLevel(Level logLevel)
{
	_level = logLevel;
}

void Log::Error(const char* message)
{
	if(_level >= LevelError)
		std::cout << "[ERROR]: " << message << std::endl;
}

void Log::Warning(const char* message)
{
	if (_level >= LevelWarning)
		std::cout << "[WARNING]: " << message << std::endl;
}

void Log::Info(const char* message)
{
	if (_level >= LevelInfo)
		std::cout << "[INFO]: " << message << std::endl;
}
