#include "main.h"
/**
 * _strstr - locate a substring in a string
 * @haystack: pointer to the string
 * @needle: the substring to locate
 * Return: pointer of first occurrence of substring, NULL if not found
 */
void print_chessboard(char (*a)[8])
{
int i, j;
for (i = 0; i < 8; i++)
{
for (j = 0; j < 8; j++)
{
_putchar(a[i][j]);
}
_putchar('\n');
}
}
