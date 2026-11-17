#include <stdio.h>
#include "function_pointers.h"
/**
 * array_iterator - do thing on the array
 * @array: the array
 * @size: the size of the array
 * @action: the function to do
 * Return: void
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
int i;
for (i = 0; i < size; i++)
{
action(array[i]);
}
}
