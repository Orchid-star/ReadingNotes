#include "add_s.h"
#include "stdio.h"
#include "add.h"

double add_s(double a, double b)
{
    printf("%.2f + %.2f = %.2f\n", a, b, add(a, b));
    return add(a, b);
}