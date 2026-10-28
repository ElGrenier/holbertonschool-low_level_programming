#include <stdio.h>
#include "main.h"
/**
* add - adds two integers
* @a: first integer
* @b: second integer
* Return: the sum of a and b
*/
void print_to_98(int n)
{
if (n <= 98)
{
while (n < 98)
{
printf("%d, ", n);
n++;
}
printf("%d", 98);
}
else
{
while (n > 98)
{
printf("%d, ", n);
n--;
}
printf("%d", 98);
}
printf("\n");
}
