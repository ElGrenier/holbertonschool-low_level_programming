#include "main.h"
/**
 * print_sign - check the sign of a number
 * @n: the character to check
 *
 * Return: 1 if the number is positive, 0 if the number is zero, -1 if the number is negative
 */
int print_sign(int n)
{
if (n > 0)
{
_putchar('+');
_putchar('\n');
return (1);
}
else if (n == 0)
{
_putchar('0');
_putchar('\n');
return (0);
}
else
{
_putchar('-');
_putchar('\n');
return (-1);
}
}
