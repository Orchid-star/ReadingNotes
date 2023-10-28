#include "test1.h"
#include <iostream>

CTest1::CTest1()
{
}

void CTest1::echo_msg(const char* msg)
{
	std::cout << "test1:" << msg << std::endl;
}
