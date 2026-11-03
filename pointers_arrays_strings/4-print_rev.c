#include "main.h"
/**
 * _puts - print a string
 * @str: pointer to the string
 *
 * Return: void
 */
void print_rev(char *s)
{
int i; 
for (; *s != '\0'; s++)
{
i++;
}
s--;
for (; i >= 0; i--)
{
_putchar(*s);
s--;
}
_putchar('\n');
}
