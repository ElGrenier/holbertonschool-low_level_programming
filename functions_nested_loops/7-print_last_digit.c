#include "main.h"
/**
 * print_last_digit - print the last digit of a number
 * @n: the number to check
 *
 * Return: the last digit of n
 */
int print_last_digit(int n)
{
int i;
if (n < 0)
{
n = -n;
}
i = n % 10;
_putchar(i + '0');
return (i);
}
