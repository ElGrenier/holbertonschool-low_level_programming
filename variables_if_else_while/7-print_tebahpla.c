#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - print the alphabet in lowercase in reverse
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char letter = 'z';
while (letter >= 'a')
{
putchar(letter);
letter--;
}
putchar('\n');
return (0);
}
