#include <stdio.h>
#include <string.h>

#include "lists.h"

/**
 * list_len - list the number of nodes
 * @h: pointer to the start of the nodes
 *
 * Return: size_t count of nodes
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t node = {strdup(str), strlen(str), NULL};
	*head = &node;

	return (&node);
}
