#include "main.h"
/**
 * puts_half - print the second half of a string
 * @str: pointer to the string
 *
 * Return: void
 */
void puts_half(char *str)
{

int len = 0, half = 0, i;
for (; str[len] != '\0'; len++)
;
if (len % 2 == 0)
{
half = len / 2;
}
else
{
half = (len + 1) / 2;
}
for (i = half; str[i] != '\0'; i++)
{
_putchar(str[i]);
}
_putchar('\n');
}
