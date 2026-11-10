#include <stdlib.h>
#include "main.h"
/**
 * _memset - fill memory with a constant byte
 * @s: pointer to the memory area
 * @b: the constant byte
 * @n: number of bytes to fill
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
{
s[i] = b;
}
return (s);
}
/**
 * _calloc - allocate memory with 0 bytes
 * @nmemb: number of element
 * @size: size of the element
 *
 * Return: pointer to the memory, NULL if failed
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
void *ptr;

if (nmemb == 0 || size == 0)
	return (NULL);

ptr = malloc((size * nmemb));
if (ptr == NULL)
	return (NULL);
_memset(ptr, 0, (size * nmemb));
return (ptr);
}
