#include <stdio.h>
#include "function_pointers.h"
/**
 * int_index - do thing on the array
 * @array: the array
 * @size: the size of the array
 * @cmp: the function to compare
 * Return: void
 */
int int_index(int *array, int size, int (*cmp)(int))
{
int i;

if (size <= 0 || array == NULL || cmp == NULL)
	return (-1);

for (i = 0; i < size ; i++)
{
if (cmp(array[i]) != 0)
	return (i);
}
return (-1);
}
