#include "sub_s.h"
#include "stdio.h"
#include "sub.h"

double sub_s(double a, double b)
{
    printf("%.2f - %.2f = %.2f\n", a, b, sub(a, b));
    return sub(a, b);
}