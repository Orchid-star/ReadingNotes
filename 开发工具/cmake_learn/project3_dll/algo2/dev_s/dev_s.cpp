#include "dev_s.h"
#include "stdio.h"
#include "dev.h"

double dev_s(double a, double b)
{
    printf("%.2f / %.2f = %.2f\n", a, b, dev(a, b));
    return dev(a, b);
}