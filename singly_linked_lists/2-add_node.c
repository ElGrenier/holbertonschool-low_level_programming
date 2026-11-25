#include <string.h>
#include <stdlib.h>

#include "lists.h"

/**
 * add_node - add a new node
 * @head: pointer to the head
 * @str: the string to add to the new node
 *
 * Return: list_t count of nodes
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = strdup(str);
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}
	new->len = strlen(str);
	new->next = *head;
	*head = new;

	return (new);
}
