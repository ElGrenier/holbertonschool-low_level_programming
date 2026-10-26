#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - print the alphabet in lowercase
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char letter = 'a';
while (letter <= 'z')
{
if (letter == 'e' || letter == 'q')
{
letter++;
continue;
}
putchar(letter);
letter++;
}
letter = 'A';
putchar('\n');
return (0);
}
