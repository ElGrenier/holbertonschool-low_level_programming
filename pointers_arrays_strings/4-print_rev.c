#include "main.h"
/**
 * print_rev - print a string in reverse
 * @s: pointer to the string
 *
 * Return: void
 */
void print_rev(char *s)
{
int i = 0;
for (; *s != '\0'; s++)
{
i++;
}
s--;

for (; i > 0; i--)
{
_putchar(*s);
s--;
}
_putchar('\n');
}
