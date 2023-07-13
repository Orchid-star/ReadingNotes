#include "test1.h"
#include "add_s.h"
#include "sub_s.h"
#include "mul_s.h"
#include "dev_s.h"

void test()
{
    double a = 10;
    double b = 5;

    add_s(a, b);
    dev_s(a, b);
    mul_s(a, b);
    sub_s(a, b);
}