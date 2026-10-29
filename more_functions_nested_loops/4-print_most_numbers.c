#include "main.h"
/**
 * print_most_numbers - print the numbers from 0 to 9 except 2 and 4
 *
 * Return: Nothing
 */
void print_most_numbers(void)
{
char number = '0';
while (number <= '9')
{
if (number == '2')
{
continue;
}
else if (number == '4')
{
continue;
}
else
{
_putchar(number);
number++;
}
}
_putchar('\n');
}

