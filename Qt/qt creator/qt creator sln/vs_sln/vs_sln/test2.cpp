#include "test2.h"
#include <iostream>

CTest2::CTest2()
{
}

void CTest2::echo_msg(const char* msg)
{
	std::cout << "test2:" << msg << std::endl;
}