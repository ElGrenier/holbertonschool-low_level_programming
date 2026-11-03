#include "main.h"
/**
 * puts2 - print every other character of a string
 * @str: pointer to the string
 *
 * Return: void
 */
void puts2(char *str)
{
int i = 0;
for (; *str != '\0'; str++, i++)
{
if (i % 2 == 0)
{
_putchar(*str);
}
}
_putchar('\n');
}
