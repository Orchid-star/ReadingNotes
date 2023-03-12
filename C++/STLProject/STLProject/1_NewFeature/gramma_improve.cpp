#include "header.h"

typedef std::vector<int > new_type1;
typedef std::vector<int> new_type2;

void test_nullptr(int a) {
	std::cout << "int" << std::endl;
}

void test_nullptr(void* a) {
	std::cout << "pointer" << std::endl;
}

void test0313()
{
	std::nullptr_t ptrr = 0;
	test_nullptr(0);
	test_nullptr(nullptr);
	test_nullptr(ptrr);
	std::cout << (ptrr == nullptr);
}