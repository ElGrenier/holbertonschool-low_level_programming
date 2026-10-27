#include "main.h"
/**
 * _abs - compute the absolute value of an integer
 * @n: the character to check
 *1
 * Return: the absolute value of n
 */
int _abs(int n)
{
if (n > 0)
{
return (n);
}
else if (n == 0)
{
return (0);
}
else
{
return (n * -1);
}
}
