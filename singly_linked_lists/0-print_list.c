#include <stdio.h>
#include "lists.h"

/**
 * print_list - print the full single linked list
 * @h: pointer to the start of the nodes
 *
 * Return: size_t count of nodes
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;
	while (h != NULL)
	{
		count += 1;
		if (h->str == NULL)
		{
			printf("[0] (nil)\n");
		}
		else
		{
			printf("[%u] %s\n", h->len, h->str);
		}
		h = h->next;
	}
	return (count);
}
