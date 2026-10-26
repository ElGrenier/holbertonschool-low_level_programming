#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - print the numbers from 0 to 9
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
char number = '0';
while (number <= '9')
{
putchar(number);
number++;
}
putchar('\n');
return (0);
}

