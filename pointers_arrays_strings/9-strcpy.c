#include <stdio.h>
/**
 * print_array - print elements of an array of integers
 * @a: pointer to the array
 * @n: number of elements to print
 *
 * Return: void
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;
for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}