#include <stdlib.h>
#include <stdio.h>
/**
 * main - print the alphabet in lowercase in reverse
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char letter = '0';
while (letter <= '9')
{
putchar(letter);
letter++;
}
letter = 'a';
while (letter <= 'f')
{
putchar(letter);
letter++;
}
putchar('\n');
return (0);
}
