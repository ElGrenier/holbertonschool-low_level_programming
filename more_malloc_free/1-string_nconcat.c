#include <stdlib.h>
#include "main.h"
/**
 * _strlen - calculate the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
int len = 0;
while (s[len] != '\0')
len++;

return (len);
}
/**
 * _strncpy - copy a string
 * @dest: pointer to the destination array
 * @src: pointer to the source string
 * @n: maximum number of characters to copy
 *
 * Return: pointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j;

	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[j] = src[j];
	}
	for (; j < n; j++)
	{
		dest[j] = '\0';
	}
	return (dest);
}
/**
 * string_nconcat - concatenate two strings
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 * @n: number of characters to concatenate from the second string
 *
 * Return: pointer to the concatenated string, or NULL if it fails
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
char *ptr;
int i;

if (s1 == NULL)
s1 = "";
if (s2 == NULL)
s2 = "";

ptr = malloc((sizeof(char) * (_strlen(s1) + n + 1)));
if (ptr == NULL)
	return (NULL);

for (i = 0; i < (_strlen(s1)); i++)
{
	ptr[i] = s1[i];
}
_strncpy(&ptr[i], s2, n);
ptr[i + n] = '\0';
return (ptr);
}
