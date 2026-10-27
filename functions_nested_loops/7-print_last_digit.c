#include "main.h"
/**
 * print_last_digit - print the last digit of a number
 * @n: the number to check
 *
 * Return: the last digit of n
 */
int print_last_digit(int n)
{
int i = n % 10;
int last_digit = i + n % 10;
return (last_digit);
}
