#include <iostream>
#include "Log.h"

void InitLog()
{
	
}

void Log(const char* message)
{
	std::cout << message << std::endl;
}

void Increment1(int* value)
{
	(*value)++;
}

void Increment2(int& value)
{
	value++;
}