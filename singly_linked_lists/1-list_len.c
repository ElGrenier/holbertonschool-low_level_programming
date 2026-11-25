#include <stdio.h>
#include "lists.h"

/**
 * list_len - list the number of elements
 * @h: pointer to the start of the nodes
 *
 * Return: size_t count of nodes
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		count += 1;
	}
	return (count);
}
