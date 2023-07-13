#include "mul_s.h"
#include "stdio.h"
#include "mul.h"

double mul_s(double a, double b)
{
    printf("%.2f * %.2f = %.2f\n", a, b, mul(a, b));
    return mul(a, b);
}