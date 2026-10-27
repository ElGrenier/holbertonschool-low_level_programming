#include <stdlib.h>
#include <stdio.h>
/**
 * main - print the alphabet in lowercase in reverse
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
int letter = 48;
while (letter <= 57)
{
putchar(letter);
if (letter != 57)
{
putchar(',');
putchar(' ');
}
letter++;
}
putchar('\n');
return (0);
}
