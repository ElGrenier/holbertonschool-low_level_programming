#include <stdlib.h>
#include "main.h"
/**
 * _calloc - allocate memory with 0 bytes
 * @nmemb: number of element
 * @size: size of the element
 *
 * Return: pointer to the memory, NULL if failed
 */
int *array_range(int min, int max)
{
int delta = max - min + 1;
int i;
int *ptr;

if (min > max)
	return (NULL);

ptr = malloc(sizeof(int) * delta);
if (ptr == NULL)
	return (NULL);

for (i = 0; i <= delta; i++, min++)
{
ptr[i] = min;
}
return (ptr);
}
