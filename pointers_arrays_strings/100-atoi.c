#include <stdio.h>
/**
 * _atoi - convert a string to an integer
 * @s: pointer to the string
 *
 * Return: the integer value of the string
 */
int _atoi(char *s)
{
int minus = 0, number = 0;

while (*s != '\0' && (*s < '0' || *s > '9'))
{
if (*s == '-')
{
minus++;
}
s++;
}

while (*s >= '0' && *s <= '9')
{
number = number * 10 - (*s - '0');
s++;
}

if (minus % 2 == 0)
{
number = -number;
}
return (number);
}
