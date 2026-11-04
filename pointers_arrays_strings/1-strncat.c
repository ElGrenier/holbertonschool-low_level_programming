#include <stdio.h>
/**
 * _strncat - concatenate two strings
 * @dest: pointer to the destination array
 * @src: pointer to the source string
 * @n: maximum number of characters to concatenate
 *
 * Return: pointer to the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i + j] = src[j];
	}
	return (dest);
}
