#include "main.h"
/**
 * print_last_digit - print the last digit of a number
 * @n: the number to check
 *
 * Return: the last digit of n
 */
int print_last_digit(int n)
{
return ((n % 10) * 10 + (n % 10));
}
